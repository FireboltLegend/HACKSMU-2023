#ifndef math_h
#define math_h

#include "fxp32_16.h"
fxp32_16 gaussianQuadrature(fxp32_16 (*f)(fxp32_16), fxp32_16 a, fxp32_16 b);//returns the numerical integral of the function passed as its first parameter. 
fxp32_16 slope_2point(fxp32_16 (*f)(fxp32_16), fxp32_16 x, fxp32_16 h);//central divided difference. 
fxp32_16 slope_4point(fxp32_16 (*f)(fxp32_16), fxp32_16 x, fxp32_16 h);//4 point central divided difference. This is very precise. all dp of precision is maintained. for locally smooth functions.

#endif
