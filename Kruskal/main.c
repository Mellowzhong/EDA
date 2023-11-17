#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int dato;
    struct Nodo* siguiente;
} Nodo;

typedef Nodo* LSE;

typedef struct Arista {
    int inicio;
    int fin;
    int peso;
} Arista;

typedef struct Grafo {
    int n;
    LSE* A;
    int** W;
} Grafo;

LSE crearListaVacia() {
    return NULL;
}

void insertarNodoFinal(LSE* lista, int fin) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->dato = fin;
    nuevo->siguiente = NULL;

    if (*lista == NULL) {
        *lista = nuevo;
    } else {
        Nodo* temp = *lista;
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
    }
}

Arista* ordenarAristas(Grafo* grafo) {
    int n = grafo->n;
    int numAristas = 0;

    for (int i = 0; i < n; i++) {
        LSE adyacentes = grafo->A[i];
        while (adyacentes != NULL) {
            numAristas++;
            adyacentes = adyacentes->siguiente;
        }
    }

    Arista* aristas = (Arista*)malloc(numAristas * sizeof(Arista));
    int indice = 0;

    for (int i = 0; i < n; i++) {
        LSE adyacentes = grafo->A[i];
        while (adyacentes != NULL) {
            aristas[indice].inicio = i;
            aristas[indice].fin = adyacentes->dato;
            aristas[indice].peso = grafo->W[i][adyacentes->dato];
            indice++;
            adyacentes = adyacentes->siguiente;
        }
    }

    qsort(aristas, numAristas, sizeof(Arista), compararAristas);

    return aristas;
}

int existeCiclo(LSE MST, Arista arista) {
    int inicio = arista.inicio;
    int fin = arista.fin;

    int* conjuntoVertices = (int*)malloc((inicio + fin) * sizeof(int));
    for (int i = 0; i < inicio + fin; i++) {
        conjuntoVertices[i] = -1;
    }

    Nodo* temp = MST;
    while (temp != NULL) {
        conjuntoVertices[temp->dato] = temp->dato;
        temp = temp->siguiente;
    }

    if (conjuntoVertices[inicio] == conjuntoVertices[fin]) {
        free(conjuntoVertices);
        return 1;
    }

    free(conjuntoVertices);
    return 0;
}

LSE kruskal(Grafo* grafo) {
    LSE MST = crearListaVacia();
    Arista* colaAristas = ordenarAristas(grafo);
    int inicio = 1;

    while (!esColaVacia(colaAristas)) {
        Arista arista = frente(colaAristas);
        desencolar(colaAristas);

        if (inicio == 1) {
            insertarNodoFinal(&MST, arista.fin);
            inicio = 0;
        } else {
            if (!existeCiclo(MST, arista)) {
                insertarNodoFinal(&MST, arista.fin);
            }
        }
    }

    free(colaAristas);

    return MST;
}


int main() {
    printf("peo");

    return 0;
}
