#include <stdio.h>
#include <stdlib.h>

/*------------- estructura de datos -------------*/

typedef struct nodoGenericoTripleta
{
  int peso;
  int fin;
  struct nodoGenericoTripleta* puntero;
}nodoTripleta;

typedef nodoTripleta* TDAlistaTripleta;

/*------------- operaciones -------------*/

TDAlistaTripleta crearListaVaciaTripleta()
{
  TDAlistaTripleta lista=(TDAlistaTripleta)malloc(sizeof(TDAlistaTripleta));
  lista=NULL;
  return lista;
}

int esListaVaciaTripleta(TDAlistaTripleta* lista)
{
  if (lista == NULL)
    return 1;
  else
    return 0;
}

void insertarInicioTripleta(TDAlistaTripleta* lista, int dato, int fin, int peso)
{
  nodoTripleta* nuevo=(nodoTripleta*)malloc(sizeof(nodoTripleta));
  nuevo->peso=peso;
  nuevo->fin = fin;
  nuevo->puntero=*lista;
  *lista=nuevo;
}

void recorrerListaTripleta(TDAlistaTripleta lista)
{
  if (!esListaVaciaTripleta(&lista))
  {
    nodoTripleta* auxiliar=lista;
    while (auxiliar!=NULL)
    {
      printf("fin:%d peso:%d ",auxiliar->fin, auxiliar->peso);
      auxiliar=auxiliar->puntero;
    }
    printf("\n");
  }
  else
    printf("La lista está vacía\n");
}