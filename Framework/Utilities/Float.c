float Float_Clamp(float value,float minimum,float maximum){
	if(maximum < minimum || value < minimum){return minimum;}
	if(minimum > maximum || value > maximum){return maximum;}
	return value;
}
float Float_Lerp(float start,float end,float normalizedStep){
	return (1 - normalizedStep) * start + normalizedStep * end;
}
float Float_Normalize(float value,float minimum,float maximum){
	return (value - minimum) / (maximum - minimum);
}
