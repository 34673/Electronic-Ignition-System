#include "Framework/Data/Data.h"
#include "Framework/Map/Map.h"
#include "Framework/Math/Math.h"
#include "IO.h"   //Doesn't exist -- Provides hardware inputs/outputs access.
#include "ROM.h"  //Doesn't exist -- Provides ROM access for loading baked data.
#include "Time.h" //Doesn't exist -- Provides time related utilities.
int lastPulseTime = ~0;
void Setup(){
    Data data;
    data.start = ROM_Read(0);
    MapData.mode = Data_ReadByte(&data);
    MapData.size = Data_ReadInt(&data);
    Data_ReadBytes(&data,MapData.values,MapData.size);
}
void Loop(){
    int currentTime;
    int rpm;
    int advance = 0;
    int pulse = IO_ReadPin(PIN1);
    if(!pulse){return;}
    currentTime = GetTime();
    rpm = 60 / (currentTime - lastPulseTime);
    if(MapData.mode == Baked){advance = Clamp(MapData.values[rpm]);}
    if(MapData.mode == Blended){
        int previous = PreviousIndex(MapData.values[rpm]);
        int next = NextIndex(MapData.values[rpm]);
        advance = Lerp(MapData.values[previous],MapData.values[next],MapData.values[rpm]);
    };
    lastPulseTime = currentTime;
}
