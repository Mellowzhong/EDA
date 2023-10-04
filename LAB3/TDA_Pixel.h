#ifndef TDA_Pixel_h
#define TDA_Pixel_h

#include <stdio.h>

typedef struct TDA_Pixel{
    int posy_x;
    int pos_y;
    int color;

}pixel;

//Dom: coordenada x del nuevo pixel - coordenada y del nuevo pixel - color del nuevo pixel
//Rec: pixel con las corrdenadas y el color asignado
//Descripcion: Crea un nuevo pixel con los datos dados
pixel crearPixel(int coordX, int coordY, int color){

    pixel nuevo_pixel;

    nuevo_pixel.posy_x = coordX;
    nuevo_pixel.pos_y = coordY;
    nuevo_pixel.color = color;

    return nuevo_pixel;
}

//Dom: pixel a cambiar - nuevo color del pixel
//Rec: void
//Descripcion: Cambia el color del pixel dado
void cambiarColorPixel(pixel* nuevo_pixel, int nuevoColor){
    nuevo_pixel->color = nuevoColor;
}

//Dom: pixel a cambiar - numero de desplazamientos
//Rec: void
//Descripcion: Traslada una cantidad de posiciones en la coordenada x al pixel
void trasladarHorizontalmentePixel(pixel* nuevo_pixel, int desplazamientoX){
    nuevo_pixel->posy_x = nuevo_pixel->posy_x + desplazamientoX;
}

//Dom: pixel a mostrar
//Rec: void
//Descripcion: Muestra en pantalla la coordenada x e y del pixel, ademas del color
void visualizarPIxel(pixel nuevo_pixel){
    printf("posicion x: %d, posicion y: %d, color: %d", nuevo_pixel.posy_x, nuevo_pixel.pos_y, nuevo_pixel.color);
}

#endif