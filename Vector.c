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
void Matrix_mul(Matrix* dest, Matrix* a, Matrix* b){
	for(char i = 0; i < 16; i+= 4){
		for(char j = 0; j < 4; j++){
			dest->a[i + j] = 0;
			for(char k = 0; k < 4; k++){
				dest->a[i + j] += fxp_mul(a->a[i + k], b->a[(k << 2) + j]);
			}
		}
	}
}//cannot be used destructively
void Matrix_scale(Matrix* dest, Matrix* src, fxp32_16 scaleFactor){
	long long scaleFactor_long = scaleFactor;	
	for(char i = 0; i < 16; i++){
		dest->a[i] = fxp_mul(scaleFactor_long, src->a[i]);	
	}
}
void Matrix_add(Matrix* dest, Matrix* a, Matrix* b){
	for(char i = 0; i < 16; i++){
		dest->a[i] = a->a[i] + b->a[i];	
	}
}
void Matrix_sub(Matrix* dest, Matrix* a, Matrix* b){
	for(char i = 0; i < 16; i++){
		dest->a[i] = a->a[i] - b->a[i];	
	}
}
void Matrix_transform(Vector* dest, Matrix* m, Vector* v){
	v->a[3] = 65536;
	for(char i = 0; i < 12; i+=4){
		dest->a[i] = 0;
		for(char j = 0; j < 4; j++){
			dest->a[i >> 2] += fxp_mul(m->a[i + j], v->a[j]);
		}
	}
	dest->a[3] = 65536;
}//cannot be used destructively
