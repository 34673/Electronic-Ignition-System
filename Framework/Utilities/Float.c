float Float_Clamp(float minimum,float maximum,float value){
    if(maximum < minimum || value < minimum){return minimum;}
    if(minimum > maximum || value > maximum){return maximum;}
    return value;
}
float Float_Lerp(float start,float end,float normalizedStep){
	return (1 - normalizedStep) * start + normalizedStep * end;
}
