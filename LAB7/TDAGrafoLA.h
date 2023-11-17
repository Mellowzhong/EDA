/* grafo no dirigido no ponderado usando LISTA DE ADYACENCIA */
#include <stdio.h>
#include <stdlib.h>
#include "TDAlista.h"
#include "TDApila.h"
#include "TDAcola.h"

/*------------- estructura de datos -------------*/

struct grafo
{
	TDAlista* A; 					//Arreglo donde cada celda representa un vertice y de tipo Lista
	int* V;							//Arreglo donde cada celda representa un vertice y de tipo entero
	int n; 							//número de vértices del grafo
	int m; 							//numero de aristas del grafo
};

typedef struct grafo TDAGrafoLA;

typedef struct NodoColaPrioridad {
    int vertice;
    int prioridad;
} NodoColaPrioridad;

typedef struct ColaPrioridad {
    NodoColaPrioridad* elementos;
    int capacidad;
    int tamaño;
} ColaPrioridad;

/*------------- operaciones -------------*/

void insertarNodoFinal(TDAlista* lista, int dato) {
  nodo* nuevo = (nodo*)malloc(sizeof(nodo));
  nuevo->dato = dato;
  nuevo->puntero = NULL;

  if (esListaVacia(*lista)) {
    *lista = nuevo;
  } else {

    nodo* aux = *lista;
    while (aux->puntero != NULL) {
      aux = aux->puntero;
    }
    aux->puntero = nuevo;
  }
}

TDAGrafoLA* crearGrafoVacio(int n)
{
	int i;

	TDAGrafoLA* G= (TDAGrafoLA*)malloc(sizeof(TDAGrafoLA));
    G->A = (TDAlista*)malloc(sizeof(TDAlista)*n);
    G->V = (int*)malloc(sizeof(int)*n);

	for (i=0; i<n; i++)
	{
      G->A[i] = crearListaVacia(); 
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
		recorrerLista(G->A[i]);
	}
}

void agregar_arista(TDAGrafoLA* G, int v, int w)
{
	insertarInicio(&(G->A[v-1]),w);	
}

//NoDirigido NoPonderado
TDAGrafoLA* leerGrafoNoDirigido(char *nombreArchivo)
{
	int n_vertices, m_aristas;
	int i,j,k;
	TDAGrafoLA* G;

	FILE* pf=fopen(nombreArchivo,"r");
	if (pf ==NULL)
	{
		printf("Error de archivo\n");
		return NULL;
	}
	else
	{
		//Cantidad de vértices y aristas
		fscanf(pf, "%d %d", &n_vertices,&m_aristas); 		
		G=crearGrafoVacio(n_vertices);	
		G->n=n_vertices;
		G->m=m_aristas;
		
		for(k=0;k<m_aristas;k++)
		{
			fscanf(pf,"%d %d",&i, &j);
			agregar_arista(G, i, j);
			agregar_arista(G, j, i);			
		}
		fclose(pf);
		return  G;	
	}
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

//-------- Actividad 2: DFS -------------

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

/*-------- Actividad 3: aplicación DFS -------------*/ 


//-------- Actividad 4: BFS -------------

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

/*-------- Actividad 5: aplicación BFS -------------*/ 
