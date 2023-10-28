#include <stdio.h>
#include <stdlib.h>

typedef struct nodoGenerico{
  int dato;
  struct nodoGenerico* puntero;
}nodo;

typedef nodo* TDAPila;

TDAPila crearListaVacia(int n){
  TDAPila lista=(TDAPila)malloc(sizeof(TDAPila));
  lista = NULL;
  return lista;
}

int esListaVacia(TDAPila lista){
  if (lista == NULL){
    return 1;
  }else{
    return 0;
  }
}

void apilar(TDAPila* lista, int dato){
  nodo* nuevo=(nodo*)malloc(sizeof(nodo));
  nuevo->dato=dato;
  nuevo->puntero=*lista;
  *lista=nuevo;
}

int desapilar(TDAPila* lista) {
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

int mirar(TDAPila lista) {
  if (!esListaVacia(lista)) {
    nodo* aux = lista;
    return aux->dato;
  }else{
    printf("No hay nada en la pila\n");
    return -1;
  }
}

TDAPila listaInversa(TDAPila* lista){
  int n = 2;
  TDAPila inicio=crearListaVacia(n);
  while(!esListaVacia(*lista)){
    apilar(&inicio, (*lista)->dato);
    desapilar(lista);
  }
  return inicio;
}

void imprimirCola(TDAPila* cola) {
    nodo* actual = *cola;
    while (actual != NULL) {
        printf("%d -> ", actual->dato);
        actual = actual->puntero;
    }
    printf("NULL\n");
}

int encontrarValor(TDAPila* lista, int v){
  int n = 2;
  TDAPila inicio = crearListaVacia(n);
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
TDAPila ordenarPila(TDAPila* lista){
  int n = 2;
  TDAPila listaAux = crearListaVacia(n);
  TDAPila listaFinal = crearListaVacia(n);
  
}

//Ejercicio 5
TDAPila eliminarRepetidos(TDAPila* lista){
  int n = 2;
  TDAPila listaAux = crearListaVacia(n);

}