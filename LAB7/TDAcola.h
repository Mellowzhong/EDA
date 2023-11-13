#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura de un nodocola en la TDACola
typedef struct nodocola {
    int dato;
    struct nodocola* siguiente;
} nodocola;

// Definición de la TDACola
typedef struct TDAcola{
  int capacidad;
  int size;
  nodocola* frente;
  nodocola* final;
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
        nodocola* nuevonodocola = (nodocola*)malloc(sizeof(nodocola));
        nuevonodocola->dato = dato;
        nuevonodocola->siguiente = NULL;
        if (esColaVacia(lista)){
            lista->frente = nuevonodocola;
            lista->final = nuevonodocola;
        } else {
            lista->final->siguiente = nuevonodocola;
            lista->final = nuevonodocola;
        }
        lista->size++; // Incrementa el tamaño de la cola
    } else {
        printf("La cola está llena.\n");
    }
}

int desencolar(TDAcola* lista) {
    if (!esColaVacia(lista)) {
        nodocola* nodocolaFrente = lista->frente;
        lista->frente = lista->frente->siguiente;
        free(nodocolaFrente);
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
    nodocola* actual = cola->frente;
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