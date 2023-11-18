#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura de un nodocolatripleta en la TDAColaTripleta
typedef struct nodocolatripleta {
    int fin;
    int peso;
    struct nodocolatripleta* siguiente;
} nodocolatripleta;

// Definición de la TDAColaTripleta
typedef struct TDAcolaTripleta{
  int capacidad;
  int size;
  nodocolatripleta* frente;
  nodocolatripleta* final;
} TDAcolaTripleta;

int esColaVaciaTripleta(TDAcolaTripleta* lista){
  if((*lista).frente == NULL){
    return 1;
  }
  else{
    return 0;
  }
}

// Función para crear una TDAColaTripleta vacía
TDAcolaTripleta* crearColaVaciaTripleta(int capacidad){
    TDAcolaTripleta* nueva = (TDAcolaTripleta*)malloc(sizeof(TDAcolaTripleta));
    nueva->capacidad = capacidad;
    nueva->size = 0;
    nueva->frente = nueva->final = NULL;
    return nueva;
}

// Función para enTDAColaTripletar un elemento
void encolarTripleta(TDAcolaTripleta* lista, int dato, int peso) {
    if (lista->size < lista->capacidad) {
        nodocolatripleta* nuevoNodo = (nodocolatripleta*)malloc(sizeof(nodocolatripleta));
        if (nuevoNodo == NULL) {
            // Manejo de error si la asignación de memoria falla
            printf("Error: no se pudo asignar memoria para el nuevo nodo.\n");
            return;
        }

        nuevoNodo->fin = dato;
        nuevoNodo->peso = peso;
        nuevoNodo->siguiente = NULL;

        if (esColaVaciaTripleta(lista)) {
            printf("La cola esta vacía.\n");
            lista->frente = nuevoNodo;
            lista->final = nuevoNodo;
        } else {
            printf("La cola no esta vacia.\n");
            lista->final->siguiente = nuevoNodo;
            lista->final = nuevoNodo;
        }

        lista->size++; // Incrementa el tamaño de la cola
    } else {
        printf("La cola esta llena.\n");
    }
    printf("Termino de encolar.\n");
}

int desencolarTripleta(TDAcolaTripleta* lista) {
    if (!esColaVaciaTripleta(lista)) {
        nodocolatripleta* nodocolatripletaFrente = lista->frente;
        lista->frente = lista->frente->siguiente;
        free(nodocolatripletaFrente);
        lista->size--; // Decrementa el tamaño de la cola
        return 1; // Indicador de éxito
    } else {
        printf("La cola está vacía.\n");
        return 0; // Indicador de error
    }
}

nodocolatripleta* mirarTripleta(TDAcolaTripleta* lista) {
    if (!esColaVaciaTripleta(lista)) {
        return lista->frente;
    }else{
        printf("no hay algo que mirar\n");
        return NULL;
    }
}

void imprimirColaTripleta(TDAcolaTripleta* cola) {
    nodocolatripleta* actual = cola->frente;
    while (actual != NULL) {
        printf("fin:%d peso:%d-> ", actual->fin, actual->peso);
        actual = actual->siguiente;
    }
    printf("NULL\n");
}