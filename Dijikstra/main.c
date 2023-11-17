#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "TDAlista.h"

typedef struct Nodo {
    int dato;
    struct Nodo* siguiente;
} Nodo;

typedef Nodo* LSE;

typedef struct Grafo {
    int n;
    int** A;
    int** W;
} Grafo;

int calcularLargoArreglo(int* arreglo) {
    // Supongamos que el arreglo tiene un valor especial al final, como -1
    int largo = 0;
    while (arreglo[largo] != -1) {
        largo++;
    }
    return largo;
}

int existeEnArreglo(int* arreglo, int elemento) {
    int i = 0;
    while (arreglo[i] != -1) {
        if (arreglo[i] == elemento) {
            return 1;
        }
        i++;
    }
    return 0;
}

int noVisitadoDistanciaMinima(int* distancia, int* visitados, int n) {
    int minDistancia = INT_MAX;
    int vertice = -1;

    for (int i = 0; i < n; i++) {
        if (!visitados[i] && distancia[i] < minDistancia) {
            minDistancia = distancia[i];
            vertice = i;
        }
    }

    return vertice;
}

void marcarVisitado(int* visitados, int vertice) {
    visitados[vertice] = 1;
}

TDAlista obtenerAdyacentes(TDAGrafoLA* grafo, int vertice)
{
	TDAlista adyacentes=crearListaVacia();
	nodo* aux= grafo->A[vertice-1];
	while (aux!=NULL) 
	{
		insertarInicio(&adyacentes, aux->dato);
		aux=aux->puntero;		
	}
	return(adyacentes);
}

int* dijkstra(Grafo* grafo, int inicio) {
    int n = grafo->n;

    int* anterior = (int*)malloc(n * sizeof(int));
    int* distancia = (int*)malloc(n * sizeof(int));
    int* visitados = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        anterior[i] = 0;
        if (grafo->A[inicio][i] > 0) {
            distancia[i] = grafo->W[inicio][i];
            anterior[i] = inicio;
        } else {
            distancia[i] = INT_MAX;
        }
    }

    distancia[inicio] = 0;
    marcarVisitado(visitados, inicio);

    while (calcularLargoArreglo(visitados) < n) {
        int u = noVisitadoDistanciaMinima(distancia, visitados, n);
        marcarVisitado(visitados, u);
        TDAlista adyacentes = obtenerAdyacentes(grafo, u);
        while (adyacentes != NULL){
            int v = adyacentes->dato;
            if (distancia[v] > distancia[u]+grafo->W[u][v]){
                distancia[v] = distancia[u]+grafo->W[u][v];
                anterior[v] = u;
            }
            adyacentes = adyacentes->puntero;
        }
        
    }

    free(visitados);
    free(anterior);
    //Falta devolver distancia pero detalles menores
    return distancia;
}

int main() {
    printf("peo");

    return 0;
}
