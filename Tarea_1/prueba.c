#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
char** leerArchivoMatriz(char* fileName, int* x, int* y){
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
char** leerArchivoPalabras(char* fileName, int* size_array_words){

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

void comprobation_right(char** matrix, int filas, int columnas, char* word, int y, int x){

    char** copy_matrix = copyArray(matrix, filas, columnas);
    int len_word = strlen(word);

    for(int i = 0; i < len_word; i++){
        if(matrix[y][x] == word[i]){
            printf("se cumplio: %c,%c\n", matrix[y][x], word[i]);
            matrix[y][x] == '*';
            x++;
        }else{
            printf("no se cumplio: %c,%c\n", matrix[y][x], word[i]);
            return;
        }
        printf("%c\n", word[i]);
    }
    printf("palabra pasada: %s\n", word);
}

int findWords(char** matrix, int filas, int columnas, char** array_words, int size_array_words){
    for (int k = 0; k < size_array_words; k++){//recorro la lista de las palabras
        //recorro la matriz
        for (int y = 0; y < columnas; y++){
            for (int x = 0; x < filas; x++){
                printf("[%c]", matrix[y][x]);
                printf("array_word[%c]\n", array_words[k][0]);
                if(matrix[y][x] == array_words[k][0]){
                    printf("word: %s\n", array_words[k]);
                    printf("iguales: %c,%c\n", array_words[k][0],matrix[y][x]);                    
                    printf("posicion: y:%d, x:%d\n", y, x);
                    comprobation_right(matrix, filas, columnas, array_words[k], y, x);
                    //terminar las demas comprobaciones en las otras direcciones
                }
            }
        }
    }
    return 0;
}

int main() {
    
    int filas, columnas, size_array_words;
    char matrix_fileName[100];
    char words_fileName[100];

    printf("Ingrese el nombre del archivo con la sopa de letras:\n");
    scanf("%s", matrix_fileName);

    printf("Ingrese el nombre del archivo con las palabras:\n");
    scanf("%s", words_fileName);

    //un arreglo que contiene una lista con caracteres
    char** matrix = leerArchivoMatriz(matrix_fileName, &filas, &columnas);

    show_matriz(matrix, filas, columnas);

    //un arreglo que contiene una lista de caracteres(las palabras)
    char** array_words = leerArchivoPalabras(words_fileName, &size_array_words);

    show_array(array_words, size_array_words);

    printf("\n");

    int result = findWords(matrix, filas, columnas, array_words, size_array_words);

    printf("%d", result);

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
