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

  Matrix_mul(projMatrix, &rz, &t, 4,4,4);
  Matrix_mul(&t, &ry, projMatrix,4,4,4);
  Matrix_mul(&rz, &rx, &t,4,4,4);

  Matrix* k = (Matrix*)cameraTransform;
  Matrix_mul(projMatrix, cameraTransform, &rz, 3, 4, 4);

  for(int i = 0; i < 16; i++){
    projMatrix->elements[i] = rz.elements[i];
  }
}