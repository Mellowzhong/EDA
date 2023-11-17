#include <stdio.h>
#include <stdlib.h>
#include "TDAGrafoLA.h"


int main() 
{
    TDAGrafoLA* grafo = leerGrafoNoDirigido("grafoND-NP.in");
    
    imprimirListaAdyacencia(grafo);

    TDAlista adyacentes = obtenerAdyacentes(grafo, 2);

    printf("Adyacentes del vertice 2:\n");
    recorrerLista(adyacentes);
    
    printf("DFS:\n");
    recorridoDFS(grafo, 2);

    printf("BFS:\n");
    recorridoBFS(grafo, 1);

    printf("dijkstra\n");
    int nodoInicio = 2; // Nodo de inicio para el algoritmo de Dijkstra

    int* distancias = (int*)malloc(grafo->n * sizeof(int));
    int* anterior = (int*)malloc(grafo->n * sizeof(int));
    int* visitados = (int*)malloc(grafo->n * sizeof(int));

    // Inicializar visitados
    for (int i = 0; i < grafo->n; i++) {
        visitados[i] = 0;
    }
    dijkstra(grafo, nodoInicio, distancias, anterior, visitados);

    imprimirSolucion(distancias, anterior, grafo->n);

    mostrar_grafo(grafo);

 	return 0;
}
