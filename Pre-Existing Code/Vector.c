#include "Vector.h"
fxp32_16 Vector_length(Vector* v){
	fxp32_16* arr = v->a;
	long long sum = 0;
	for(char i = 0; i < 3; i++){
		sum += fxp_mul(arr[i], arr[i]);
	}
	return fxp_sqrt((fxp32_16)sum);
}
void Vector_normalize(Vector* dest, Vector* src){
	fxp32_16 len = Vector_length(src);
	for(char i = 0; i < 4; i++){
		dest->a[i] = fxp_div(src->a[i], len);
	}
}
void Vector_add(Vector* dest, Vector* a, Vector* b){
	for(char i = 0; i < 3; i++){
		dest->a[i] = a->a[i] + b->a[i];
	}
}
void Vector_sub(Vector* dest, Vector* a, Vector* b){
	for(char i = 0; i < 3; i++){
		dest->a[i] = a->a[i] - b->a[i];
	}
}
void Vector_scale(Vector* dest, Vector* a, fxp32_16 scaleFactor){
	long long scaleFactor_long = scaleFactor;
	for(char i = 0; i < 3; i++){
		dest->a[i] = fxp_mul(scaleFactor_long, a->a[i]);
	}
}

void Vector_init(Vector* a, fxp32_16 x, fxp32_16 y, fxp32_16 z, fxp32_16 w){	
	a->a[0] = x;
	a->a[1] = y;
	a->a[2] = z;
	a->a[3] = w;
}