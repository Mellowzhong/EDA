#include <stdio.h>
#include <stdlib.h>

/*------------- estructura de datos -------------*/

typedef struct nodoGenerico
{
   int dato;
   struct nodoGenerico* puntero;
}nodo;

typedef struct
{
  int capacidad;
  int size;
  nodo* tope;
}TDApila;

/*------------- operaciones -------------*/

TDApila* crearPilaVacia(int capacidad)
{
  TDApila* pila=(TDApila*)malloc(sizeof(TDApila));
  pila->capacidad=capacidad;
  pila->size=0;
  pila->tope=NULL;
  return pila;
}

int esPilaVacia(TDApila* pila)
{
  if (pila->size == 0)
    return 1;
  else
    return 0;
}


/*------------- Actividad 2 -------------*/
//Dom: pila con los nodos
//Rec: nodo del tope
//Descripcion: devuelve el nodo del tope
nodo* tope(TDApila* pila){
  if (!esPilaVacia(pila)) {
    return pila->tope;
  }else{
    return NULL;
  }
}

/*------------- Actividad 3 -------------*/
//Dom: pila con los nodos - dato a apilar
//Rec: void
//Descripcion: agrega un elemento al tope de la pila
void apilar(TDApila* pila, int dato){
  if(pila->size < pila->capacidad){
    nodo* nuevo = (nodo*)malloc(sizeof(nodo));
    nuevo->dato = dato;
    nuevo->puntero = pila->tope;
    pila->tope = nuevo;
    pila->size = pila->size + 1;
  }else{
    printf("La pila esta llena, no se pueden agregar mas datos");
  }
}

/*------------- Actividad 4 -------------*/
//Dom: pila con los nodos
//Rec: void
//Descripcion: elimina el tope de la pila
void desapilar(TDApila* pila){
  if(!esPilaVacia(pila)) {
    nodo* aux = pila->tope;
    int dato = aux->dato;
    pila->tope = (pila->tope)->puntero;
    pila->size = pila->size - 1;
    free(aux);
  }else{
    printf("La pila esta vacia\n");
  }
}

/*------------- Actividad 5 -------------*/
//Dom: pila con los nodos - dato a buscar
//Rec: 1 si se encontro o 0 si no se encontro
//Descripcion: busca en la pila el elemento buscado y mantiene la pila original
int buscarDatoPila(TDApila* pila, int dato){
  int encontrado = 0;
  if(!esPilaVacia(pila)){
    TDApila* inicio = crearPilaVacia(pila->capacidad);
    while (!esPilaVacia(pila)){
      int dato_buscar = (pila->tope)->dato;
      apilar(inicio, dato_buscar);
      if(dato_buscar == dato){
        encontrado = 1;
      }
      desapilar(pila);
    }
    while (!esPilaVacia(inicio)){
      apilar(pila, inicio->tope->dato);
      desapilar(inicio);
    }

    return encontrado;  
  }else{

    printf("No hay elementos en la lista\n");
    return encontrado;
  }
}