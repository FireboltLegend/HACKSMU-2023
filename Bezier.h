#include "fxp32_16.h"
#include "Vector.h"
#include "math.h"

typedef struct
{
	Vector controlPoints[4];
} BezierCurve;
typedef struct
{
	fxp32_16 start;
	fxp32_16 end; // the implied step is 1/16 of the difference between start and end.
	fxp32_16 values[17];
} CumulativeLengthParametrizationTable;

void BezierCurve_position(Vector *result, BezierCurve *curve, fxp32_16 t);
void BezierCurve_velocity(Vector *result, BezierCurve *curve, fxp32_16 t);
void BezierCurve_acceleration(Vector *result, BezierCurve *curve, fxp32_16 t);
void BezierCurve_jolt(Vector *result, BezierCurve *curve, fxp32_16 t);

fxp32_16 BezierCurve_arcLength(BezierCurve *curve, fxp32_16 t);				   // uses numerical integration techniques to compute arclength
fxp32_16 BezierCurve_arcLengthParametrization(CumulativeLengthParametrizationTable *table, fxp32_16 s); // taking in a parameter s, representing how much distance along the curve, we return the corresponding curve parameter t
void BezierCurve_populateArcLengths(CumulativeLengthParametrizationTable *table, BezierCurve *curve);
void BezierCurve_tangent(Vector *result, BezierCurve *curve, fxp32_16 t);
