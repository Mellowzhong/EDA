#include <stdio.h>
#include <stdlib.h>

/*------------- estructura de datos -------------*/

typedef struct nodopilaGenerico
{
   int dato;
   struct nodopilaGenerico* puntero;
}nodopila;

typedef struct
{
  int capacidad;
  int size;
  nodopila* tope;
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

// Descripcion: Retorna el tope de una pila sin sacarlo de la pila.
// Dom: pila (pila)
// Rec: topa (nodopila)
nodopila* tope(TDApila* pila){
  return pila->tope;
}

/*------------- Actividad 3 -------------*/

// Descripcion: Agrega un dato al principio del tope de la pila.
// Dom: pila (pila) X dato (int)
// Rec: -
void apilar(TDApila* pila, int dato){
  if(pila->size + 1 < pila->capacidad){
    nodopila* nuevonodopila = (nodopila*)malloc(sizeof(nodopila));
    nuevonodopila->dato = dato;
    nuevonodopila->puntero = pila->tope;
    pila->tope = nuevonodopila;
    pila->size = pila->size + 1;
  }
  else{
    printf("La pila esta llena.\n");
  }
}

/*------------- Actividad 4 -------------*/

// Descripcion: Sacar un dato  al principio del tope de la pila.
// Dom: pila (pila)
// Rec: -
void desapilar(TDApila* pila){
  if(!esPilaVacia(pila)){
    nodopila* nodopilaActual = pila->tope;
    nodopila* nodopilaSiguiente = nodopilaActual->puntero;
    pila->tope = nodopilaSiguiente;
    pila->size = pila->size - 1;
    free(nodopilaActual);
  }
  else{
    printf("La pila esta vacia.\n");
  }
}

/*------------- Actividad 5 -------------*/

// Descripcion: Identifica si existe el dato en una pila.
// Dom: pila (pila) X dato (int)
// Rec: verificador (int)
int buscarDatoPila(TDApila* pila, int dato){
  int valorTope, verificador;
  nodopila* nodopilaActual;
  TDApila* aux = crearPilaVacia(8); // se asume que la capacidad de la pila auxiliar es 8.

  verificador = 0;

  while(!esPilaVacia(pila)){
    nodopilaActual = tope(pila);
    valorTope = nodopilaActual->dato;

    if(valorTope == dato){
      verificador = 1;
    }

    desapilar(pila);
    apilar(aux, valorTope);
  }

  while(!esPilaVacia(aux)){
    nodopilaActual = tope(aux);
    valorTope = nodopilaActual->dato;
    desapilar(aux);
    apilar(pila, valorTope);
  }
  return verificador;
}
