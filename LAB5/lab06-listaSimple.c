#include "TDAlista.h"

int main(){
    TDAlista lista = crearListaVacia();

    insertarInicio(&lista, 4);
    insertarInicio(&lista, 1);
    insertarInicio(&lista, 3);
    insertarInicio(&lista, 2);

    printf("lista1\n");
    recorrerLista(lista);

    TDAlista lista_2 = sumaVecinos(lista);
    
    printf("lista2 (vecinos)\n");
    recorrerLista(lista_2);

    if(compararListas(&lista, &lista_2)){

        printf("Son iguales\n");
    }else{

        printf("No son iguales\n");
    }

    TDAlista lista_3 = ListaInversa(&lista_2);

    printf("lista2 inversa\n");
    recorrerLista(lista_3);

    printf("elementos cambiados\n");
    elementosCambiados(&lista, 2 , 4);
    recorrerLista(lista);

    liberarLista(&lista);

    printf("lista1 liberada\n");
    recorrerLista(lista);

    return 0;
}