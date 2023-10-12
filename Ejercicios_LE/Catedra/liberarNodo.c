#include "TDALista.h"

int main(){
  TDAlista lista=crearListaVacia();

  insertarInicio(&lista, 4);
  insertarInicio(&lista, 1);
  insertarInicio(&lista, 3);
  insertarInicio(&lista, 2);

  int nodos = obtenerNumNodos(lista);

  liberarLista(&lista, nodos);

  recorrerLista(lista);
  return 1;
}