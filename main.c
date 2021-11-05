#include "Framework/Data/Data.h"
#include "Framework/Utilities/Float.h"
#include "Framework/Utilities/Int.h"
#include "Framework/Map/Map.h"
#include "IO.h"   //Doesn't exist -- Provides hardware inputs/outputs access.
#include "ROM.h"  //Doesn't exist -- Provides ROM access for loading baked data.
#include <stdio.h>
#include <time.h>
int (*FetchMap)();
Map map = {0};
int settingsChanged = 0;
int lastPulseTime = ~0;
int GetIndex(Values* values,int valuesCount,int rpm){
    int minimum = 0;
	int maximum = valuesCount;
	while(minimum != maximum){
		int middle = (values[maximum].rpm - values[minimum].rpm) / 2;
    	if(rpm > middle){minimum = middle + 1;}
		else if(rpm < middle){maximum = middle - 1;}
	}
	return minimum;
}
int FetchBaked(){
    int currentTime = clock();
	int rpm = 60 / ((currentTime - lastPulseTime) / CLOCKS_PER_SEC);
	rpm = Int_Clamp(rpm,0,map.valuesCount - 1);
    lastPulseTime = currentTime;
	return map.values[rpm].advance;
}
int FetchBlended(){
    int currentTime = clock();
	int rpm = 60 / ((currentTime - lastPulseTime) / CLOCKS_PER_SEC);
	int max = map.valuesCount - 1;
	int previous;
	int next;
	if(rpm < 0){return map.values[0].advance;}
	if(rpm > max){return map.values[max].advance;}
	previous = GetIndex(map.values,map.valuesCount,rpm);
	next = previous + 1;
    lastPulseTime = currentTime;
    return Int_Lerp(map.values[previous].advance,map.values[next].advance,map.values[rpm]);
}
int FetchLogarithmic(){
    int currentTime = clock();
	int rpm = 60 / ((currentTime - lastPulseTime) / CLOCKS_PER_SEC);
    lastPulseTime = currentTime;
    return log2(rpm);
}
int Setup(){
	int (*Methods[]) = {&FetchBaked,&FetchBlended,&FetchLogarithmic};
    int romOffset = ROM_Read(0);
    int index = 0;
    Data data = {0};
    data.start = romOffset;
    map.mode = Data_ReadByte(&data);
    if(!Int_Within(map.mode,0,MaxMapType)){
        printf("main.c/Setup(): unknown map type. Exiting.\n");
        return 0;
    }
	FetchMap = Methods[map.mode];
    map.dataSize = Data_ReadInt(&data);
    if(!map.dataSize){
        printf("main.c/Setup(): data is of size 0. Exiting.\n");
        return 0;
    }
    map.valuesCount = map.dataSize % sizeof(Values);
    for(;index<map.valuesCount;++index){
        map.values[index].rpm = Data_ReadShort(&data);
        map.values[index].advance = Data_ReadByte(&data);
    }
    return 1;
}
int main(){
    if(!Setup()){return -1;}
    while(1){
		int pulse;
		int timing;
		if(settingsChanged){
			if(!Setup()){return -1;}
			settingsChanged = 0;
			printf("main.c/main(): settings changed.\n");
			continue;
		}
		pulse = IO_Read(IGNITION_PULSE);
		if(!pulse){continue;}
		timing = FetchMap();
    }
    return 0;
}
