int Int_Within(int current,int minimum,int maximum){
	return current > minimum && current < maximum;
}
int Int_Clamp(int value,int minimum,int maximum){
	if(maximum < minimum || value < minimum){return minimum;}
	if(minimum > maximum || value > maximum){return maximum;}
	return value;
	}
int Int_Lerp(int start,int end,float normalizedStep){
	return (1 - normalizedStep) * start + normalizedStep * end;
}
