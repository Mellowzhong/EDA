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

/*------------- operaciones -------------*/

TDAGrafoLA* crearGrafoVacio(int n)
{
	int i;

	TDAGrafoLA* G=malloc(sizeof(TDAGrafoLA));
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
  nuevo->puntero = NULL;

  if (esListaVacia(*visitados)) {
    *visitados = nuevo;
  } else {

    nodo* aux = *visitados;
    while (aux->puntero != NULL) {
      aux = aux->puntero;
    }
    aux->puntero = nuevo;
  }
  printf("se visito: %d\n", vertice);
}

int adyacenteNoVisitado(TDAlista adyacentes, TDAlista* visitados)
{
	nodo* aux_adyacentes = *visitados;
	while (aux_adyacentes != NULL)
	{
		nodo* aux_visitados = *visitados;
		while (aux_visitados->puntero != NULL)
		{
			if (aux_adyacentes->dato != aux_visitados->dato)
			{
				return aux_adyacentes->dato;
			}
			aux_visitados = aux_visitados->puntero;
		}
		aux_adyacentes = aux_adyacentes->puntero;
	}
	
	return -1;
}

void recorridoDFS(TDAGrafoLA* grafo, int inicio)
{
	int topePila,w,i;
	TDAlista adyacentes;

	//definir tipo de dato de "visitados"
	TDAlista visitados = crearListaVacia();

	TDApila* pila=crearPilaVacia(grafo->n);
	apilar(pila,inicio);
	marcarVisitado(&visitados,inicio);
	
	while (!(esPilaVacia(pila)))
	{
		topePila=tope(pila)->dato;
		adyacentes=obtenerAdyacentes(grafo,topePila);
		w=adyacenteNoVisitado(adyacentes,&visitados);
		if (w!=-1)
		{
			apilar(pila,w);
			marcarVisitado(&visitados,w);
		}
		else
		{
			desapilar(pila);
		}
	}
	printf("\n");
}

/*-------- Actividad 3: aplicación DFS -------------*/ 


/*-------- Actividad 4: BFS -------------

int estaVisitado(int vertice)
{
	return 1;
}

void recorridoBFS(TDAGrafoLA* grafo, int vertice)
{
	int frenteCola,w;
    TDAlista adyacentes;
    
    //definir tipo de dato de "visitados"

	TDAcola* cola = crearColaVacia(grafo->n);
	encolar(cola, vertice);
	while(!esColaVacia(*cola))
	{
		frenteCola=frente(*cola)->dato;
		descolar(cola);
		//marcarVisitado(frenteCola);	
		adyacentes=obtenerAdyacentes(grafo,frenteCola);
		while(adyacentes!=NULL)
		{
			w=adyacentes->dato;
			if (!(estaVisitado(w)))
				encolar(cola,w);
			adyacentes=adyacentes->puntero;
		}
	}
	printf("\n");
}

/*-------- Actividad 5: aplicación BFS -------------*/ 