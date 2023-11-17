/* grafo no dirigido no ponderado usando LISTA DE ADYACENCIA */
#include <stdio.h>
#include <stdlib.h>
#include "TDAlista.h" 
#include "TDAcola.h"
#include "TDApila.h"
#include "TDAlistaTripleta.h"


/*------------- estructura de datos -------------*/

struct grafo
{
	TDAlistaTripleta* A; 					//Arreglo donde cada celda representa un vertice y de tipo Lista
	int* V;							//Arreglo donde cada celda representa un vertice y de tipo entero
	int n; 							//número de vértices del grafo
	int m; 							//numero de aristas del grafo
};

typedef struct grafo TDAGrafoLA;

/*------------- operaciones -------------*/

TDAGrafoLA* crearGrafoVacio(int n)
{
	int i;

	TDAGrafoLA* G=malloc(sizeof(TDAGrafoLA));
    G->A = (TDAlistaTripleta*)malloc(sizeof(TDAlistaTripleta)*n);
    G->V = (int*)malloc(sizeof(int)*n);

	for (i=0; i<n; i++)
	{
      G->A[i] = crearListaVaciaTripleta(); 
	  G->V[i] = i+1; 	
	}
	G->n = n;
	G->m = 0;

	return  G;	
}

void imprimirListaAdyacencia(TDAGrafoLA* G)
{
	int i; 
	printf("Numero de vertices:%d \n",G->n);
	for (i=0; i<G->n; i++)
	{
		printf("%d  ",G->V[i]);
	}
	printf("\nNumero de aristas:%d \n",G->m);
	for (i=0; i<G->n; i++)
	{
		printf("%d  ",i+1 );
		recorrerListaTripleta(G->A[i]);
	}
}
/*
void agregar_arista(TDAGrafoLA* G, int v, int w)
{
	insertarInicio(&(G->A[v-1]),w);	
}
*/
void agregar_arista_peso(TDAGrafoLA *G, int v, int w, int peso)
{

	insertarInicioTripleta(&(G->A[v-1]), v, w,peso);	
}

//NoDirigido Ponderado
TDAGrafoLA* leerGrafoNoDirigidoPond(char *nombreArchivo)
{
	FILE*pf;		   					
	pf = fopen(nombreArchivo,"r");
	int n_vertices, m_aristas, peso;
	int i,j,k,p;
	if (pf ==NULL)
	{
		printf("Error de archivo\n");
		return NULL;
	}
	else
	{
		//Cantidad de nodos y aristas
		fscanf(pf, "%d %d", &n_vertices,&m_aristas); 		
		TDAGrafoLA *G=crearGrafoVacio(n_vertices);	
		G->n=n_vertices;
		G->m=m_aristas;
		//dependiendo de las lineas de archivo, 
		for(k=0;k<m_aristas;k++)
		{
			fscanf(pf,"%d %d %d",&i, &j, &p);
			agregar_arista_peso(G, i, j, p);
			agregar_arista_peso(G, j, i, p);			
		}
		fclose(pf);
		return  G;	
	}
}

TDAlista obtenerAdyacentes(TDAGrafoLA* grafo, int vertice)
{
	TDAlista adyacentes=crearListaVacia();
	nodoTripleta* aux= grafo->A[vertice-1];
	while (aux!=NULL) 
	{
		insertarInicio(&adyacentes, aux->fin);
		aux=aux->puntero;		
	}
	return(adyacentes);
}

//Actividades asíncronas
int adyacenciaNodos(TDAGrafoLA* G, int vertice1, int vertice2);
int esCompleto(TDAGrafoLA* G);
int esCamino(TDAGrafoLA* G, TDAlista* secuencia);
int esComplemento(TDAGrafoLA* G1, TDAGrafoLA* G2);
int gradodeVertice(TDAGrafoLA* G, int vertice);
int gradoPromedio(TDAGrafoLA* G); 
int esRegular(TDAGrafoLA* G); 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++

/*-------- semana 9 -------------*/

void marcarVisitado(TDAlista* visitados, int vertice)
{
  nodo* nuevo = (nodo*)malloc(sizeof(nodo));
  nuevo->dato = vertice;
  nuevo->puntero = *visitados;
  *visitados = nuevo;
}
int adyacenteNoVisitado(TDAlista* adyacentes, TDAlista* visitados) {
    nodo* aux_adyacentes = *adyacentes;

    while (aux_adyacentes != NULL) {
        nodo* aux_visitados = *visitados;
        int encontrado = 0;

        while (aux_visitados != NULL) {
            if (aux_adyacentes->dato == aux_visitados->dato) {
                encontrado = 1;
                break;
            }
            aux_visitados = aux_visitados->puntero;
        }

        if (!encontrado) {
            return aux_adyacentes->dato;
        }

        aux_adyacentes = aux_adyacentes->puntero;
    }

    return -1;
}
void recorridoDFS(TDAGrafoLA* grafo, int inicio)
{
    int topePila, w;
    TDAlista adyacentes;

    // Definir tipo de dato de "visitados"
    TDAlista visitados = NULL;

    TDApila* pila = crearPilaVacia(grafo->n);
    apilar(pila, inicio);
    marcarVisitado(&visitados, inicio);

    while (!esPilaVacia(pila)) {
        topePila = tope(pila)->dato;
        adyacentes = obtenerAdyacentes(grafo, topePila);
        w = adyacenteNoVisitado(&adyacentes, &visitados);

        if (w != -1) {
            printf(" -> %d", w);
            apilar(pila, w);
            marcarVisitado(&visitados, w);
        } else {
            printf(" <- %d", topePila);
            desapilar(pila);
        }
    }
    printf("\n");
}
int estaVisitado(TDAlista* visitados, int vertice)
{
    nodo* aux_visitados = *visitados;
    while (aux_visitados != NULL) {
        if (vertice == aux_visitados->dato) {
            return 1;  // Vértice ya visitado
        }
        aux_visitados = aux_visitados->puntero;
    }

    return 0;  // Vértice no visitado
}
void recorridoBFS(TDAGrafoLA* grafo, int vertice)
{
	int frenteCola,w;
    TDAlista adyacentes;
    
    //definir tipo de dato de "visitados"
	TDAlista visitados = crearListaVacia();

	TDAcola* cola = crearColaVacia(grafo->n);
	encolar(cola, vertice);
	while(!esColaVacia(cola))
	{
		frenteCola=mirar(cola);
		desencolar(cola);
		printf("visitando: %d\n", frenteCola);
		marcarVisitado(&visitados, frenteCola);	
		adyacentes=obtenerAdyacentes(grafo,frenteCola);
		while(adyacentes!=NULL)
		{
			w=adyacentes->dato;
			if (!(estaVisitado(&visitados, w))){
				encolar(cola,w);
			}
			adyacentes=adyacentes->puntero;
		}
	}
	printf("\n");
}

/*-------- semana 10 -----------*/

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
    int minDistancia = 9999;
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

void dijkstra(Grafo* grafo, int inicio, TDAlista visitados, int* distancias) {
    int n = grafo->n;

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
}

TDAlista* mstPrim(TDAGrafoLA* grafo, int inicio); //TDAlistaTripleta* 
TDAlista* msrtKruskal(TDAGrafoLA* grafo); //TDAlistaTripleta*
