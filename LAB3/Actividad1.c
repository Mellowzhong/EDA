#include "TDA_Pixel.h"

int main(){

    pixel nuevo_pixel = crearPixel(1,2, 3);

    cambiarColorPixel(&nuevo_pixel, 4);
    trasladarHorizontalmentePixel(&nuevo_pixel, -1);
    visualizarPIxel(nuevo_pixel);

    return 0;
}