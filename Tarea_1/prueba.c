#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_matriz(char** matriz, int x, int y){

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            printf("[%c]", matriz[i][j]);
        }
        printf("\n");
    }
}

void imprimir(char* arreglo, int n){
    int i;
    for(i = 0; i < n; i++){
        printf("%c ", arreglo[i]);
    }
    printf("\n");
}

char** leerArchivoMatriz(char* fileName, int* x, int* y){
    FILE* file;
    char **matriz;
    int filas, columnas;
    int i, j;

    file = fopen(fileName, "r");

    if (file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        exit(1);
    }

    fscanf(file, "%d %d", &filas, &columnas);

    matriz = (char **)malloc(filas * sizeof(char *));
    for (i = 0; i < filas; i++) {
        matriz[i] = (char *)malloc(columnas * sizeof(char));
    }

    for (i = 0; i < filas; i++) {
        for (j = 0; j < columnas; j++) {
            fscanf(file, " %c", &matriz[i][j]); 
        }
    }

    fclose(file);

    *x = filas;
    *y = columnas;

    return matriz;
}

void leerArchivoPalabras(char* fileName, int* size_array){

    FILE *archivo = fopen(fileName, "r");

    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        exit(1);
    }

    int cantidadPalabras;
    fscanf(archivo, "%d", &cantidadPalabras);
    fgetc(archivo); // Consumir el carácter de nueva línea después del número

    char **listaPalabras = (char **)malloc(cantidadPalabras * sizeof(char *));
    if (listaPalabras == NULL) {
        perror("Error al asignar memoria");
        exit(1);
    }

    char linea[100];

    for (int i = 0; i < cantidadPalabras; i++) {
        if (fgets(linea, sizeof(linea), archivo) != NULL) {
            linea[strcspn(linea, "\n")] = '\0'; // Eliminar el carácter de nueva línea si está presente
            listaPalabras[i] = strdup(linea); // Almacenar la palabra en la lista
        } else {
            fprintf(stderr, "Error al leer la línea %d\n", i + 2);
        }
    }

    fclose(archivo);

    *size_array = cantidadPalabras;

    // Imprimir la lista de palabras
    printf("Lista de palabras:\n");
    for (int i = 0; i < cantidadPalabras; i++) {
        printf("[%s]", listaPalabras[i]);
        free(listaPalabras[i]); // Liberar la memoria asignada para cada palabra
    }

    free(listaPalabras); // Liberar la memoria de la lista de punteros

}

int main() {
    
    int filas, columnas, size_words;

    char** matriz = leerArchivoMatriz("tablero1.ini", &filas, &columnas);

    show_matriz(matriz, filas, columnas);

    leerArchivoPalabras("lista1.lst", &size_words);

    for (int i = 0; i < filas; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}
