/*Estructura de datos para grafo usando LISTA DE ADYACENCIA
 GRAFO NO PONDERADO y DIRIGIDO -- > esto se explica en c�tedra
 */ 
#include <stdbool.h>
#include <stdlib.h>


#include "TDA_LISTA.h"
struct grafo{
	float **Mad; //Arreglo donde cada celda representa un vertice y de tipo Lista
	int n; //numero de nodos del grafo
	int m; //numero de vertices del grafo
};
typedef struct grafo Grafo;

typedef struct vertice_visitado{
	int marcado;
	int pred;
	int distancia;  //distancia o tiempo alcanzado
}Visit;

struct arista{
	int v,w;
	float peso;
};
typedef struct arista Arista;

// Programaci�n Operaciones
Grafo *crear_grafo(int n);
Arista crear_arista(int v, int w, float peso);
bool agregar_arista(Grafo *g, Arista a);
void mostrar_grafo(Grafo *g);
bool eliminar_arista(Grafo *g, Arista a);
bool existe_arista(Grafo *g, Arista a);
bool existe_vertice(Grafo *g, int v);
int grado_vertice(Grafo *g, int v);
int *adyacentes_vertice(Grafo *g, int v);
void mostrar_adyacentes(Grafo *g, int v);

Arista crear_arista(int v, int w, float peso){
	Arista a;
	a.v = v;
	a.w = w;
	a.peso = peso;
	return a;
}

int grado_vertice(Grafo *g, int v){
	int cuenta=0;
	if (existe_vertice(g,v)){ // La existencia debiera validarse antes de entrar v aa la funci�n
		for (int j=0; j<g->n; j++) {
			if (g->Mad[v][j] != 0.0)
				cuenta = cuenta + 1;
		}
	}
	return cuenta;
}

int *adyacentes_vertice(Grafo *g, int v){
	int *adyacentes = NULL, k=0;
	if (grado_vertice(g,v)){ // La existencia debiera validarse antes de entrar v a la funci�n
		adyacentes = (int*)malloc(sizeof(int) * grado_vertice(g,v));
		for (int j=0; j<g->n; j++) {
			if (g->Mad[v][j] != 0.0){
					adyacentes[k] = j;
					k = k + 1;
			}
		}
	} //else printf("\n  adyacentes es NULL");
	return adyacentes;
}

Grafo *crear_grafo(int n){
	Grafo *g;
	g = malloc(sizeof(Grafo));
  g->Mad = malloc(sizeof(float*)*n);
	for (int i=0; i<n; i++){
      g->Mad[i] = malloc(sizeof(float)*n);
	}
	//Todas las aristas M[i][j] de la matriz quedan inactivas (sin conexi�n)
	for (int i=0; i<n;i++) {
		for (int j=0; j<n;j++) 
				g->Mad[i][j] = 0.0;
	}
  g->n = n;
  g->m = 0;
	return  g;	
}

void mostrar_grafo(Grafo *g){ 
	printf("\n Numero de vertices:%d",g->n);
	printf("\n Numero de aristas:%d",g->m);
	printf("\n");
	for (int i=0; i < g->n; i++){ 
		for (int j=0; j < g->n; j++){
			
			printf("%.2f ", g->Mad[i][j]);
		}
		printf("\n");
	}
}

bool agregar_arista(Grafo *g, Arista a){
	if (existe_vertice(g,a.v)){ // existe v�rtice v?
		if (existe_vertice(g,a.w)){ // existe v�rtice w?
				g->Mad[a.v][a.w] = a.peso;
				g->m = g->m + 1;
				return true;
		}
	}
	return false;
}

bool eliminar_arista(Grafo *g, Arista a){
	if (existe_vertice(g,a.v)){ // existe v�rtice v?
		if (existe_vertice(g,a.w)){ // existe v�rtice w?
			if (g->Mad[a.v][a.w] != 0.0) {
				g->Mad[a.v][a.w] = 0.0;
				g->m = g->m - 1;
				return true;
			}
		}
	}
	return false;
}

bool existe_vertice(Grafo *g, int v){
	if (v < g->n)
		return true;
	else
		return false;
}

bool existe_arista(Grafo *g, Arista a){
	if (existe_vertice(g,a.v)){ // existe v�rtice v?
		if (existe_vertice(g,a.w)){ // existe v�rtice w?
			if (g->Mad[a.v][a.w] != 0.0)
				return true;
		}
	}
	return false;
}

void mostrar_adyacentes(Grafo *g, int v){
			//Se asume que antes de llamar a esta operaci�n ha validado existencia adyacentes
			for (int j=0; j<g->n; j++) {
				if (g->Mad[v][j] != 0.0){
						printf("\n  %d", j);
			  }
		  }
}
