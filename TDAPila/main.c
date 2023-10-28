#include "TDAPila.h"

int main() {
    TDAPila lista = crearListaVacia(2);

    apilar(&lista, 9);
    apilar(&lista, 3);
    apilar(&lista, 7);
    apilar(&lista, 5);
    apilar(&lista, 6);
    apilar(&lista, 8);

    TDAPila lista_2 = ordenarPila(&lista);

    int encontrado = encontrarValor(&lista, 10);
    printf("valor: %d", encontrado);

    printf("Primer elemento de la TDAPila: %d\n", mirar(lista));

    TDAPila inversa = listaInversa(&lista);

    printf("Primer elemento de la TDAPila: %d\n", mirar(inversa));

    free(lista);
    return 0;
}
