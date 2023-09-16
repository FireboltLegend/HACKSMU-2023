#include "Bezier.h"
#include <math.h>

static void polynomial_evaluate(Vector *result, fxp32_16 t, const fxp32_16 *polynomialArray)
{
    const char arr_side = 4;
    for (char i = 0; i < arr_side; i++)
    {
        fxp32_16 sum = polynomialArray[i * arr_side];
        for (char j = 1; j < arr_side; j++)
        {
            sum = fxp_mul(sum, t);
            sum += polynomialArray[i * arr_side + j];
        }
		  result->a[i] = sum;
    }
}

void BezierCurve_position(Vector *result, BezierCurve *curve, fxp32_16 t)
{
    /**
     * Bernstein polynomial => {
     *      P0(-1t3, 3t2, -3t, 1)
     *      P1(3t3, -6t2, 3t, 0)
     *      P2(-1t3, 3t2, 0, 0)
     *      P3(1t3, 0, 0, 0)
     *  }
     */
    static const fxp32_16 table[] = {-1 * 65536,  3 * 65536, -3 * 65536,  1 * 65536,
		 										  3 * 65536, -6 * 65536,  3 * 65536,  0, 
												 -3 * 65536,  3 * 65536,  0,          0, 
												  1 * 65536,  0,          0,          0};
    // the table is flattened
	 Vector bernsteinCoefficients;
    polynomial_evaluate(&bernsteinCoefficients, t, table);

	 Vector scaledPoint;
	 Vector_scale(result, &(curve->controlPoints[0]), bernsteinCoefficients.a[0]);
	 for(char i = 1; i < 4; i++){
	 	Vector_scale(&scaledPoint, &(curve->controlPoints[i]), bernsteinCoefficients.a[i]);
	 	Vector_add(result, result, &scaledPoint);
	 }
}

void BezierCurve_velocity(Vector *result, BezierCurve *curve, fxp32_16 t)
{
    /**
     * Bernstein polynomial => {
     *      P0(0t3, -3t2, 6t, -3)
     *      P1(0t3, 9t2, -12t, 3)
     *      P2(0t3, -3t2, 6t, 0)
     *      P3(0t3, 3t2, 0t, 0)
     *  }
     */
    static const fxp32_16 table[] = {0, -3 * 65536, 6 * 65536  , -3 * 65536,
                                     0,  9 * 65536, -12 * 65536,  3 * 65536,
                                     0, -9 * 65536, 6 * 65536  ,  0        ,
                                     0,  3 * 65536, 0          ,          0};
	 Vector bernsteinCoefficients;
    polynomial_evaluate(&bernsteinCoefficients, t, table);

	 Vector scaledPoint;
	 Vector_scale(result, &(curve->controlPoints[0]), bernsteinCoefficients.a[0]);
	 for(char i = 1; i < 4; i++){
	 	Vector_scale(&scaledPoint, &(curve->controlPoints[i]), bernsteinCoefficients.a[i]);
	 	Vector_add(result, result, &scaledPoint);
	 }
}

void BezierCurve_acceleration(Vector *result, BezierCurve *curve, fxp32_16 t)
{
    /**
     * Bernstein polynomial => {
     *      P0(0, 0, -6t, 6 )
     *      P1(0, 0, 18t, -12 )
     *      P2( 0, 0 ,-6t, 6)
     *      P3(0, 0, 6t, 0 )
     *  }
     */
    static const fxp32_16 table[] = {0, 0, -6 * 65536,  6 * 65536, 
                                     0, 0, 18 * 65536, -12 * 65536, 
                                     0, 0, -18 * 65536,  6 * 65536,
                                     0, 0,  6 * 65536,  0 };
	 Vector bernsteinCoefficients;
    polynomial_evaluate(&bernsteinCoefficients, t, table);

	 Vector scaledPoint;
	 Vector_scale(result, &(curve->controlPoints[0]), bernsteinCoefficients.a[0]);
	 for(char i = 1; i < 4; i++){
	 	Vector_scale(&scaledPoint, &(curve->controlPoints[i]), bernsteinCoefficients.a[i]);
	 	Vector_add(result, result, &scaledPoint);
	 }
}

void BezierCurve_Jolt(Vector *result, BezierCurve *curve, fxp32_16 t)
{
    /**
     * Bernstein polynomial => {
     *      P0(0, 0, 0 -6 )
     *      P1(0, 0, 0, 18 )
     *      P2( 0, 0 ,0, -6)
     *      P3(0, 0, 0, 6  )
     *  }
     */
    static const fxp32_16 table[] = {0, 0, 0, -6 * 65536, 
                                     0, 0, 0, -18 * 65536, 
                                     0, 0, 0, -18 * 65536,
                                     0, 0, 0,  6 * 65536};
	 Vector bernsteinCoefficients;
    polynomial_evaluate(&bernsteinCoefficients, t, table);

	 Vector scaledPoint;
	 Vector_scale(result, &(curve->controlPoints[0]), bernsteinCoefficients.a[0]);
	 for(char i = 1; i < 4; i++){
	 	Vector_scale(&scaledPoint, &(curve->controlPoints[i]), bernsteinCoefficients.a[i]);
	 	Vector_add(result, result, &scaledPoint);
	 }
}


fxp32_16 BezierCurve_arcLength(BezierCurve *curve, fxp32_16 t) {
    //this is the gaussian quadrature method. It interpolates a 5th degree polynomial through teh curve, and returns its integral.
    long long scale = (t) >> 1;
    fxp32_16 offset = (t) >> 1;

    static const long long abcissae[3] = {0,-831716840, 831716840};
    static const long long weights[3] = {954437177,  596523236,  596523236};
    long long sum = 0;
    for(char i = 0; i < 3; i++){
        long long x_val = (scale * abcissae[i] >> 30) + offset;
		  Vector v;
		  BezierCurve_velocity(&v, curve, x_val);
		  fxp32_16 len = Vector_length(&v);
        sum += ((weights[i] * len) >> 30);//the function returns a 32 bit value, weights is 31 bits long, so we shift by that amount
    }

    return (sum* scale) >> 16;
}

fxp32_16 BezierCurve_arcLengthParametrization(CumulativeLengthParametrizationTable *table, fxp32_16 s) {
    fxp32_16 lower = fxp32_16_from_int(0);
    fxp32_16 upper = fxp32_16_from_int(1);
	 fxp32_16 middle = fxp32_16_from_int(1)/2;
    while(upper - lower > 4096){
        if(table->values[middle >> 12] < s){
            lower = middle;  
        }
        else if(s < table->values[middle >> 12]){
            upper = middle;
        }
        else{
            return middle;//return the correspondign t_value if it equals what we want.
        }
        middle = (upper + lower) >> 1;
    }
    
    fxp32_16 s_upper = table->values[upper >> 12];
    fxp32_16 s_lower = table->values[lower >> 12];
    
    return lower + ((fxp_div(s - s_lower, s_upper - s_lower)) >> 4); 
}

void BezierCurve_populateArcLengths(CumulativeLengthParametrizationTable *table, BezierCurve *curve) {
    fxp32_16 dt = fxp32_16_from_int(1) >> 4;//take 1/16 as a step size;
    fxp32_16 t = dt;
    table->values[0] = 0;
    for (int i = 1; i <= 16; i++) {
        table->values[i] = BezierCurve_arcLength(curve, t);
        t += dt;
    }
	 table->start = 0;
	 table->end = fxp32_16_from_int(1);

/*		
	table->values[0] = 0;
	Vector lastPoint;
	Vector currentPoint;
	Vector w;
	BezierCurve_position(&lastPoint, curve, 0);
	for(fxp32_16 t = 4096; t <= 65536; t += 4096){
		BezierCurve_position(&currentPoint, curve, t);
		Vector_sub(&w, &currentPoint, &lastPoint);//
		table->values[t >> 12] = table->values[(t >> 12) - 1] + Vector_length(&w);//add the length of the difference vector to the next entry.
		Vector_scale(&lastPoint, &currentPoint, 65536);//copy current point to last point.
	}
*/
}

void BezierCurve_tangent(Vector *result, BezierCurve *curve, fxp32_16 t) {
    BezierCurve_velocity(result, curve, t);
    Vector_normalize(result, result);
}

