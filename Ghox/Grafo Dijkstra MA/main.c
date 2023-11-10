#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Agregue el TDA correspondiente
#include "TDA_GRAFO_MA.h"


int main(int argc,  char *argv[]) {
	int i , num_vertices, v, w;
	float peso;
	Grafo *grafo;
	FILE *fil;
	fil = fopen("archivo.txt","r");
	fscanf(fil, "%d", &num_vertices);
	grafo = crear_grafo(num_vertices);	 
	while(fscanf(fil,"%i %i %f", &v, &w, &peso) == 3){
		Arista aux = crear_arista(v, w, peso);
		agregar_arista(grafo, aux);
	}			
	mostrar_grafo(grafo);
  	return 0;
}