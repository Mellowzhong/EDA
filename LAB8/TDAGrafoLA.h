/* grafo no dirigido no ponderado usando LISTA DE ADYACENCIA */
#include <stdio.h>
#include <stdlib.h>
#include "TDAlista.h" 
#include "TDAcola.h"
#include "TDAcolaTripleta.h"
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

int existenVerticesSinVisitar(int* arreglo, int largo) {
    for (int i = 0; i < largo; i++){
        if (arreglo[i] == 0){
            return 1;
        }
    }
    return 0;
}

int noVisitadoDistanciaMinima(int* distancia, int* visitados, int n) {
    int minDistancia = 9999;
    int vertice = -1;

    for (int i = 0; i < n; i++) {
        if (!visitados[i] && distancia[i] < minDistancia){
            minDistancia = distancia[i];
            vertice = i;
        }
    }

    return vertice;
}

void dijkstra(TDAGrafoLA* grafo, int inicio, int* anterior, int* distancia) {
    int n = grafo->n;

    int* visitados = (int*)malloc(grafo->n*(sizeof(int)));

    for (int i = 0; i < n; i++) {
        visitados[i] = 0;
        anterior[i] = -1;
        distancia[i] = 9999;
    }
    int i = 0;
    TDAlista adyacentes = obtenerAdyacentes(grafo, inicio);
    distancia[inicio] = 0;

    while (adyacentes != NULL){
        anterior[i] = 0;
        if (adyacentes->dato > 0){
            distancia[i] = (grafo->A[i])->peso;
            anterior[i] = inicio;
        }else{
            distancia[i] = 9999;
        }
        adyacentes = adyacentes->puntero;
    }
    distancia[inicio] = 0;
    visitados[inicio] = 1;

    while(existenVerticesSinVisitar(visitados, grafo->n)){
        int u = noVisitadoDistanciaMinima(distancia, visitados, grafo->n);
        visitados[u] = 1;
        adyacentes = obtenerAdyacentes(grafo, u+1);
        while (adyacentes != NULL){
            int v = adyacentes->dato;
            if(distancia[v] > distancia[u] + (grafo->A[u])->peso){
                distancia[v] = distancia[u] + (grafo->A[u])->peso;
                anterior[v] = u;
            }
            adyacentes = adyacentes->puntero;
        }
    }
}


//Prim
int buscarDato(TDAlista MST, int elegido){
    while (MST != NULL){
        if (MST->dato == elegido){
            return 1;
        }
    }
    return 0;
}


TDAlista mstPrim(TDAGrafoLA* grafo, int inicio) {
    TDAlista MST = crearListaVacia();
    int n = grafo->n;
    TDAcolaTripleta* candidatos = crearColaVaciaTripleta(grafo->n);
    int cuenta = 1;
    int u = inicio;
    int* visitados = (int*)malloc(grafo->n*(sizeof(int)));
    visitados[u] = 1;
    insertarNodoFinal(&MST, u);

    while (cuenta < n){
        TDAlista adyacentes = obtenerAdyacentes(grafo, u);
        
        while (adyacentes != NULL){
            int v = adyacentes->dato;
            encolarTripleta(candidatos, u, (grafo->A[v])->peso);
            adyacentes = adyacentes->puntero;
        }
                            
        nodocolatripleta* elegido = mirarTripleta(candidatos);
        while (buscarDato(MST, elegido->fin)){
            desencolarTripleta(candidatos);
            elegido = mirarTripleta(candidatos);
        }
        if (elegido != NULL){
            visitados[elegido->fin] = 1;
            insertarNodoFinal(&MST, elegido->fin);
            desencolarTripleta(candidatos);
            cuenta++;
            u = elegido->fin;
        }
    }
    return MST;
}
//kruskall
Arista* ordenarAristas(Grafo* grafo) {
    //por hacer
}

int existeCiclo(LSE MST, Arista arista) {
    int inicio = arista.inicio;
    int fin = arista.fin;

    int* conjuntoVertices = (int*)malloc((inicio + fin) * sizeof(int));
    for (int i = 0; i < inicio + fin; i++) {
        conjuntoVertices[i] = -1;
    }

    Nodo* temp = MST;
    while (temp != NULL) {
        conjuntoVertices[temp->dato] = temp->dato;
        temp = temp->siguiente;
    }

    if (conjuntoVertices[inicio] == conjuntoVertices[fin]) {
        free(conjuntoVertices);
        return 1;
    }

    free(conjuntoVertices);
    return 0;
}

TDAlista kruskal(TDAGrafoLA* grafo) {
    TDAlista MST = crearListaVacia();
    nodoGenerico* colaAristas = ordenarAristas(grafo);
    int inicio = 1;

    while (!esColaVacia(colaAristas)) {
        Arista arista = frente(colaAristas);
        desencolar(colaAristas);

        if (inicio == 1) {
            insertarNodoFinal(&MST, arista.fin);
            inicio = 0;
        } else {
            if (!existeCiclo(MST, arista)) {
                insertarNodoFinal(&MST, arista.fin);
            }
        }
    }

    free(colaAristas);

    return MST;
}
