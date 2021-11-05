typedef enum{Baked,Blended,Logarithmic,MaxMapType};
typedef struct{
	char mode;
	int dataSize;
	short valuesCount;
	Values* values;
}Map;
typedef struct{
	short rpm;
	char advance;
}Values;
