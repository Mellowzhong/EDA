#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Agregue el TDA correspondiente
#include "TDA_GRAFO.h"


int main(int argc,  char *argv[]) {

		/* Este c�digo es s�lo experimental. 
		   Despu�s de que comprenda lo que est� haciendo, usted debe 
			 cambiarlo seg�n las indicaciones del docente */
    Grafo *g;
		g = crear_grafo(4); //crea el grafo con 4 v�rtices
    printf("\nGrafo creado en @ = %p  con  %d vertices\n", g, g->n);
		// Insertar aristas al primer v�rtice 
		insertar_nodo_fin(g->lisv[0],1);
		insertar_nodo_fin(g->lisv[0],2);
		insertar_nodo_fin(g->lisv[0],3);
		printf("\nAristas (0,w) donde w son:");
		mostrar_lista(g->lisv[0]); 

		// Insertar aristas al segundo v�rtice
		insertar_nodo_fin(g->lisv[1],0);
		insertar_nodo_fin(g->lisv[1],2);
		insertar_nodo_fin(g->lisv[1],3);
		printf("\nAristas (1,w) donde w son:");
		mostrar_lista(g->lisv[1]); 

		printf("\nAristas (2,w) donde w son:");
		mostrar_lista(g->lisv[2]); 
		printf("\nAristas (3,w) donde w son:");
		mostrar_lista(g->lisv[3]); 

		agregar_vertice(g); //Debiera agregar una lista en g->lisv[4]
		insertar_nodo_fin(g->lisv[4],3);
		printf("\nAristas (4,w) donde w son:");
		mostrar_lista(g->lisv[4]); 
		
		
		/* de la TAREA 4: Despu�s de programar la operaci�n agregar_arista, 
		   Reemplace el c�digo anterior utilizando los datos del grafo 
			 datos_grafo.txt
			 
			 Pasos a seguir:
			 a) Declare las variables necesarias. Recuerde que una variable tipo
			    archivo se declara:
					FILE *fp;
					y la lectura del archivo es:
					fp = fopen("datos_grafo.txt", "r")*/
					
	int i , num_vertices, v, w;
	Grafo *grafo;
	FILE *fil;
	fil = fopen("archivo.txt","r");
	fscanf(fil, "%d", &num_vertices);
	/* b) Crear el grafo usando el n�mero de v�rtices que se encuentra 
		en la primera fila del archivo */
	grafo = crear_grafo(num_vertices);	 
	/*	 c) Para  cada arista del grafo almacenada en el archivo datos_grafo.txt
		ins�rtela al grafo usando la funci�n agregar_arista que ha creado en el .h */
	while(fscanf(fil,"%i %i", &v, &w) == 2){
		agregar_arista(grafo,v,w);
	}			
		/*		d) muestre el grafo resultante */
	mostrar_grafo(grafo);
			/*	e) Agregue un nuevo v�rtice al grafo y pruebe que se haya creado correctamente
		*/ 
	// Paso e)
		agregar_vertice(grafo); //n cambia y debiera agregar una lista en g->lisv[n-1]
		printf("\nNumero de vertices cambio a: %d", grafo->n); //debiera mostrar 7
		printf("\nNumero de aristas (nodos) del nuevo vertice %d es %d", grafo->n-1, grafo->lisv[grafo->n-1]->n); //debiera mostrar 0
		agregar_arista(grafo, grafo->n-1, 0);
		mostrar_grafo(grafo);
	// continuar usted con las operaciones buscar arista, eliminar arista, etc.
	int a,b;
	printf("\n\nQue arista quiere buscar(ej:1 3, 1 siendo la lista, 3 el nodo):");
	scanf("%d %d",&a,&b);
	int res = buscar_arista(grafo, a, b);
	if (res == 1){
		printf("\nLa arista entre %d y %d existe",a,b);
	}
	else{
		printf("\nLa arista entre %d y %d no existe",a,b);
	}
	printf("\n\nQue arista quiere eliminar(ej:1 3, 1 siendo la lista, 3 el nodo):");
	scanf("%d %d",&a,&b);
	eliminar_arista(grafo, a,b);
	mostrar_grafo(grafo);
	Lista* Lista_aristas = obtener_aristas(grafo);
	mostrar_lista(Lista_aristas);
	printf("\n\n");
  	return 0;
}