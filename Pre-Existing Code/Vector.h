#ifndef Vector_h
#define Vector_h
#include "fxp32_16.h"
typedef struct{
	fxp32_16 a[4];
} Vector;

typedef struct{
	fxp32_16 a[16];
} Matrix;
fxp32_16 Vector_length(Vector* v);
void Vector_normalize(Vector* dest, Vector* src);
void Vector_add(Vector* dest, Vector* a, Vector* b);
void Vector_sub(Vector* dest, Vector* a, Vector* b);
void Vector_scale(Vector* dest, Vector* a, fxp32_16 scaleFactor);
void Matrix_mul(Matrix* dest, Matrix* a, Matrix* b);//cannot be used destructively
void Matrix_scale(Matrix* dest, Matrix* src, fxp32_16 scaling);
void Matrix_add(Matrix* dest, Matrix* a, Matrix* b);
void Matrix_sub(Matrix* dest, Matrix* a, Matrix* b);
void Matrix_transform(Vector* dest, Matrix* m, Vector* v);//cannot be used destructively
#endif
