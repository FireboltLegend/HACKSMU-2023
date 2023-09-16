#ifndef fxp32_16_h
#define fxp32_16_h

typedef int fxp32_16;
#define fxp_radixPoint (16)
#define fxp_UNITY (65536)
#define fxp32_16_from_int(x) (fxp_UNITY * ((fxp32_16)(x)))
#define fxp_mul(x,y) ((fxp32_16)((((long long)(x)) * (y)) >> fxp_radixPoint))
#define fxp_div(x,y) ((fxp32_16)((((long long)(x)) << fxp_radixPoint)/(y)))
#define fxp_lerp(a,b,t) (fxp_mul((((long long)fxp_UNITY) - (t)), a) + fxp_mul((b), (t)))
#define fxp_ilerp(a,b,v) (fxp_div((v) - (a), (v) - (b)))
#define fxp_linMap(input_min, input_max, output_min, output_max, val) (fxp_lerp((output_min), (output_max), (fxp_ilerp((input_min), (input_max), (val)))))

fxp32_16 fxp_sqrt(fxp32_16 x);
fxp32_16 fxp_sin(fxp32_16 x, char precision);
fxp32_16 fxp_tan(fxp32_16 x, char precision);

#endif
