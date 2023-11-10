/*Estructura de datos para grafo usando LISTA DE ADYACENCIA
 GRAFO NO PONDERADO y DIRIGIDO -- > esto se explica en c�tedra
 */ 
#include <stdbool.h>
#include <stdlib.h>
#include "TDA_LISTA.h"
struct grafo{
	Lista **lisv; //Arreglo donde cada celda representa un vertice y de tipo Lista
	int n; //numero de nodos del grafo
	int m; //numero de vertices del grafo
};
typedef struct grafo Grafo;

Grafo *crear_grafo(int n); //Necesito saber el n�mero de v�rtices a insertar inicialmente
void agregar_vertice(Grafo *G); // agrega una celda (memoria) al arreglo din�mico del grafo creado
void mostrar_grafo(Grafo *G); 
void agregar_arista(Grafo *G, int v, int w); //agrega una arista (v,w) al grafo// Es decir, agrega un nodo a la lista G-lisv[v]. �Qu� m�s debe considerar?
int buscar_arista(Grafo *G, int v, int w);
void eliminar_arista(Grafo *G, int v, int w);
Lista* obtener_aristas(Grafo *G);
int obtener_grado_vertice(Grafo *G, int v);
/* PROGRAMACI�N OPERACIONES */

Grafo *crear_grafo(int n){
	Grafo *G;
	G = malloc(sizeof(Grafo));
  G->lisv = malloc(sizeof(Lista)*n);
	for (int i=0; i<n; i++){
      G->lisv[i] = crear_lista(); //recuerde: �qu� hace esta funci�n?
	}
  G->n = n;
  G->m = 0;
	return  G;	
}

void agregar_vertice (Grafo *G){
	G->lisv = realloc(G->lisv, sizeof(Lista)*(G->n + 1)); //realloc reasigna tama�o memoria
																												// conservando lo anterior
  G->n = G->n + 1; 
  G->lisv[G->n-1] = crear_lista(); //G->n-1 es el �ltimo �ndice del arreglo G->lisv	
	
}

void mostrar_grafo(Grafo *G){ 
	printf("\n Numero de vertices:%d",G->n);
	printf("\n Numero de aristas:%d",G->m);
	for (int i=0; i<G->n; i++){
      printf("\n %d  ",i );
			mostrar_lista(G->lisv[i]);
	}

}

/* Despu�s de programar esta funci�n, modifique el programa  .c 
   Use esta funci�n para agregar v�rtices al grafo. Siga las indicaciones de su docente
   Pruebe sus resultados usando el .c*/
void agregar_arista(Grafo *G, int v, int w){
	insertar_nodo_fin(G->lisv[v],w);
	G->m = G->m+1;
}

int buscar_arista(Grafo *G, int v, int w){
	Nodo *aux;
	aux = buscar_nodo(G->lisv[v],w);
	if (aux == NULL){
		return 0;
	}
	else{
		return 1;
	}
}

void eliminar_arista(Grafo *G, int v, int w){
	eliminar_nodo(G->lisv[v],w);
	G->m = G->m-1;
}

Lista* obtener_aristas(Grafo *G) {
    Lista* arista = crear_lista();
    for (int i = 0; i < G->n; i++) {
        insertar_nodo_fin(arista, G->lisv[i]->n);
    }
	mostrar_lista(arista);
    return arista;
}


int obtener_grado_vertice(Grafo *G, int v){
	return G->lisv[v]->n;
}