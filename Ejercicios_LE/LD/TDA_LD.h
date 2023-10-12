#include <stdio.h>
#include <stdlib.h>

/*------------- estructura de datos -------------*/

typedef struct nodoGenerico
{
  int dato;
  struct nodoGenerico* puntero;
  struct nodoGenerico* anterior;
}nodo;

typedef nodo* TDAlista;

/*------------- operaciones -------------*/

TDAlista crearListaVacia()
{
  TDAlista lista=(TDAlista)malloc(sizeof(TDAlista));
  lista=NULL;
  return lista;
}

int esListaVacia(TDAlista lista)
{
  if (lista == NULL)
    return 1;
  else
    return 0;
}

void recorrerLista(TDAlista lista)
{
  if (!esListaVacia(lista))
  {
    nodo* auxiliar=lista;
    while (auxiliar!=NULL)
    {
      printf("%d ",auxiliar->dato);
      auxiliar=auxiliar->puntero;
    }
    printf("\n");
  }
  else
    printf("La lista está vacía\n");
}

void insertarInicio(TDAlista* lista, int dato)
{
  nodo* nuevo=(nodo*)malloc(sizeof(nodo));
  nuevo->dato=dato;
  nuevo->puntero=*lista;
  nuevo->anterior = NULL;
  if(*lista != NULL){
    (*lista)->anterior = nuevo;
  }

  *lista=nuevo;
}

void insertarNodoFinal(TDAlista* lista, int dato){
  if(!esListaVacia(*lista)){
    nodo* aux = *lista;
    while(aux->puntero != NULL){
      aux = aux->puntero;
    }

    nodo* nuevo = (nodo*)malloc(sizeof(nodo));
    nuevo->dato= dato;
    nuevo->puntero = NULL;
    nuevo->anterior = aux;
    aux->puntero = nuevo;
  }else{
    insertarInicio(lista, dato);
  }
}

TDAlista append_list(TDAlista listaA, TDAlista listaB){
  TDAlista auxA = listaA;
  TDAlista list = crearListaVacia();

  while (auxA->puntero != NULL){
    auxA = auxA->puntero;
  }

  auxA->puntero = listaB;
  listaB->anterior = auxA;

  list = listaA;
  return list;
}
