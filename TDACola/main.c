#include "TDACola.h"

int main(){
    TDAlista* lista = crearListaVacia();

    encolar(lista, 3);
    encolar(lista, 4);
    recorrerLista(*lista);

    int nodos = obtenerNumNodos(*lista);
    printf("nodos: %d", nodos);
    return 0;
}