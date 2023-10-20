#include "TDACola.h"

int main() {
    TDAlista* lista = crearListaVacia();

    encolar(lista, 2);
    encolar(lista, 3);
    encolar(lista, 4);

    printf("Primer elemento de la lista: %d\n", mirar(lista));

    printf("Desencolando elementos: %d\n", desencolar(lista));

    printf("Primer elemento de la lista despues de desencolar: %d\n", mirar(lista));

    free(lista);
    return 0;
}
