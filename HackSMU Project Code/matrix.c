#include "matrix.h"

void Matrix_mul(Matrix* out, Matrix* a, Matrix* b){
  for(unsigned int i = 0; i < 4; i++){
    for(unsigned int k = 0; k < 4; k++){
      out->elements[4*i + k] = 0;
      for(unsinged int j = 0; j < 4; j++){
        out->elements[4*i + k] += fxp_mul(a->elements[4* i + j], b->elements[4*j + k]);
      }
    }
  }
}
void Matrix_add(Matrix* out, Matrix* a, Matrix* b){
  for(unsigned int i = 0;i < 16;i+=4){
    for(unsigned int j = 0;j < 4;j++){
        out->elements[i + j] = a->elements[i+j] + b->elements[i+j]; 
      }
  }//Is safe to use destructively
void Matrix_neg(Matrix* out, Matrix* in);

void Matrix_rotation(Matrix* out, Vector* axis, fxp32_16 angle);
void Matrix_reflect(Matrix* out, Vector* line, fxp32_16 bias);
void Matrix_translate(Matrix* out, Vector* path);
void Matrix_shear(Matrix* out, Vector* newX, Vector* newY, Vector* newZ);

void Matrix_apply(Vector* out, Matrix* t, Vector* in);
void Matrix_changeBasis(Matrix* out, Vector* newX, Vector* newY, Vector* newZ, Vector* newOrigin);
