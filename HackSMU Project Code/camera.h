#include "fxp32_16.h"
#include "matrix.h"

void Matrix_2DScreenProj(Matrix* out, Matrix* CameraCoordinates);
void Matrix_PerspectiveTransform(Vector* out, Vector* in);
