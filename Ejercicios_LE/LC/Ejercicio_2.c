#include "TDA_LC.h"

int main(){

    TDAlista listaA = crearListaVacia();

    insertarInicio(&listaA, 4);
    insertarNodoFinal(&listaA, 1);
    insertarNodoFinal(&listaA, 3);
    insertarNodoFinal(&listaA, 2);

    recorrerLista(listaA);
    return 0;
}