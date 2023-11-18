#include <stdio.h>
#include <stdlib.h>
#include "TDAGrafoLA.h"


int main() 
{
    
	TDAGrafoLA *grafo;
	grafo = leerGrafoNoDirigidoPond("grafo-ND-P.in");

	imprimirListaAdyacencia(grafo);


	printf("dijikstra\n");
	int* anterior = (int*)malloc(grafo->n*(sizeof(int)));
	int* distancias = (int*)malloc(grafo->n*(sizeof(int)));

	int inicio = 1;
	int destino = 8;

	dijkstra(grafo, inicio, anterior, distancias);

	printf("%d->", destino);
	while (anterior[destino] != 1){
		printf("%d->", anterior[destino]);
		destino = anterior[destino];
	}
	printf("%d\n", inicio);

	free(distancias);
	/*
	printf("prim\n");
	TDAlista listaprim = mstPrim(grafo, inicio);

	printf("kruskall\n");
	
	*/
 	return 0;
}
