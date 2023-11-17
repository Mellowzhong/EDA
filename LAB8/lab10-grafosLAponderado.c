#include <stdio.h>
#include <stdlib.h>
#include "TDAGrafoLA.h"


int main() 
{
    
	TDAGrafoLA *grafo;
	grafo = leerGrafoNoDirigidoPond("grafo-ND-P.in");

	imprimirListaAdyacencia(grafo);
 	return 0;
}
