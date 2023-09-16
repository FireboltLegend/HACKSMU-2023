#include "camera.h"

void Matrix_2DScreenProj(Matrix* projMatrix, Matrix* CameraCoordinates){
  Matrix basisChange;
  Matrix_changeBasis(&basisChange,
    (Vector*)&CameraCoordinates->elements[0], 
    (Vector*)&CameraCoordinates->elements[4],
    (Vector*)&CameraCoordinates->elements[8],
    (Vector*)&CameraCoordinates->elements[12] 
  )

  Matrix_mul(projMatrix, [], &basisChange, 3, 4, 4)

  
  
}

void Matrix_PerspectiveTransform(Vector* out, Vector* in){
  
}, 
