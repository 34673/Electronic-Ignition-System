#include "Data.h"
#include "stdlib.h"
#include "../Utilities/Float.h"
char Data_ReadByte(Data* Data){
	Data->position = Data->end ? (int)Clamp((int)Data->start,(int)Data->end,(int)Data->position + sizeof(char)) : (int)Data->position + sizeof(char);
	return *(char*)Data->position;
}
short Data_ReadShort(Data* Data){}
int Data_ReadInt(Data* Data){
	Data->position = Data->end ? (int)Clamp((int)Data->start,(int)Data->end,(int)Data->position + sizeof(int)) : (int)Data->position + sizeof(int);
	return *(int*)Data->position;
}
long Data_ReadLong(Data* Data){}
float Data_ReadFloat(Data* Data){}
double Data_ReadDouble(Data* Data){}
unsigned char Data_ReadUByte(Data* Data){}
unsigned short Data_ReadUShort(Data* Data){}
unsigned int Data_ReadUInt(Data* Data){}
unsigned long Data_ReadULong(Data* Data){}
void Data_ReadBytes(Data* Data,char* output,int size){
	if(Data->end && size > Data->end){size = (int)Data->end - (int)Data->position;}
	memcpy(output,Data->position,size);
}
void Data_ReadShorts(Data* Data){}
void Data_ReadInts(Data* Data){}
void Data_ReadLongs(Data* Data){}
void Data_ReadFloats(Data* Data){}
void Data_ReadDoubles(Data* Data){}
void Data_ReadUBytes(Data* Data){}
void Data_ReadUShorts(Data* Data){}
void Data_ReadUInts(Data* Data){}
void Data_ReadULongs(Data* Data){}
void Data_WriteByte(Data* Data){}
void Data_WriteBytes(Data* Data){}
void Data_WriteShort(Data* Data){}
void Data_WriteShorts(Data* Data){}
void Data_WriteInt(Data* Data){}
void Data_WriteInts(Data* Data){}
void Data_WriteLong(Data* Data){}
void Data_WriteLongs(Data* Data){}
void Data_WriteFloat(Data* Data){}
void Data_WriteFloats(Data* Data){}
void Data_WriteDouble(Data* Data){}
void Data_WriteDoubles(Data* Data){}
void Data_WriteUByte(Data* Data){}
void Data_WriteUBytes(Data* Data){}
void Data_WriteUShort(Data* Data){}
void Data_WriteUShorts(Data* Data){}
void Data_WriteUInt(Data* Data){}
void Data_WriteUInts(Data* Data){}
void Data_WriteULong(Data* Data){}
void Data_WriteULongs(Data* Data){}
