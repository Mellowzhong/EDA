#include "TDACola.h"

int main() {
    TDAlista* lista = crearListaVacia();

    encolar(lista, 2);
    encolar(lista, 3);
    encolar(lista, 2);

    TDAlista* lista_2 = cambiarOcurrencias(lista, 2, 10);

    printf("Primer elemento de la lista: %d\n", mirar(lista_2));

    printf("Desencolando elementos: %d\n", desencolar(lista_2));

    printf("Primer elemento de la lista despues de desencolar: %d\n", mirar(lista_2));

    free(lista);
    return 0;
}
