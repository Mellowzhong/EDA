#include <stdio.h>
#include <stdlib.h>

typedef struct nodoGenerico{
  int dato;
  struct nodoGenerico* puntero;
}nodo;

typedef nodo* TDAlista;

TDAlista crearListaVacia(){
  TDAlista lista=(TDAlista)malloc(sizeof(TDAlista));
  lista = NULL;
  return lista;
}

int esListaVacia(TDAlista lista){
  if (lista == NULL){

    return 1;
  }else{

    return 0;
  }
}

void apilar(TDAlista* lista, int dato){
  nodo* nuevo=(nodo*)malloc(sizeof(nodo));
  nuevo->dato=dato;
  nuevo->puntero=*lista;
  *lista=nuevo;
}

int desapilar(TDAlista* lista) {
  if (!esListaVacia(*lista)) {
    nodo* aux = *lista;
    int dato = aux->dato;
    *lista = (*lista)->puntero;
    free(aux);
    return dato;
  }else{
    printf("La pila esta vacia\n");
    return -1;
  }

}

int mirar(TDAlista lista) {
  if (!esListaVacia(lista)) {
    nodo* aux = lista;
    return aux->dato;
  }else{
    printf("No hay nada en la pila\n");
    return -1;
  }
}