#ifndef camera_h
#define camera_h
#include "fxp32_16.h"
#include "matrix.h"

void Matrix_2DScreenProj(Matrix* out, Vector* orientation, Vector* position);

#endif