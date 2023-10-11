#include "TDALista.h"

int main(){

    TDAlista lista_1=crearListaVacia();

    insertarInicio(&lista_1, 4);
    insertarInicio(&lista_1, 1);
    insertarInicio(&lista_1, 3);
    insertarInicio(&lista_1, 2);

    TDAlista lista_2=crearListaVacia();

    insertarInicio(&lista_2, 4);
    insertarInicio(&lista_2, 1);
    insertarInicio(&lista_2, 3);
    insertarInicio(&lista_2, 2);

    bool equal = equalList(&lista_1, &lista_2);

    if(equal){
        printf("Son iguales\n");
    }else{
        printf("No son iguales\n");
    }

    return 0;
}