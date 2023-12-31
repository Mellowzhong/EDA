#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

/*------------- Actividad 1 -------------*/
//Dom: lista con los nodos
//Rec: numero de nodos
//Descripcion: entrega el numero de nodos de la lista
int obtenerNumNodos(TDAlista lista){
  if(!esListaVacia(lista)){
    int count = 0;
    nodo* auxiliar = lista;
    
    while (auxiliar != NULL){
      auxiliar = auxiliar->puntero;
      count++;
    }
    return count;

  }else{
    return 0;
  }
}

/*------------- Actividad 2 -------------*/
//Dom: lista con los nodos - dato a buscar
//Rec: entrega si se econtro el dato
//Descripcion: busca un dato dentro de la lista
int buscarDatoLista(TDAlista lista, int dato){
  if(!esListaVacia(lista)){
    nodo* aux = lista;
    while (aux->dato != dato){
      if(aux->puntero == NULL){
        return 0;
      }
      aux = aux->puntero;
    }
    return 1;
  }
}

/*------------- Actividad 3 -------------*/
//Dom: lista con los nodos - dato a insertar
//Rec: void
//Descripcion: agrega un nodo al final de la lista
void insertarNodoFinal(TDAlista* lista, int dato){
  if(!esListaVacia(*lista)){
    nodo* aux = *lista;
    while(aux->puntero != NULL){
      aux = aux->puntero;
    }

    nodo* nuevo = (nodo*)malloc(sizeof(nodo));
    nuevo->dato= dato;
    aux->puntero = nuevo;
  }
}

//Dom: lista con los nodos - dato a insertar
//Rec: void
//Descripcion: agrega un nodo arbitrariamente en la lista
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

/*------------- Actividad 4 -------------*/
//Dom: lista con los nodos
//Rec: void
//Descripcion: elimina un nodo al final de la lista
void eliminarFinal(TDAlista* lista){
  nodo* aux = *lista;
  nodo* antes = NULL;

  while (aux->puntero != NULL){
    antes = aux;
    aux = aux->puntero;
  }
  antes->puntero = NULL;
}

//Dom: lista con los nodos - dato a eliminar
//Rec: void
//Descripcion: elimina un nodo arbitrariamente en la lista
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

/*------------- Actividad 5 -------------*/
//Dom: lista con los nodos - dato a eliminar
//Rec: void
//Descripcion: elimina un nodo arbitrariamente en la lista
nodo* obtenerNodo(TDAlista lista, int posicion){
  nodo* aux = lista;
  int count = 0;

  while (count != posicion - 1){ 
    aux = aux->puntero;
    count++;
  }

  return aux;
}

//Dom: lista con los nodos
//Rec: void
//Descripcion: elimina todos los nodos de la lista dejandola vacia
void liberarLista(TDAlista* lista){
  while (!(esListaVacia(*lista))){
    eliminarInicio(lista);
  }
}

//Dom: lista_1 con los nodos - lista_2 con los nodos
//Rec: boleano
//Descripcion: comprueba que la lista_1 sea igual a la lista_2, si es asi devuelve true, sino sera false
bool equalList(TDAlista* lista_1, TDAlista* lista_2){
  nodo* aux_1 = *lista_1;
  nodo* aux_2 = *lista_2;

  while (aux_1->puntero != NULL && aux_2->puntero != NULL){
    if(aux_1->dato == aux_2->dato){

      aux_1 = aux_1->puntero;
      aux_2 = aux_2->puntero;
    }else{
      return false;
    }
  }
  return true;
}

//Dom: lista con los nodos
//Rec: void
//Descripcion: invierte la lista entregada
void invertirList(TDAlista* lista){
  nodo* aux = *lista;
  nodo* aux_inv = crearListaVacia();

  while (aux->puntero != NULL){
    insertarInicio(&aux_inv, aux->dato);
    aux = aux->puntero;
  }
  insertarInicio(&aux_inv, aux->dato);
  liberarLista(&aux);
  *lista = aux_inv;
}