#include "TDACola.h"

int main() {
    TDAcola* lista = crearColaVacia(3);

    encolar(lista, 1);
    encolar(lista, 3);
    encolar(lista, 2);

    imprimirCola(lista);

    TDAcola* lista2 = invertirCola(lista);
    imprimirCola(lista2);
    free(lista);
    return 0;
}
