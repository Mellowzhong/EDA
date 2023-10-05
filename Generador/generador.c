#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILAS 40
#define COLUMNAS 40
#define PALABRAS 50
#define LONGITUD_MAXIMA 20

void generarSopa(char sopa[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            sopa[i][j] = 'a' + rand() % 26;  // letras aleatorias de la A a la Z
        }
    }
}

void generarPalabras(char palabras[PALABRAS][LONGITUD_MAXIMA]) {
    // Lista de palabras en español de ejemplo
    char listaPalabras[PALABRAS][LONGITUD_MAXIMA] = {
        "manzana", "plátano", "naranja", "uva", "cereza", "melón", "fresa", "arándano", "kiwi", "piña",
        "pera", "sandía", "limón", "mandarina", "frambuesa", "pomelo", "ciruela", "mango", "granada", "papaya",
        "albaricoque", "coco", "higo", "calabaza", "avellana", "chirimoya", "coco", "dátil", "nuez", "caqui",
        "zarzamora", "membrillo", "guayaba", "guanábana", "café", "tamarindo", "canela", "chocolate", "aceituna", "coco",
        "durazno", "maracuyá", "fruta de la pasión", "guayaba", "fruta del dragón", "carambola", "grosella", "nectarina", "mora", "zapote"
    };

    for (int i = 0; i < PALABRAS; ++i) {
        strcpy(palabras[i], listaPalabras[i]);
    }
}

void guardarArchivoSopa(char sopa[FILAS][COLUMNAS]) {
    FILE *archivo = fopen("30.txt", "w");

    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            fprintf(archivo, "%c ", sopa[i][j]);
        }
        fprintf(archivo, "\n");
    }

    fclose(archivo);
}

void guardarArchivoPalabras(char palabras[PALABRAS][LONGITUD_MAXIMA]) {
    FILE *archivo = fopen("palabras.txt", "w");

    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < PALABRAS; ++i) {
        fprintf(archivo, "%s\n", palabras[i]);
    }

    fclose(archivo);
}

int main() {
    srand(time(NULL));

    char sopa[FILAS][COLUMNAS];
    char palabras[PALABRAS][LONGITUD_MAXIMA];

    generarSopa(sopa);
    generarPalabras(palabras);

    guardarArchivoSopa(sopa);
    guardarArchivoPalabras(palabras);

    printf("Archivos generados exitosamente.\n");

    return 0;
}