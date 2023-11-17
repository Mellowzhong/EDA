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
    
 	return 0;
}
