#include <stdio.h>
#include "includes.h"
void uniform_motion(BezierCurve* curve, fxp32_16 step){
	printf("Points upon uniform animation: arc_length step: %.4f \n", step/65536.0);
	CumulativeLengthParametrizationTable table;
	BezierCurve_populateArcLengths(&table, curve);
	fxp32_16 arclength = 0;
	
	fxp32_16 totalArcLength = BezierCurve_arcLength(curve, fxp32_16_from_int(1));
	fxp32_16 t;
	printf("arcLength: %.4f \n", totalArcLength/65536.0);
	for(;arclength <= totalArcLength; arclength += step){
		t = BezierCurve_arcLengthParametrization(&table, arclength);	
		Vector v;
		BezierCurve_position(&v, curve, t);
		printf("%d, %d,\n", t, arclength - BezierCurve_arcLength(curve, t));
	}
}

void rotate_vector(Vector* v, Vector* axis){
	fxp32_16 angle_step = 65536/16;
	fxp32_16 angle = 0;
	printf("Rotation around axis <%.4f, %.4f, %.4f>:\n", axis->a[0]/65536.0, axis->a[1]/65536.0, axis->a[2]/65536.0);
	for(; angle < fxp32_16_from_int(1); angle+= angle_step){
		Matrix m;
		Trnsfm_rotateAroundVector(&m, angle, axis);
		Vector w;
		Matrix_transform(&w, &m, v);
		printf("<%.4f, %.4f, %.4f>\n", w.a[0]/65536.0, w.a[1]/65536.0, w.a[2]/65536.0);	
	}
}

int main(void){
	BezierCurve curve;
	curve.controlPoints[0].a[0] = 0;
	curve.controlPoints[0].a[1] = 0;
	curve.controlPoints[0].a[2] = 0;
	curve.controlPoints[0].a[3] = fxp32_16_from_int(1);

	curve.controlPoints[1].a[0] = 0;
	curve.controlPoints[1].a[1] = fxp32_16_from_int(-5);
	curve.controlPoints[1].a[2] = 0;
	curve.controlPoints[1].a[3] = 65536;

	curve.controlPoints[3].a[0] = fxp32_16_from_int(4);
	curve.controlPoints[3].a[1] = fxp32_16_from_int(5);
	curve.controlPoints[3].a[2] = 0;
	curve.controlPoints[3].a[3] = fxp32_16_from_int(1);

	curve.controlPoints[2].a[0] = fxp32_16_from_int(3);
	curve.controlPoints[2].a[1] = fxp32_16_from_int(-3);
	curve.controlPoints[2].a[2] = 0;
	curve.controlPoints[2].a[3] = fxp32_16_from_int(1);

	uniform_motion(&curve, 32768);
	fxp32_16 len = BezierCurve_arcLength(&curve, 32768);
	printf("%.4f", len/65536.0);
}
