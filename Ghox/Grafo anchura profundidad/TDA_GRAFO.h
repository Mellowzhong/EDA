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

typedef struct vertice_visitado{
	int marcado;
	int pred;
	int distancia;  //distancia o tiempo alcanzado
}Visit;

Grafo *crear_grafo(int n); //Necesito saber el n�mero de v�rtices a insertar inicialmente
void agregar_vertice(Grafo *G); // agrega una celda (memoria) al arreglo din�mico del grafo creado
void mostrar_grafo(Grafo *G); 
void agregar_arista(Grafo *G, int v, int w); //agrega una arista (v,w) al grafo// Es decir, agrega un nodo a la lista G-lisv[v]. �Qu� m�s debe considerar?
int buscar_arista(Grafo *G, int v, int w);
void eliminar_arista(Grafo *G, int v, int w);
Lista* obtener_aristas(Grafo *G);
Lista* obtener_adyacentes(Grafo *G, int v) ;
int *adyacentes_vertice(Grafo *g, int v);
int obtener_grado_vertice(Grafo *G, int v);
bool Verificar_conexo_anchura(Grafo *G, int origen);
bool Conexo_DFS(Grafo *G);
void DFS_visit(Grafo *g, Visit vertex[], int u, int *t);
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
	insertar_nodo_fin(G->lisv[w],v);
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
	eliminar_nodo(G->lisv[w],v);
	G->m = G->m-1;
}

Lista* obtener_aristas(Grafo *G) {
    Lista* arista = crear_lista();
    for (int i = 0; i < G->n; i++) {
        insertar_nodo_fin(arista, G->lisv[i]->n);
    }
    return arista;
}

Lista* obtener_adyacentes(Grafo *G, int v) {
    Lista* arista = crear_lista();
    Nodo* aux = G->lisv[v]->head;
	while (aux != NULL){
		insertar_nodo_fin(arista, aux->info);
		aux = aux->sig;
	}
    return arista;
}

int *adyacentes_vertice(Grafo *g, int v){
	int *adyacentes = NULL, k=0;
	if (obtener_grado_vertice(g,v)){ // La existencia debiera validarse antes de entrar v a la funci�n
		adyacentes = (int*)malloc(sizeof(int) * obtener_grado_vertice(g,v));
		Nodo* aux = g->lisv[v]->head;
		while (aux != NULL){
			adyacentes[k] = aux->info;
			k = k + 1;
			aux = aux->sig;
		}
	} //else printf("\n  adyacentes es NULL");
	return adyacentes;
}

int obtener_grado_vertice(Grafo *G, int v){
	return G->lisv[v]->n;
}


bool Verificar_conexo_anchura(Grafo* G, int origen) {
    bool visitados[G->n]; // Defino una lista falsa de todos los vértices del grafo
    for (int i = 0; i < G->n; i++) {
        visitados[i] = false;
    }
    visitados[origen] = true; // Defino el origen como visitado

    int cola[G->n]; // Defino una cola
    int frente = 0;
    int fin = 0;
    cola[fin++] = origen;

    while (frente != fin) {
        int vertice = cola[frente++];
        Lista* adya = obtener_adyacentes(G, vertice);
        Nodo* aux = adya->head;
        while (aux != NULL) {
            if (visitados[aux->info] == false) {
                visitados[aux->info] = true;
                cola[fin++] = aux->info;
            }
            aux = aux->sig;
        }
    }
    for (int i = 0; i < G->n; i++) {
		if (visitados[i] == false) {
            return false;
        }
    }
    return true;
}

bool Conexo_DFS(Grafo *G) {
	Visit vertex[G->n];
	for (int i = 0; i < G->n; i++) {
		vertex[i].marcado = 0;
		vertex[i].pred = -1;
		vertex[i].distancia = 0;
	}
	int time = 0;
	for (int i = 0; i < G->n; i++) {
		if (vertex[i].marcado == 0) {
			DFS_visit(G, vertex, i, &time);
		}
	}
	for (int i = 0; i < G->n; i++) {
		if (vertex[i].marcado == 1) {
			return false;
		}
	}
	return true;
}

void DFS_visit(Grafo *g, Visit vertex[], int u, int *t) {
	int grado_s, *ady = NULL;
	*t = *t + 1;
	vertex[u].distancia = *t;
	vertex[u].marcado = 1; // nodo a explorar
	printf("\nPor la arista (%d,%d)\t", vertex[u].pred, u);
	printf("visito nodo %d\t en tiempo %d", u, vertex[u].distancia);
	grado_s = obtener_grado_vertice(g, u);
	if (grado_s == 0) {
		return;
	}
	ady = adyacentes_vertice(g, u);
	if (ady != NULL) {
		for (int k = 0; k < grado_s; k++) { // Recorre adyacentes de nodo u
			if (vertex[ady[k]].marcado == 0) {
				vertex[ady[k]].pred = u;
				DFS_visit(g, vertex, ady[k], t);
			}
		} // fin for
		vertex[u].marcado = 2; // Fin de exploración del nodo
		*t = *t + 1;
	}
}
