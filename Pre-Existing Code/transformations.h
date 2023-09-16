#ifndef transformations_h
#define transformations_h
#include "Vector.h"
#include "fxp32_16.h"
enum Axes {
	AXIS_X = 0, AXIS_Y, AXIS_Z
};
fxp32_16 Vector_length(Vector* v);
void Vector_normalize(Vector* dest, Vector* src);
void Trnsfm_rotateAroundVector(Matrix* dest, fxp32_16 angle, Vector* axis);//given a unit vector for an axis and an angle to rotate by, it returns a rotation matrix. It is slow. Use only when necessary.
void Trnsfm_scale(Matrix* dest, Vector* scaling);//teh vector stores how much to scale in each direction. It's a useful way to pass info is all.
void Trnsfm_slide(Matrix* dest, Vector* direction);
void Trnsfm_shear(Matrix* dest, char axis, Vector* resultantVector);//upon applying the transformation, the basis vector is shorn to the resultant vector
#endif
