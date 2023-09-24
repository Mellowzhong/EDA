#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void write_matrix(char** matrix, int filas, int columnas, char* matrix_name){
    FILE *archivo = fopen(matrix_name, "a");
    for(int i = 0; i < columnas; i++){
        for (int j = 0; j < filas; j++){
            fprintf(archivo, "[%c]", matrix[i][j]);
        }
        fprintf(archivo, "\n");
    }
    fprintf(archivo, "\n");
    fclose(archivo);
}

void write_word(char* word, int y, int x, char* list_name){
    FILE *archivo = fopen(list_name, "a");
    fprintf(archivo,"%d %d (%s)\n", y+1, x+1, word);
    fclose(archivo);
}

//Entrada: arreglo de enteros - filas de la matriz - columnas de la matriz
//Salida: arreglo de enteros
//Descripcion: Copio los datos del array dado a uno auxiliar
char** copyArray(char** array, int filas, int columnas){
    char** aux = (char**)malloc(filas * sizeof(char*));
    for (int i = 0; i < columnas; i++){
        aux[i] = (char*)malloc(columnas * sizeof(char));
    }
    
    for(int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            aux[i][j] = array[i][j];
        }
    }

    return aux;
}

char** crar_matriz(int filas, int columnas){
    char** new = (char **)malloc(columnas * sizeof(char *));

    for (int i = 0; i < columnas; i++) {
        new[i] = (char *)malloc(filas * sizeof(char)); 
    }

    return new;
}

//Entrada: arreglo que contiene un arreglo de caracteres - filas de la matriz - columnas de la matriz
//Salida: void
//Descripcion: Imprime en pantalla la matriz dada dado
void show_matriz(char** matriz, int x, int y){

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            printf("[%c]", matriz[i][j]);
        }
        printf("\n");
    }
}

//Entrada: arreglo que contiene un arreglo de caracteres - largo del arreglo dado
//Salida: void
//Descripcion: Imprime en pantalla el array dado
void show_array(char** arreglo, int n){
    for(int i = 0; i < n; i++){
        printf("%s ", arreglo[i]);
    }
}

//Entrada: nombre del archivo - filas - columnas
//Salida: arreglo que contiene una arreglo de caracteres 
//Descripcion: lee un archivo y entrega una matriz con los caracteres dados en este
char** readFileMatrix(char* fileName, int* x, int* y){
    FILE* file;
    int filas, columnas;
    int i, j;

    file = fopen(fileName, "r");

    if (file == NULL) { //Si no se puede abrir el archivo se finaliza
        printf("No se pudo abrir el archivo de la sopa de letras\n");
        exit(1);
    }

    fscanf(file, "%d %d", &filas, &columnas);

    char** matriz = crar_matriz(filas, columnas);

    //copia los caracteres a la matriz
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

//Entrada: nombre del archivo - largo del arreglo de las palabras
//Salida: arreglo que contiene una arreglo de caracteres
//Descripcion: Lee un archivo y crea un arreglo con las palabras dadas en este mismo
char** readFileWords(char* fileName, int* size_array_words){

    FILE *file = fopen(fileName, "r");
    char line[100];
    int size_words;

    if (file == NULL) { //Si no se puede abrir el archivo se finaliza
        printf("Error al abrir el archivo de las palabras");
        exit(1);
    }
    fscanf(file, "%d", &size_words);
    fgetc(file);

    char **array_words = (char **)malloc(size_words * sizeof(char *));

    //copia las palabras del archivo al arreglo
    for (int i = 0; i < size_words; i++) {
        if (fgets(line, sizeof(line), file) != NULL) {
            line[strcspn(line, "\n")] = '\0';
            array_words[i] = strdup(line); 
        }
    }

    fclose(file);

    *size_array_words = size_words; 

    return array_words;
}

void comprobation_right(char** matrix, int filas, int columnas, char* word, int y, int x, char* list_name, char* matrix_name) {
    char** copy_matrix = copyArray(matrix, filas, columnas);
    int len_word = strlen(word);
    int y_aux = y;
    int x_aux = x;
    for (int i = 0; i <= len_word; i++) {
        if(i == len_word){
            write_word(word, y_aux , x_aux, list_name);
            write_matrix(copy_matrix, filas, columnas, matrix_name);
        }
        if (x < 0 || x >= columnas || y < 0 || y >= filas || matrix[y][x] != word[i]) {
            return;
        }
        copy_matrix[y][x] = '*';
        x++;
    }
}

void comprobation_upper_right(char** matrix, int filas, int columnas, char* word, int y, int x, char* list_name, char* matrix_name) {
    char** copy_matrix = copyArray(matrix, filas, columnas);
    int len_word = strlen(word);
    int y_aux = y;
    int x_aux = x;
    for (int i = 0; i <= len_word; i++) {
        if(i == len_word){
            write_word(word, y_aux , x_aux, list_name);
            write_matrix(copy_matrix, filas, columnas, matrix_name);
        }
        if (x < 0 || x >= columnas || y < 0 || y >= filas || matrix[y][x] != word[i]) {
            return;
        }
        copy_matrix[y][x] = '*';
        x++;
        y--;
    }
}

void comprobation_upper(char** matrix, int filas, int columnas, char* word, int y, int x, char* list_name, char* matrix_name) {
    char** copy_matrix = copyArray(matrix, filas, columnas);
    int len_word = strlen(word);
    int y_aux = y;
    int x_aux = x;
    for (int i = 0; i <= len_word; i++) {
        if(i == len_word){
            write_word(word, y_aux , x_aux, list_name);
            write_matrix(copy_matrix, filas, columnas, matrix_name);
        }
        if (x < 0 || x >= columnas || y < 0 || y >= filas || matrix[y][x] != word[i]) {
            return;
        }
        copy_matrix[y][x] = '*';
        y--;
    }
}

void comprobation_upper_left(char** matrix, int filas, int columnas, char* word, int y, int x, char* list_name, char* matrix_name) {
    char** copy_matrix = copyArray(matrix, filas, columnas);
    int len_word = strlen(word);
    int y_aux = y;
    int x_aux = x;
    for (int i = 0; i <= len_word; i++) {
        if(i == len_word){
            write_word(word, y_aux , x_aux, list_name);
            write_matrix(copy_matrix, filas, columnas, matrix_name);
        }
        if (x < 0 || x >= columnas || y < 0 || y >= filas || matrix[y][x] != word[i]) {
            return;
        }
        copy_matrix[y][x] = '*';
        x--;
        y--;
    }
}
void comprobation_left(char** matrix, int filas, int columnas, char* word, int y, int x, char* list_name, char* matrix_name) {
    char** copy_matrix = copyArray(matrix, filas, columnas);
    int len_word = strlen(word);
    int y_aux = y;
    int x_aux = x;
    for (int i = 0; i <= len_word; i++) {
        if(i == len_word){
            write_word(word, y_aux , x_aux, list_name);
            write_matrix(copy_matrix, filas, columnas, matrix_name);
        }
        if (x < 0 || x >= columnas || y < 0 || y >= filas || matrix[y][x] != word[i]) {
            return;
        }
        copy_matrix[y][x] = '*';
        x--;
    }
}

void comprobation_down_left(char** matrix, int filas, int columnas, char* word, int y, int x, char* list_name, char* matrix_name) {
    char** copy_matrix = copyArray(matrix, filas, columnas);
    int len_word = strlen(word);
    int y_aux = y;
    int x_aux = x;
    for (int i = 0; i <= len_word; i++) {
        if(i == len_word){
            write_word(word, y_aux , x_aux, list_name);
            write_matrix(copy_matrix, filas, columnas, matrix_name);
        }
        if (x < 0 || x >= columnas || y < 0 || y >= filas || matrix[y][x] != word[i]) {
            return;
        }
        copy_matrix[y][x] = '*';
        x--;
        y++;
    }
}

void comprobation_down(char** matrix, int filas, int columnas, char* word, int y, int x, char* list_name, char* matrix_name) {
    char** copy_matrix = copyArray(matrix, filas, columnas);
    int len_word = strlen(word);
    int y_aux = y;
    int x_aux = x;
    for (int i = 0; i <= len_word; i++) {
        if(i == len_word){
            write_word(word, y_aux , x_aux, list_name);
            write_matrix(copy_matrix, filas, columnas, matrix_name);
        }
        if (x < 0 || x >= columnas || y < 0 || y >= filas || matrix[y][x] != word[i]) {
            return;
        }
        copy_matrix[y][x] = '*';
        y++;
    }
}

void comprobation_down_right(char** matrix, int filas, int columnas, char* word, int y, int x, char* list_name, char* matrix_name) {
    char** copy_matrix = copyArray(matrix, filas, columnas);
    int len_word = strlen(word);
    int y_aux = y;
    int x_aux = x;
    for (int i = 0; i <= len_word; i++) {
        if(i == len_word){
            write_word(word, y_aux , x_aux, list_name);
            write_matrix(copy_matrix, filas, columnas, matrix_name);
        }
        if (x < 0 || x >= columnas || y < 0 || y >= filas || matrix[y][x] != word[i]) {
            return;
        }
        copy_matrix[y][x] = '*';
        x++;
        y++;
    }
}

void findWords(char** matrix, int filas, int columnas, char** array_words, int size_array_words, char* list_name, char* matrix_name){
    for (int k = 0; k < size_array_words; k++){//recorro la lista de las palabras
        //recorro la matriz
        for (int y = 0; y < columnas; y++){
            for (int x = 0; x < filas; x++){
                if(matrix[y][x] == array_words[k][0]){
                    comprobation_right(matrix, filas, columnas, array_words[k], y, x, list_name, matrix_name);
                    comprobation_upper_right(matrix, filas, columnas, array_words[k], y, x, list_name, matrix_name);
                    comprobation_upper(matrix, filas, columnas, array_words[k], y, x, list_name, matrix_name);
                    comprobation_upper_left(matrix, filas, columnas, array_words[k], y, x, list_name, matrix_name);
                    comprobation_left(matrix, filas, columnas, array_words[k], y, x, list_name, matrix_name);
                    comprobation_down_left(matrix, filas, columnas, array_words[k], y, x, list_name, matrix_name);
                    comprobation_down(matrix, filas, columnas, array_words[k], y, x, list_name, matrix_name);
                    comprobation_down_right(matrix, filas, columnas, array_words[k], y, x, list_name, matrix_name);
                }
            }
        }
    }
}

int main() {
    
    int filas, columnas, size_array_words, final_size_array_words;
    char matrix_fileName[100];
    char words_fileName[100];

    printf("Ingrese el nombre del archivo con la sopa de letras:\n");
    scanf("%s", matrix_fileName);

    printf("Ingrese el nombre del archivo con las palabras:\n");
    scanf("%s", words_fileName);

    //un arreglo que contiene una lista con caracteres
    char** matrix = readFileMatrix(matrix_fileName, &filas, &columnas);

    //un arreglo que contiene una lista de caracteres(las palabras)
    char** array_words = readFileWords(words_fileName, &size_array_words);

    char* matrix_name = strtok(matrix_fileName, ".");
    strcat(matrix_name, ".out");

    char* list_name = strtok(words_fileName, ".");
    strcat( list_name, ".out");

    FILE *archivo = fopen(list_name, "w");
    fprintf(archivo, "0\n");
    fclose(archivo);

    findWords(matrix, filas, columnas, array_words, size_array_words, list_name, matrix_name);

    //se libera la memoria
    for (int i = 0; i < filas; i++) {
        free(matrix[i]);
    }
    free(matrix);

    for(int i = 0; i < size_array_words; i++){
        free(array_words[i]);
    }
    free(array_words);

    return 0;
}
