#include "fxp32_16.h"
#include "Vector.h"

typedef struct {
    fxp32_16 elements[16];
} Matrix;

void Matrix_mul(Matrix* out, Matrix* a, Matrix* b);
void Matrix_add(Matrix* out, Matrix* a, Matrix* b);//Is safe to use destructively
void Matrix_neg(Matrix* out, Matrix* in);

void Matrix_rotation(Matrix* out, Vector* axis, fxp32_16 angle);
//void Matrix_reflect(Matrix* out, Vector* line, fxp32_16 bias);
void Matrix_translate(Matrix* out, Vector* path);
//void Matrix_shear(Matrix* out, Vector* newX, Vector* newY, Vector* newZ);

void Matrix_apply(Vector* out, Matrix* t, Vector* in);
//void Matrix_changeBasis(Matrix* out, Vector* newX, Vector* newY, Vector* newZ, Vector* newOrigin);

