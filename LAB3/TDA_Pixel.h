#ifndef TDA_Pixel_h_
#define TDA_Pixel_h_

#include <stdio.h>

typedef struct TDA_Pixel{
    int posy_x;
    int pos_y;
    int color;

}pixel;

pixel crearPixel(int coordX, int coordY, int color);
void cambiarColorPixel(pixel* nuevo_pixel, int nuevoColor);
void trasladarHorizontalmentePixel(pixel* nuevo_pixel, int desplazamientoX);
void visualizarPIxel(pixel nuevo_pixel);

#endif