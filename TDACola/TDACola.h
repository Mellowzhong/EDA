#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura de un nodo en la TDACola
typedef struct Nodo {
    int dato;
    struct Nodo* siguiente;
} Nodo;

// Definición de la TDACola
typedef struct TDAcola{
  int capacidad;
  int size;
  Nodo* frente;
  Nodo* final;
} TDAcola;

int esColaVacia(TDAcola* lista){
  if((*lista).frente == NULL){
    return 1;
  }
  else{
    return 0;
  }
}

// Función para crear una TDACola vacía
TDAcola* crearColaVacia(int capacidad){
    TDAcola* nuevaTDACola = (TDAcola*)malloc(sizeof(TDAcola));
    nuevaTDACola->capacidad = capacidad;
    nuevaTDACola->size = 0;
    nuevaTDACola->frente = nuevaTDACola->final = NULL;
    return nuevaTDACola;
}

// Función para enTDAColar un elemento
void encolar(TDAcola* lista, int dato) {
    if (lista->size < lista->capacidad) {
        Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
        nuevoNodo->dato = dato;
        nuevoNodo->siguiente = NULL;
        if (esColaVacia(lista)){
            lista->frente = nuevoNodo;
            lista->final = nuevoNodo;
        } else {
            lista->final->siguiente = nuevoNodo;
            lista->final = nuevoNodo;
        }
        lista->size++; // Incrementa el tamaño de la cola
    } else {
        printf("La cola está llena.\n");
    }
}

int desencolar(TDAcola* lista) {
    if (!esColaVacia(lista)) {
        Nodo* nodoFrente = lista->frente;
        lista->frente = lista->frente->siguiente;
        free(nodoFrente);
        lista->size--; // Decrementa el tamaño de la cola
        return 1; // Indicador de éxito
    } else {
        printf("La cola está vacía.\n");
        return 0; // Indicador de error
    }
}

int mirar(TDAcola* lista) {
    if (!esColaVacia(lista)) {
        return lista->frente->dato;
    }else{
        return -1;   //No hay elementos en la cola
    }
}

void imprimirCola(TDAcola* cola) {
    Nodo* actual = cola->frente;
    while (actual != NULL) {
        printf("%d -> ", actual->dato);
        actual = actual->siguiente;
    }
    printf("NULL\n");
}

TDAcola* cambiarOcurrencias(TDAcola* lista, int v1, int v2){
    int capacidadLista = lista->capacidad;
    TDAcola* inicio = crearColaVacia(capacidadLista);
    int resta = v2 - v1;
    while (!esColaVacia(lista)){
       if(lista->frente->dato == v1){
        encolar(inicio, resta);
        desencolar(lista);
       }else{
        encolar(inicio, lista->frente->dato);
        desencolar(lista);
       }
    }
    return inicio;
}

TDAcola* invertirCola(TDAcola* lista) {
    TDAcola* colaInvertida = crearColaVacia(lista->capacidad);

    while (lista->frente != NULL){
        int dato = mirar(lista);
        desencolar(lista);
        Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
        nuevoNodo->dato = dato;
        nuevoNodo->siguiente = colaInvertida->frente;
        colaInvertida->frente = nuevoNodo;
        colaInvertida->size++;
    }

    colaInvertida->final = colaInvertida->frente;

    return colaInvertida;
}
