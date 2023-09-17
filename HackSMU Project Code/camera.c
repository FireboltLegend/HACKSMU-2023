#include "camera.h"
#define focalLength 100000
static fxp32_16 cameraTransform[16] = {
  focalLength,  0,            0,      0,
  0,            focalLength,  0,      0,
  0,            0,            65536,  0,
  0,            0,            0,      0
};

void Matrix_2DScreenProj(Matrix* projMatrix, Vector* cameraOrientation, Vector* cameraPosition){//orientation is given as 3 different angles
  Matrix t; Vector v;
  Vector_scale(&v, cameraPosition, -65536);
  Matrix_translate(&t, &v);

  Matrix rx, ry, rz;
  Matrix_rotate(&rz, cameraOrientation->a[2], 2);
  Matrix_rotate(&ry, cameraOrientation->a[1], 1);
  Matrix_rotate(&rx, cameraOrientation->a[0], 0);

  // p = rx * ry * rz * t

  Matrix_mul(projMatrix, &rz, &t);
  Matrix_mul(&t, &ry, projMatrix);
  Matrix_mul(&rz, &rx, &t);

  for(int i = 0; i < 16; i++){
    projMatrix->elements[i] = rz.elements[i];
  }
}