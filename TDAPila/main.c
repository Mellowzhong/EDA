#include "TDAPila.h"

int main() {
    TDAlista lista = crearListaVacia();

    apilar(&lista, 9);
    apilar(&lista, 3);
    apilar(&lista, 7);
    apilar(&lista, 5);
    apilar(&lista, 6);
    apilar(&lista, 8);

    TDAlista lista_2 = ordenarPila(&lista);

    int encontrado = encontrarValor(&lista, 10);
    printf("valor: %d", encontrado);

    printf("Primer elemento de la TDAlista: %d\n", mirar(lista));

    TDAlista inversa = listaInversa(&lista);

    printf("Primer elemento de la TDAlista: %d\n", mirar(inversa));

    free(lista);
    return 0;
}
