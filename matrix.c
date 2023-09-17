#include "matrix.h"

void Matrix_mul(Matrix* out, Matrix* a, Matrix* b, int rowa, int cola, int colb){
  for(unsigned int i = 0; i < rowa; i++){
    for(unsigned int k = 0; k < colb; k++){
      out->elements[4*i + k] = 0;
      for(unsigned int j = 0; j < cola; j++){
        out->elements[4*i + k] += fxp_mul(a->elements[4* i + j], b->elements[4*j + k]);
      }
    }
  }
}
void Matrix_add(Matrix* out, Matrix* a, Matrix* b, int rows, int cols){
  for(unsigned int i = 0; i < rows; i++)
    for(unsigned int j = 0; j < cols; j++)
      out->elements[4*i + j] = a->elements[4*i+j] + b->elements[4*i+j]; 

}//Is safe to use destructively
void Matrix_neg(Matrix* out, Matrix* in, int rows, int cols){
  for(unsigned int i = 0; i < rows; i++)
    for(unsigned int j = 0; j < cols; j++)
      out->elements[4*i + j] = -(in->elements[4*i+j]);
}

//void Matrix_rotationAroundAxis(Matrix* out, Vector* axis, fxp32_16 angle){}

void Matrix_rotate(Matrix* out, fxp32_16 angle, char axis){
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      if(i == j){
        out->elements[4*i + j] = 65536;
      }
      else{
        out->elements[4*i + j] = 0;
      }
    }
  }

  angle = -angle;
  fxp32_16 cos = fxp_sin(32768 - angle, 20);
  fxp32_16 sin = fxp_sin(angle, 20);
  if(axis == 0){
    out->elements[5] = cos;
    out->elements[6] = sin;
    out->elements[9] = -sin;
    out->elements[10] = cos;
  }
  else if(axis == 1){
    out->elements[0] = cos;
    out->elements[2] = -sin;
    out->elements[8] = sin;
    out->elements[10] = cos;
  }
  else{
    out->elements[0] = cos;
    out->elements[1] = sin;
    out->elements[4] = -sin;
    out->elements[5] = cos;
  }
}
//void Matrix_reflect(Matrix* out, Vector* line, fxp32_16 bias);
void Matrix_translate(Matrix* out, Vector* path){
  for(int i = 0; i < 16; i++){
    out->elements[i] = 0;
  }
  out->elements[0] = 65536;
  out->elements[5] = 65536;
  out->elements[10] = 65536;
  out->elements[15] = 65536;

  out->elements[3] = path->a[0];
  out->elements[7] = path->a[1];
  out->elements[11] = path->a[2];
}
//void Matrix_shear(Matrix* out, Vector* newX, Vector* newY, Vector* newZ);

void Matrix_apply(Vector* out, Matrix* t, Vector* in){
  for(int i = 0; i < 4; i++){
    out->a[i] = 0;
    for(int j = 0; j < 4; j++){
      out->a[i] += fxp_mul(t->elements[4*i + j], in->a[j]);
    }
  }
}
//void Matrix_changeBasis(Matrix* out, Vector* newX, Vector* newY, Vector* newZ, Vector* newOrigin){}
