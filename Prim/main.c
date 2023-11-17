#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Nodo {
    int inicio;
    int fin;
    int peso;
    struct Nodo* puntero;
} Nodo;

typedef Nodo* LSE;  // Lista simplemente enlazada

typedef struct ElementoColaPrioridades {
    int inicio;
    int fin;
    int peso;
} ElementoColaPrioridades;

typedef struct NodoColaPrioridades {
    ElementoColaPrioridades elemento;
    struct NodoColaPrioridades* siguiente;
} NodoColaPrioridades;

typedef struct ColaPrioridades {
    NodoColaPrioridades* frente;
    NodoColaPrioridades* final;
} ColaPrioridades;

typedef struct Grafo {
    int n;  // Número de vértices
    LSE* A;  // Arreglo donde cada celda representa un vértice y es de tipo Lista
    int** W;  // Matriz de pesos
} Grafo;

// Función para inicializar la cola de prioridades
ColaPrioridades crearColaPrioridadesVacia() {
    ColaPrioridades cola;
    cola.frente = cola.final = NULL;
    return cola;
}

// Función para insertar un elemento en la cola de prioridades
void encolar(ColaPrioridades* cola, ElementoColaPrioridades elemento) {
    NodoColaPrioridades* nuevo = (NodoColaPrioridades*)malloc(sizeof(NodoColaPrioridades));
    nuevo->elemento = elemento;
    nuevo->siguiente = NULL;

    if (cola->final == NULL) {
        cola->frente = cola->final = nuevo;
    } else {
        cola->final->siguiente = nuevo;
        cola->final = nuevo;
    }
}

// Función para extraer el elemento con la prioridad más baja de la cola de prioridades
ElementoColaPrioridades desencolar(ColaPrioridades* cola) {
    if (cola->frente == NULL) {
        ElementoColaPrioridades elementoVacio = { -1, -1, -1 };  // Valor de elemento nulo
        return elementoVacio;
    }

    NodoColaPrioridades* temp = cola->frente;
    ElementoColaPrioridades elemento = temp->elemento;

    cola->frente = cola->frente->siguiente;
    free(temp);

    if (cola->frente == NULL) {
        cola->final = NULL;
    }

    return elemento;
}

// Función para verificar si la cola de prioridades está vacía
int esColaPrioridadesVacia(ColaPrioridades* cola) {
    return cola->frente == NULL;
}

// Función para liberar la memoria utilizada por la cola de prioridades
void liberarColaPrioridades(ColaPrioridades* cola) {
    while (!esColaPrioridadesVacia(cola)) {
        desencolar(cola);
    }
}

// Función para crear una lista simplemente enlazada vacía
LSE crearListaVacia() {
    return NULL;
}

// Función para insertar un nodo al final de la lista
void insertarNodoFinal(LSE* lista, int fin) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->inicio = -1;  // Valor de inicio nulo
    nuevo->fin = fin;
    nuevo->peso = -1;  // Valor de peso nulo
    nuevo->puntero = NULL;

    if (*lista == NULL) {
        *lista = nuevo;
    } else {
        Nodo* temp = *lista;
        while (temp->puntero != NULL) {
            temp = temp->puntero;
        }
        temp->puntero = nuevo;
    }
}

// Función para verificar si un vértice está en la lista
int buscarDato(LSE lista, int dato) {
    Nodo* temp = lista;
    while (temp != NULL) {
        if (temp->fin == dato) {
            return 1;  // Se encontró el dato en la lista
        }
        temp = temp->puntero;
    }
    return 0;  // No se encontró el dato en la lista
}

// Función principal de Prim
LSE prim(Grafo* grafo, int s) {
    LSE MST = crearListaVacia();
    int n = grafo->n;
    ColaPrioridades candidatos = crearColaPrioridadesVacia();
    int cuenta = 1;
    int u = s;

    // Marcar el vértice inicial como visitado e insertar en el MST
    insertarNodoFinal(&MST, u);

    while (cuenta < n) {
        LSE adyacentes = grafo->A[u];
        while (adyacentes != NULL) {
            int v = adyacentes->fin;
            int peso = grafo->W[u][v];

            ElementoColaPrioridades elemento = { u, v, peso };
            encolar(&candidatos, elemento);

            adyacentes = adyacentes->puntero;
        }

        ElementoColaPrioridades elegido = desencolar(&candidatos);

        while (buscarDato(MST, elegido.fin)) {
            elegido = desencolar(&candidatos);
        }

        if (elegido.fin != -1) {
            insertarNodoFinal(&MST, elegido.fin);
            cuenta++;
            u = elegido.fin;
        }
    }

    // Liberar la memoria utilizada por la cola de prioridades
    liberarColaPrioridades(&candidatos);

    return MST;
}

int main() {
    printf("peo");

    return 0;
}
