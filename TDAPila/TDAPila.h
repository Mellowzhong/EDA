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

TDAlista listaInversa(TDAlista* lista){
  TDAlista inicio=crearListaVacia();
  while(!esListaVacia(*lista)){
    apilar(&inicio, (*lista)->dato);
    desapilar(lista);
  }
  return inicio;
}

void imprimirCola(TDAlista* cola) {
    nodo* actual = *cola;
    while (actual != NULL) {
        printf("%d -> ", actual->dato);
        actual = actual->puntero;
    }
    printf("NULL\n");
}

int encontrarValor(TDAlista* lista, int v){
  TDAlista inicio = crearListaVacia();
  int encontrado = 0;
  while (!esListaVacia(*lista)){
    int dato = (*lista)->dato;
    apilar(&inicio, dato);
    if(dato == v){
      encontrado = 1;
    }
    desapilar(lista);
  }
  while (!esListaVacia(inicio)){
    apilar(lista, inicio->dato);
    desapilar(&inicio);
  }

  return encontrado;
}

//Ejercicio 4
TDAlista ordenarPila(TDAlista* lista){
  TDAlista listaAux = crearListaVacia();
  TDAlista listaFinal = crearListaVacia();
  
}

//Ejercicio 5
TDAlista eliminarRepetidos(TDAlista* lista){

}