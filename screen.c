#include "screen.h"

static int pixelAddress(Screen* scr, fxp32_16 x, fxp32_16 y){
    return ((((scr->height * y) & (~65536)) * scr->width) + ((scr->height * x) & (~65535))) >> 16;
}

static char getAscii(char brightness){
    const char* strArr = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
    return strArr[((255 - brightness) * 69)/256];
}

Screen* Screen_make(int w, int h){
    Screen* res = malloc(sizeof(Screen) + sizeof(char) * h * w);
    res->height = h;
    res->width = w;
    return res;
}

void Screen_delete(Screen* scr){
    free(scr);
}

void Screen_point(Screen* scr, fxp32_16 x, fxp32_16 y, fxp32_16 brightness){
    int index = pixelAddress(scr, x, y);
    scr->pixels[index] = brightness >> 8;
}
void Screen_clear(Screen* scr){
    int numPixels = scr->height * scr->width;
    for(int i = 0; i < numPixels; i++){
        scr->pixels[i] = 0;
    }
}
void Screen_show(Screen* scr){
    for(int i = 0; i < scr->height; i++){
        for(int j = 0; j < scr->width; j++){
            printf("%c", getAscii(scr->pixels[i * scr->width + j]));
        }
        printf("%c", '\n');
    }
}