#include "TDAlista.h"

int main(){
    TDAlista lista=crearListaVacia();

    insertarInicio(&lista, 4);
    insertarInicio(&lista, 1);
    insertarInicio(&lista, 3);
    insertarInicio(&lista, 2);

    TDAlista lista_2 = sumaVecinos(lista);

    TDAlista lista_3 = listOrder(lista,lista_2);
    recorrerLista(lista);
    recorrerLista(lista_2);
    recorrerLista(lista_3);
    return 0;
}