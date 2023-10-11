#include "TDALista.h"

int main(){

    TDAlista lista_1=crearListaVacia();

    insertarInicio(&lista_1, 4);
    insertarInicio(&lista_1, 1);
    insertarInicio(&lista_1, 3);
    insertarInicio(&lista_1, 2);

    recorrerLista(lista_1);

    invertirList(&lista_1);

    recorrerLista(lista_1);
    return 0;
}