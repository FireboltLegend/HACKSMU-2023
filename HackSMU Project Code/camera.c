#include "camera.h"
#define focalLength 100000
static fxp32_16 cameraTransform[16] = {
  focalLength,  0,            0,      0,
  0,            focalLength,  0,      0,
  0,            0,            65536,  0,
  0,            0,            0,      0
};

void Matrix_2DScreenProj(Matrix* projMatrix, Matrix* CameraCoordinates){
  Matrix basisChange;
  Matrix_changeBasis(&basisChange,
    (Vector*)&CameraCoordinates->elements[0], 
    (Vector*)&CameraCoordinates->elements[4],
    (Vector*)&CameraCoordinates->elements[8],
    (Vector*)&CameraCoordinates->elements[12] 
  );

  Matrix_mul(projMatrix, (Matrix*)&cameraTransform, &basisChange, 3, 4, 4);
}