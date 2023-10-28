#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura de un nodo en la TDACola
typedef struct Nodo {
    int dato;
    struct Nodo* siguiente;
} Nodo;

// Definición de la TDACola
typedef struct TDACola {
    Nodo* frente;
    Nodo* final;
} TDACola;

int esListaVacia(TDACola lista){
  if (lista.frente == NULL){
    return 1;
  }else{
    return 0;
  }
}

// Función para crear una TDACola vacía
TDACola* crearListaVacia() {
    TDACola* nuevaTDACola = (TDACola*)malloc(sizeof(TDACola));
    nuevaTDACola->frente = nuevaTDACola->final = NULL;
    return nuevaTDACola;
}

// Función para enTDAColar un elemento
void encolar(TDACola* lista, int dato) {
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

int desencolar(TDACola* lista) {
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

int mirar(TDACola* lista) {
    if (!esListaVacia(*lista)) {
        return lista->frente->dato;
    }else{
        return -1;   //No hay elementos en la cola
    }
}

void imprimirCola(TDACola* cola) {
    Nodo* actual = cola->frente;
    while (actual != NULL) {
        printf("%d -> ", actual->dato);
        actual = actual->siguiente;
    }
    printf("NULL\n");
}

TDACola* cambiarOcurrencias(TDACola* lista, int v1, int v2){
    TDACola* inicio = crearListaVacia();
    int resta = v2 - v1;
    while (!esListaVacia(*lista)){
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