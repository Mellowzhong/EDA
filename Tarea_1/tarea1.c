#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Entrada: el nombre del archivo del tablero
//Descripcion: crea un arreglo con las dimensiones del tablero
//Salida: El arreglo con las dimensiones

int * cantidad_fila_Y_columnas(char * Nombretablero){
    //n y m están en la primera linea del archivo
    FILE * tablero;

    tablero = fopen(Nombretablero,"r");
    if(tablero == NULL){
        printf("No se pudo abrir el archivo\n");
    exit(1);
    }else{
        printf("Se logro abrir con exito\n");
    }
    int *dimension_tablero = (int *)malloc(2 * sizeof(int));
    fscanf(tablero, "%d" "%d",&dimension_tablero[0], &dimension_tablero[1]); //saca el primer valor de la primera linea 
    printf("N = %d M = %d \n", dimension_tablero[0], dimension_tablero[1]);

    fclose(tablero);

    return dimension_tablero;

}

//Entrada: el nombre del archivo de la lista
//Descripcion: extrae la cantidad de palabras del archivo
//Salida: un int 
int cantidad_palabrasFUN(char * nombreLista){
        FILE * lista;

    lista = fopen(nombreLista,"r");
    if(lista == NULL){
        printf("No se pudo abrir el archivo\n");
    exit(1);
    }else{
        printf("Se logro abrir con exito\n");
    }

    int cantidad_palabras;
    fscanf(lista, "%d",&cantidad_palabras); //saca el primer valor de la primera linea y lo almacena en cantidad_palabras
    printf("%d \n", cantidad_palabras);

    return cantidad_palabras;
}


//Entrada: el nombre del archivo del tablero
//Descripcion: Crea una matriz con la sopa de letras que está dentro del archivo .ini
//Salida: El arreglo con el tablero

char ** leerTablero (char * NombreTablero){
    //n y m están en la primera linea del archivo
    FILE * tablero;

    tablero = fopen(NombreTablero,"r");
    if(tablero == NULL){
        printf("No se pudo abrir el archivo\n");
    exit(1);
    }else{
        printf("Se logro abrir con exito\n");
    }

    //ver como saco esto, ya que está en la otra función
    //creación de matriz hasra linea 37
    int cantidad_filas;
    int cantidad_columnas;
    fscanf(tablero, "%d" "%d",&cantidad_filas, &cantidad_columnas); //saca el primer valor de la primera linea 
    printf("n = %d m = %d \n", cantidad_filas, cantidad_columnas);

    int i,j;    
    char **array_tablero;
    array_tablero = (char **)malloc(cantidad_filas * sizeof(char*));


    for(i = 0; i < cantidad_filas; i++){
        array_tablero[i] = (char *)malloc(cantidad_columnas * sizeof(char));
          if (array_tablero[i] == NULL) {
            printf("Error: No se pudo reservar memoria para las columnas.\n");
            exit(1);
        }
    }
    
    //ciclo que almacena los caracteres del archivo en la matriz
    for(i = 0; i < cantidad_filas; i++){
        for(j = 0; j < cantidad_columnas; j++){
            fscanf(tablero, " %c", &array_tablero[i][j]); 
        }
    }

    fclose(tablero);

    //impresión de matriz con los valores ya agregados
    for(i = 0; i < cantidad_filas; i++){
        for(j = 0; j < cantidad_columnas; j++){
            printf("%c ", array_tablero[i][j]);
        }
        printf("\n");
    }

    return array_tablero;
    //liberación de memoria
    /*for (int i = 0; i < cantidad_filas; i++) {
        free(array_tablero[i]);
    }
    free(array_tablero); */
}

//Entrada: El archivo lista que contiene las palabras a encontrar
//Descripcion: función que abre y lee el archivo de lista y crea un arreglo con todas las palabras dentro
//Salida: Arreglo con las palabras a encontrar

char ** leerLista (char * NombreLista){
    FILE * lista;

    lista = fopen(NombreLista,"r");
    if(lista == NULL){
        printf("No se pudo abrir el archivo\n");
    exit(1);
    }else{
        printf("Se logro abrir con exito\n");
    }

    int cantidad_palabras;
    fscanf(lista, "%d",&cantidad_palabras); //saca el primer valor de la primera linea y lo almacena en cantidad_palabras
    //printf("%d \n", cantidad_palabras);


    int i,j;    
    char **array_palabras;
    array_palabras = (char **)malloc(cantidad_palabras * sizeof(char*));

    //ciclo que almacena los caracteres del archivo en la matriz
    
    for (i = 0; i < cantidad_palabras; i++) {
        int longitud_palabra;
        fscanf(lista, "%d", &longitud_palabra); // Lee la longitud de la palabra
        array_palabras[i] = (char *)malloc((longitud_palabra + 1) * sizeof(char));
        fscanf(lista, "%s", array_palabras[i]);
    }

    fclose(lista);

    //impresión del arreglo con las palabras
    /*for(i = 0; i < cantidad_palabras; i++){
        printf("%s ", array_palabras[i]);
        printf("\n");
    }*/

    //me imprime el primer caracter
    /*for(i = 0; i < cantidad_palabras; i++){
        printf("%c ", array_palabras[i][0]);
        printf("\n");
    }*/

    return array_palabras;

}


/*char ** horizontal(char ** tablero, char ** listaPalabras, int fila, int columna, int cantidad_palabras){
 int i,j,k,z;
    int tamano_palabra; //strlen
    //y si tengo que hacer 4 ciclos?????
    //obtener los caracteres

    //int encontrado = 0; // Bandera para verificar si se encontró la letra

    //estos dos for me sirven para recorrer el tablero completo y me da todas las p*/

void horizontal(char **tablero, char **listaPalabras, int fila, int columna, int cantidad_palabras) {
    int i, j, k, z;
    int tamano_palabra;
    for (k = 0; k < cantidad_palabras; k++) {
    tamano_palabra = strlen(listaPalabras[k]);
            for (i = 0; i < fila; i++) {
                for (j = 0; j < columna; j++) {
                    if (listaPalabras[k][0] == tablero[i][j]) {
                        for (z = 0; z < tamano_palabra; z++) {
                            if (i >= 0 && i < fila && j >= 0 && j < columna) {
                                if (i >= 0 && i < fila && (j + 1) >= 0 && (j + 1) < columna) {
                                    if (listaPalabras[k][z + 1] == tablero[i][j + 1]) {
                                        printf("se encontro la palabra a la der %c %c\n", listaPalabras[k][z + 1], tablero[i][j + 1]);
                                    }
                                }
                                if (i >= 0 && i < fila && (j - 1) >= 0 && (j - 1) < columna) {
                                    if (listaPalabras[k][z + 1] == tablero[i][j - 1]) {
                                        printf("se encontro la palabra a la izq %c %c\n", listaPalabras[k][z + 1], tablero[i][j - 1]);
                                    }
                                }
                                
                            }
                        }
                    }
                }
            }
        
    }
}



int main(int argc, char *argv[]){
    int *dimensiones_tablero = cantidad_fila_Y_columnas("tablero1.ini");
    int cantidad_palabras_lista = cantidad_palabrasFUN("lista1.lst");
    //printf("cantidad palabras: %i\n", cantidad_palabras_lista);

    /*for(int i = 0; i < 2; i++){
        printf("array 1: %i\n", dimensiones_tablero[i]);
    }*/

    char **prueba = leerTablero("tablero1.ini");

    //printf("%c",prueba);

    char ** prueba1 = leerLista("lista1.lst");
    horizontal(prueba, prueba1, dimensiones_tablero[0], dimensiones_tablero[1], cantidad_palabras_lista);

    


    return 0;
}
