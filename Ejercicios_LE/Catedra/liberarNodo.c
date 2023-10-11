#include <stdio.h>
#include <stdlib.h>
#include "TDALista.h"

int main(){
  TDAlista lista=crearListaVacia();

  insertarInicio(&lista, 4);
  insertarInicio(&lista, 1);
  insertarInicio(&lista, 3);
  insertarInicio(&lista, 2);

  //Actividad 1
  int nodos = obtenerNumNodos(lista);
  printf("cantidad nodos:%d\n", nodos);

  //Actividad 2
  int dato = buscarDatoLista(lista, 7);
  printf("dato buscado : %d\n", dato);

  //Actividad 3
  insertarNodoFinal(&lista, 7);
  insertarNodoDespues(&lista, 5, 1);

  //Actividad 4
  eliminarFinal(&lista);
  eliminarDato(&lista, 3);

  //Actividad 5
  nodo* nuevo = obtenerNodo(lista, 2);
  printf("el dato es: %d\n", nuevo->dato);

  liberarLista(&lista, nodos);

  recorrerLista(lista);
  return 1;
}