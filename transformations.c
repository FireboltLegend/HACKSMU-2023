#include "transformations.h"

void Trnsfm_scale(Matrix* dest, Vector* scaling){
	fxp32_16* arr = &(dest->a[0]);
	arr[0] = scaling->a[0];//set the value to 1.
	arr[1] = 0;
	arr[2] = 0;
	arr[3] = 0;
	arr[4] = 0;
	arr[5] = scaling->a[1];
	arr[6] = 0;
	arr[7] = 0;
	arr[8] = 0;
	arr[9] = 0;
	arr[10] = scaling->a[2];
	arr[11] = 0;
	arr[12] = 0;
	arr[13] = 0;
	arr[14] = 0;
	arr[15] = fxp_UNITY;
}//teh vector stores how much to scale in each direction. It's a useful way to pass info is all.
void Trnsfm_slide(Matrix* dest, Vector* direction){
	fxp32_16* arr = &(dest->a[0]);
	arr[0] = fxp_UNITY;//set the value to 1.
	arr[1] = 0;
	arr[2] = 0;
	arr[3] = direction->a[0];
	arr[4] = 0;
	arr[5] = fxp_UNITY;
	arr[6] = 0;
	arr[7] = direction->a[1];
	arr[8] = 0;
	arr[9] = 0;
	arr[10] = fxp_UNITY;
	arr[11] = direction->a[2];
	arr[12] = 0;
	arr[13] = 0;
	arr[14] = 0;
	arr[15] = fxp_UNITY;
}
void Trnsfm_shear(Matrix* dest, char axis, Vector* resultantVector){
	fxp32_16* arr = &(dest->a[0]);
	arr[0] = fxp_UNITY;//set the value to 1.
	arr[1] = 0;
	arr[2] = 0;
	arr[3] = 0;
	arr[4] = 0;
	arr[5] = fxp_UNITY;
	arr[6] = 0;
	arr[7] = 0;
	arr[8] = 0;
	arr[9] = 0;
	arr[10] = fxp_UNITY;
	arr[11] = 0;
	arr[12] = 0;
	arr[13] = 0;
	arr[14] = 0;
	arr[15] = fxp_UNITY;

	for(unsigned char i = 0; i < 16; i+=4){
		arr[i + axis] = resultantVector->a[i];
	}//upon applying the transformation, the basis vector is shorn to the resultant vector
}

void Trnsfm_rotateAroundVector(Matrix* dest, fxp32_16 angle, Vector* axis){
	fxp32_16 sin = fxp_sin(angle, 3);
	fxp32_16 cos = fxp_UNITY - fxp_sin(32768 - angle, 3);
	Matrix W;
	W.a[0] = 0;
	W.a[1] = -axis->a[2];
	W.a[2] = axis->a[1];
	W.a[3] = 0;
	W.a[4] = axis->a[2];
	W.a[5] = 0;
	W.a[6] = -axis->a[0];
	W.a[7] = 0;
	W.a[8] = -axis->a[1];
	W.a[9] = axis->a[0];
	W.a[10] = 0;
	W.a[11] = 0;
	W.a[12] = 0;
	W.a[13] = 0;
	W.a[14] = 0;
	W.a[15] = fxp_UNITY;
	Vector_scale(axis, axis, cos);//scale the values by cosine.
	
	Matrix Y;
	Y.a[0] = sin;
	Y.a[1] = -axis->a[2];
	Y.a[2] = axis->a[1];
	Y.a[3] = 0;
	Y.a[4] = axis->a[2];
	Y.a[5] = sin;
	Y.a[6] = -axis->a[0];
	Y.a[7] = 0;
	Y.a[8] = -axis->a[1];
	Y.a[9] = axis->a[0];
	Y.a[10] = sin;
	Y.a[11] = 0;
	Y.a[12] = 0;
	Y.a[13] = 0;
	Y.a[14] = 0;
	Y.a[15] = fxp_UNITY;
	
	Matrix_mul(dest, &Y, &W);
	dest->a[0]++;
	dest->a[5]++;
	dest->a[10]++;
}
