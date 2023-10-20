#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
  int data;
  struct nodo *next;
}Nodo;

typedef struct list{  
  Nodo* head;
  Nodo* final;
}TDAlista;

TDAlista* crearListaVacia()
{
  TDAlista* lista=(TDAlista*)malloc(sizeof(TDAlista));
  lista->head = NULL;
  lista->final = NULL;

  return lista;
}

int esListaVacia(TDAlista lista)
{
  if (lista.head == NULL)
    return 1;
  else
    return 0;
}

void recorrerLista(TDAlista lista){
  if (!esListaVacia(lista)){
    
    Nodo* auxiliar = lista.head;
    while (auxiliar!=NULL){
      printf("%d ",auxiliar->data);
      auxiliar = auxiliar->next;
    }
    printf("\n");
  }
  else
    printf("La lista está vacía\n");
}

void encolar(TDAlista* lista, int dato)
{
  Nodo* nuevo=(Nodo*)malloc(sizeof(Nodo));
  nuevo->data = dato;
  nuevo->next = NULL;
  lista->head = nuevo;
  lista->final = nuevo;
}

void descolar(TDAlista* lista){
  Nodo* nodo = lista->head;
  lista->head = lista->head->next;
  free(nodo);
}

int obtenerNumNodos(TDAlista lista){
  if(!esListaVacia(lista)){
    int count = 0;
    Nodo* auxiliar = lista.head;
    
    while (auxiliar != NULL){
      auxiliar = auxiliar->next;
      count++;
    }
    return count;

  }else{
    return 0;
  }
}