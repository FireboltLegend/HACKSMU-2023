#include "screen.h"
#include "matrix.h"
#include "camera.h"
#include <stdio.h>


int main()
{
    int len, wid, hei;
    printf("Enter Length of Cuboid: ");
    scanf("%d", &len);
    printf("Enter Width of Cuboid: ");
    scanf("%d", &wid);
    printf("Enter Height of Cuboid: ");
    scanf("%d", &hei);

    Vector points[8];
    Vector_init(&(points[0]), 0,0,0,1);
    Vector_init(&(points[1]), len,0,0,1);
    Vector_init(&(points[2]), 0,wid,0,1);
    Vector_init(&(points[3]), 0,0,hei,1);
    Vector_init(&(points[4]), len,wid,0,1);
    Vector_init(&(points[5]), len,0,hei,1);
    Vector_init(&(points[6]), 0,wid,hei,1);
    Vector_init(&(points[7]), len,wid,hei,1);
    //setup camera details.
    Vector orientation, position;
    Vector_init(&orientation, 0, 32768, 0, 1);
    Vector_init(&position, 0, 655360, 0, 1);

    Matrix projection;
    Matrix_2DScreenProj(&projection, &orientation, &position);

    //rotate points:

    Matrix rotation;
    Matrix_rotate(&rotation, 32768/4, 2);
    Vector points2[8];
    for(int i = 0; i < 8; i++){
        Matrix_apply(&(points2[i]), &rotation, &(points[i]));
    }

    for(int i = 0; i < 8; i++){
        //normalize points:
        fxp_div(points2[i].a[0], points2[i].a[3]);
        fxp_div(points2[i].a[1], points2[i].a[3]);
        fxp_div(points2[i].a[2], points2[i].a[3]);
        fxp_div(points2[i].a[3], points2[i].a[3]);


        printf("(%d, %d, %d)\n", points2[i].a[0], points2[i].a[1], points2[i].a[2]);
    }
    
    return 0;
    
}