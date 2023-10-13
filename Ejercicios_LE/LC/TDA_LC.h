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
    TDAlista actual = lista;

    // Verifica si la lista no está vacía
    if (lista != NULL) {
        do {
            printf("%d ", actual->dato);
            actual = actual->puntero;
        } while (actual != lista);
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
  nuevo->puntero=nuevo;
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
    // Crear un nuevo nodo
    nodo* nuevoNodo = (nodo*)malloc(sizeof(nodo));
    nuevoNodo->dato = dato;
    nuevoNodo->puntero = *lista; // El nuevo nodo apunta al primer nodo

    // Verificar si la lista está vacía
    if (lista == NULL) {
        *lista = nuevoNodo; // El nuevo nodo es el único en la lista
    } else {
        // Encontrar el último nodo
        nodo* ultimo = *lista;
        while (ultimo->puntero != *lista) {
            ultimo = ultimo->puntero;
        }

        // Agregar el nuevo nodo al final
        ultimo->puntero = nuevoNodo;
    }
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

void liberarLista(TDAlista* lista, int numNodos){
  while (!(esListaVacia(*lista))){
    eliminarInicio(lista);
  }
}