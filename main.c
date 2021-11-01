#include "Framework/Data/Data.h"
#include "Framework/Utilities/Float.h"
#include "Framework/Utilities/Int.h"
#include "Framework/Map/Map.h"
#include "IO.h"   //Doesn't exist -- Provides hardware inputs/outputs access.
#include "ROM.h"  //Doesn't exist -- Provides ROM access for loading baked data.
#include <cmath.h>
#include <stdio.h>
#include <time.h>
Map map = {0};
int settingsChanged = 0;
int lastPulseTime = ~0;
int main(){
    if(!Setup()){return -1;}
    while(true){
        if(!settingsChanged){Step();}
        if(!Setup()){return -1;}
        settingsChanged = 0;
        printf("main.c/main(): settings changed.\n");
    }
    return 0;
}
bool Setup(){
    Data data = {0};
    int romOffset;
    int count;
    int index = 0;
    romOffset = ROM_Read(0);
    data.start = romOffset;
    map.mode = Data_ReadByte(&data);
    if(!Int_Within(map.mode,0,MaxMapType)){
        printf("main.c/Setup(): unknown map type. Exiting.\n");
        return 0;
    }
    map.dataSize = Data_ReadInt(&data);
    if(!map.dataSize){
        printf("main.c/Setup(): data is of size 0. Exiting.\n");
        return 0;
    }
    map.valuesCount = map.dataSize % valuesFields;
    for(;index<map.valuesCount;++index){
        map.values[index].rpm = Data_ReadShort(&data);
        map.values[index].advance = Data_ReadByte(&data);
    }
    return 1;
}
void Step(){
    int rpm;
    int currentTime;
    int advance = 0;
    int pulse = IO_Read(PIN1);
    if(!pulse){return;}
    currentTime = clock();
    rpm = 60 / ((currentTime - lastPulseTime) / CLOCKS_PER_SEC);
    if(map.mode == Baked){
        rpm = Clamp(0,sizeof(map.values)/sizeof(map.values[0]),rpm);
        advance = MapData.values[rpm].advance;
    }
    else if(MapData.mode == Blended){
        int previous = PreviousIndex(MapData.values[rpm]);
        int next = NextIndex(MapData.values[rpm]);
        advance = Lerp(MapData.values[previous],MapData.values[next],MapData.values[rpm]);
    }
    else{advance = log2(rpm);}
    lastPulseTime = currentTime;
}
