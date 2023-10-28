#include <stdio.h>
#include <stdlib.h>
#include "TDApila.h"

int main()
{
  TDApila* pila = crearPilaVacia(8);
  nodo* nodoTope ;

  apilar(pila, 2);
  apilar(pila, 6);
  apilar(pila, 9);
  apilar(pila, 5);
  apilar(pila, 8);

  nodoTope = tope(pila);
  printf("el primer elemento es: %d\n", nodoTope->dato);

  desapilar(pila);
  nodoTope = tope(pila);
  printf("el primer elemento es: %d\n", nodoTope->dato);

  desapilar(pila);
  nodoTope = tope(pila);
  printf("el primer elemento es: %d\n", nodoTope->dato);

  desapilar(pila);
  nodoTope = tope(pila);
  printf("el primer elemento es: %d\n", nodoTope->dato);

  desapilar(pila);
  nodoTope = tope(pila);
  printf("el primer elemento es: %d\n", nodoTope->dato);

  desapilar(pila);
  nodoTope = tope(pila);
  if(nodoTope == NULL){
    printf("Lista vacia\n");
  }else{
    printf("el primer elemento es: %d\n", nodoTope->dato);  
  }
  int datoBUscado = buscarDatoPila(pila, 91);

  if(datoBUscado == 1){
    printf("Se encontro el dato solicitado\n");
  }else{
    printf("No se encontro el dato solicitado\n");
  }

  /*------------- Actividad 6 -------------*/
  TDApila* pila_2 = crearPilaVacia(3);

  apilar(pila, 1);
  nodoTope = tope(pila);
  printf("el primer elemento es: %d\n", nodoTope->dato);
  
  apilar(pila, 2);
  nodoTope = tope(pila);
  printf("el primer elemento es: %d\n", nodoTope->dato);
    
  apilar(pila, 3);
  nodoTope = tope(pila);
  printf("el primer elemento es: %d\n", nodoTope->dato);
    
  desapilar(pila);
  nodoTope = tope(pila);
  printf("el primer elemento es: %d\n", nodoTope->dato);
    
  apilar(pila, 4);
  nodoTope = tope(pila);
  printf("el primer elemento es: %d\n", nodoTope->dato);
    
  desapilar(pila);
  nodoTope = tope(pila);
  printf("el primer elemento es: %d\n", nodoTope->dato);
    
  desapilar(pila);
  nodoTope = tope(pila);
  printf("el primer elemento es: %d\n", nodoTope->dato);
    
  desapilar(pila);
  nodoTope = tope(pila);
  if(nodoTope == NULL){
    printf("Lista vacia\n");
  }else{
    printf("el primer elemento es: %d\n", nodoTope->dato);  
  }

  free(pila);
  free(pila_2);
  return 0;
}
