#include "math.h"

fxp32_16 gaussianQuadrature(fxp32_16 (*f) (fxp32_16), fxp32_16 a, fxp32_16 b)//returns the numerical integral of the function passed as its first parameter. 
{
    long long scale = (b-a) >> 1;
    fxp32_16 offset = (b+a) >> 1;

    static long abcissae[3]={0,-1663433681, 1663433681};
    static long weights[3]={1908874354, 1193046471, 1193046471};
    long long sum = 0;

    for(char i=0; i< 3; i++){
        long long x_val = ((scale * abcissae[i]) >> 31) + offset;
        sum += ((weights[i] * (f(x_val))) >> 31);//the function returns a 32 bit value, weights is 31 bits long, so we shift by that amount
    }

    return fxp_mul(sum, scale);
}

fxp32_16 slope_2point(fxp32_16 (*f)(fxp32_16), fxp32_16 x, fxp32_16 h){
    fxp32_16 two_h = h << 1;
    return fxp_div((f(x + h) - f(x - h)), two_h);
}
fxp32_16 slope_4point(fxp32_16 (*f)(fxp32_16), fxp32_16 x, fxp32_16 h){
    fxp32_16 two_h = h << 1;
    return fxp_div((((f(x - two_h) - (f(x - h) << 3) + (f(x+h) << 3) - f(x + two_h) )/two_h) >> 1), 3);
}
