#include <stdio.h>
#include <stdlib.h>

/*------------- estructura de datos -------------*/

typedef struct nodoGenerico
{
  int dato;
  struct nodoGenerico* puntero;
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
  *lista=nuevo;
}

void eliminarInicio(TDAlista* lista)
{
  nodo* auxiliar;
  if(!esListaVacia(*lista))
  {
    auxiliar=*lista;
    *lista=(*lista)->puntero;
    free(auxiliar);
  }
}
void insertarNodoFinal(TDAlista* lista, int dato){
  if(!esListaVacia(*lista)){
    nodo* aux = *lista;
    while(aux->puntero != NULL){
      aux = aux->puntero;
    }

    nodo* nuevo = (nodo*)malloc(sizeof(nodo));
    nuevo->dato= dato;
    aux->puntero = nuevo;

  }else{
    nodo* nuevo=(nodo*)malloc(sizeof(nodo));
    nuevo->dato=dato;
    nuevo->puntero=*lista;
    *lista=nuevo;
  }
}

void eliminarDato(TDAlista* lista, int dato){
    nodo* aux = *lista;
    nodo* before = NULL;

    while (aux->dato != dato){
        before = aux;
        aux = aux->puntero;
    }
    before->puntero = aux->puntero;
    free(aux);
}

void insertarNodoDespues(TDAlista* lista, int dato, int datoAnterior){
    nodo* aux = *lista;

    while (aux->dato != datoAnterior){
      aux = aux->puntero;
    }

    nodo* nuevo = (nodo*)malloc(sizeof(nodo));
    nuevo->dato= dato;
    nuevo->puntero = aux->puntero;
    aux->puntero = nuevo;
}
/*------------- Actividad 1 -------------*/
//Dom: lista con los nodos
//Rec: void
//Descripcion: elimina todos los nodos de una lista
void liberarLista(TDAlista* lista){
  while (!(esListaVacia(*lista))){
    eliminarInicio(lista);
  }
}

/*------------- Actividad 2 -------------*/
//Dom: lista con los nodos
//Rec: lista
//Descripcion: devuelve una lista con la suma de los vecinos de cada nodo de la lista dada
TDAlista sumaVecinos(TDAlista lista1){
  nodo* aux1 = lista1;
  nodo* anterior = NULL;
  TDAlista lista2 = crearListaVacia();
  int dato = 0;

  while (aux1->puntero != NULL){
    if(anterior == NULL){
      insertarNodoFinal(&lista2, (aux1->puntero)->dato);
      anterior = aux1;
      aux1 = aux1->puntero;
    }else{
      dato = anterior->dato + aux1->puntero->dato;
      insertarNodoFinal(&lista2, dato);
      anterior = aux1;
      aux1 = aux1->puntero;
    }
  }
  insertarNodoFinal(&lista2, anterior->dato);

  return lista2;
}

/*------------- Actividad 3 -------------*/
//Dom: lista_1 con los nodos - lista_2 con los nodos
//Rec: numero
//Descripcion: comprueba que la lista_1 sea igual a la lista_2, si es asi devuelve 1, sino sera 0
int ListasIguales(TDAlista* lista_1, TDAlista* lista_2){
  nodo* aux_1 = *lista_1;
  nodo* aux_2 = *lista_2;

  while (aux_1->puntero != NULL && aux_2->puntero != NULL){
    if(aux_1->dato == aux_2->dato){

      aux_1 = aux_1->puntero;
      aux_2 = aux_2->puntero;
    }else{
      return 0;
    }
  }
  return 1;
}

/*------------- Actividad 4 -------------*/
//Dom: lista con los nodos
//Rec: void
//Descripcion: invierte la lista entregada
TDAlista ListaInversa(TDAlista* lista){
  nodo* aux = *lista;
  nodo* aux_inv = crearListaVacia();

  while (aux->puntero != NULL){
    insertarInicio(&aux_inv, aux->dato);
    aux = aux->puntero;
  }
  insertarInicio(&aux_inv, aux->dato);
  liberarLista(&aux);

  return aux_inv;
}

/*------------- Actividad 5 -------------*/
//Dom: lista con los nodos
//Rec: void
//Descripcion: cambia los elementos de posicion
void elementosCambiados(TDAlista* lista, int indice_1, int indice_2){
  nodo* aux = *lista;
  nodo* anterior = NULL;
  int posicion = 1;
  int dato_1, dato_1_anterior, dato_2, dato_2_anterior;
  if(!esListaVacia(*lista)){
    while (aux != NULL){
      if(posicion == indice_1){
        dato_1 = aux->dato;
        dato_1_anterior = anterior->dato;
      }
      if(posicion == indice_2){
        dato_2 = aux->dato;
        dato_2_anterior = anterior->dato;
      }

      anterior = aux;
      aux = aux->puntero;
      posicion++;
    }

    eliminarDato(lista, dato_1);
    eliminarDato(lista, dato_2);
    insertarNodoDespues(lista, dato_2, dato_1_anterior);
    insertarNodoDespues(lista, dato_1, dato_2_anterior);
  }else{
    
  }
}