#ifndef Vector_h
#define Vector_h
#include "fxp32_16.h"
typedef struct{
	fxp32_16 a[4];
} Vector;

fxp32_16 Vector_length(Vector* v);
void Vector_normalize(Vector* dest, Vector* src);
void Vector_add(Vector* dest, Vector* a, Vector* b);
void Vector_sub(Vector* dest, Vector* a, Vector* b);
void Vector_scale(Vector* dest, Vector* a, fxp32_16 scaleFactor);
void Vector_init(Vector* a, fxp32_16 x, fxp32_16 y, fxp32_16 z, fxp32_16 w);

#endif