#include "TDAPila.h"

int main() {
    TDAlista lista = crearListaVacia();

    apilar(&lista, 2);
    apilar(&lista, 3);
    apilar(&lista, 4);

    printf("Primer elemento de la TDAlista: %d\n", mirar(lista));

    printf("Desapilando elementos: %d\n", desapilar(&lista));

    printf("Primer elemento de la TDAlista: %d\n", mirar(lista));

    free(lista);
    return 0;
}
