#include "TDA_LD.h"

int main(){

    TDAlista listaA = crearListaVacia();

    insertarInicio(&listaA, 4);
    insertarNodoFinal(&listaA, 1);

    TDAlista listaB = crearListaVacia();

    insertarInicio(&listaB, 3);
    insertarNodoFinal(&listaB, 2);

    recorrerLista(listaA);
    recorrerLista(listaB);

    TDAlista listaC = append_list(listaA, listaB);

    recorrerLista(listaC);
    return 0;
}