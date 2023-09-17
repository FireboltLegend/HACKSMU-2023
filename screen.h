#ifndef screen_h
#define screen_h
#include "fxp32_16.h"

typedef struct {
    int height;
    int width;
    char pixels[];
} Screen;


//module interface
Screen* Screen_make(int w, int h);
Screen* Screen_delete(Screen* scr);
void Screen_point(Screen* scr, fxp32_16 x, fxp32_16 y, fxp32_16 brightness);
void Screen_clear(Screen* scr);
void Screen_show(Screen* scr);

#endif