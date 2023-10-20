#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura de un nodo en la TDAlista
typedef struct Nodo {
    int dato;
    struct Nodo* siguiente;
} Nodo;

// Definición de la TDAlista
typedef struct TDAlista {
    Nodo* frente;
    Nodo* final;
} TDAlista;

int esListaVacia(TDAlista lista){
  if (lista.frente == NULL){
    return 1;
  }else{
    return 0;
  }
}

// Función para crear una TDAlista vacía
TDAlista* crearListaVacia() {
    TDAlista* nuevaTDAlista = (TDAlista*)malloc(sizeof(TDAlista));
    nuevaTDAlista->frente = nuevaTDAlista->final = NULL;
    return nuevaTDAlista;
}

// Función para enTDAlistar un elemento
void encolar(TDAlista* lista, int dato) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = NULL;
    if (esListaVacia(*lista)) {
        lista->frente = lista->final = nuevoNodo;
    } else {
        lista->final->siguiente = nuevoNodo;
        lista->final = nuevoNodo;
    }
}

int desencolar(TDAlista* lista) {
    if (!esListaVacia(*lista)) {
        Nodo* temp = lista->frente;
        int dato = temp->dato;
        lista->frente = lista->frente->siguiente;
        free(temp);
        return dato;
    }else{
        printf("La lista esta vacia\n");
        return -1;
    }
}


int mirar(TDAlista* lista) {
    if (!esListaVacia(*lista)) {
        return lista->frente->dato;
    }else{
        return -1;   //No hay elementos en la cola
    }
}