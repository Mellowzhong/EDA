#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Entrada: arreglo de arreglos de caracteres - filas de la matriz - columnas de la matriz - nombre del archivo
//Salida: void
//Descripcion: agrega la matriz solucion al archivo correspondiente
void write_matrix(char** matrix, int filas, int columnas, char* matrix_name){
    FILE *archivo = fopen(matrix_name, "a");

    for(int i = 0; i < columnas; i++){
        for (int j = 0; j < filas; j++){
            fprintf(archivo, "%c", matrix[i][j]);
        }
        fprintf(archivo, "\n");
    }
    fprintf(archivo, "\n");
    fclose(archivo);
}

//Entrada: palara a agregar - filas de la matriz - columnas de la matriz - nombre del archivo
//Salida: void
//Descripcion: agrega una palabra al archivo correspondiente
void write_word(char* word, int y, int x, char* list_name){

    FILE *archivo = fopen(list_name, "r+");
    int current_count = 0;

    if (archivo == NULL){ //Si no se logra abrir el archivo finaliza
        printf("Error al abrir el archivo de las palabras");   
        exit(1);
    }

    if (fscanf(archivo, "%d", &current_count) != 1){ //si el numero inicial es 0 finaliza
        printf("Error al leer la cantidad actual de elementos");
        fclose(archivo);
        exit(1);
    }

    current_count++;

    //aqui seteo el nuevo contador
    fseek(archivo, 0, SEEK_SET);
    fprintf(archivo, "%d", current_count);

    //aqui seteo el nuevo dato a agregar al final del archivo
    fseek(archivo, 0, SEEK_END);
    fprintf(archivo, "\n%d %d (%s)", y + 1, x + 1, word);

    fclose(archivo);
}

//Entrada: filas de la matriz - columnas de la matriz
//Salida: una matriz
//Descripcion: se arega el largo y el ancho, y se guarda memoria para crear la matriz
char** create_matrix(int filas, int columnas){
    char** new = (char **)malloc(columnas * sizeof(char *));

    for (int i = 0; i < columnas; i++) {
        new[i] = (char *)malloc(filas * sizeof(char)); 
    }

    return new;
}

//Entrada: arreglo de enteros - filas de la matriz - columnas de la matriz
//Salida: arreglo de enteros
//Descripcion: Copio los datos del array dado a uno auxiliar
char** copyArray(char** array, int filas, int columnas){
    char** aux = create_matrix(filas, columnas);
    
    //recorro la matriz
    for(int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            aux[i][j] = array[i][j];
        }
    }

    return aux;
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
        printf("No se pudo abrir el archivo de la sopa de letras, no se encontro\n");
        exit(1);
    }

    fscanf(file, "%d %d", &filas, &columnas);

    if(filas == 0 || columnas == 0) {
        printf("Error en los datos de las filas y las columnas, por favor revisar archivo");
        exit(1);
    }

    char** matriz = create_matrix(filas, columnas);

    //copia los caracteres a la matriz
    for (i = 0; i < filas; i++) {
        for (j = 0; j < columnas; j++) {
            fscanf(file, " %c", &matriz[i][j]); 
        }
    }

    fclose(file);

    *x = filas;
    *y = columnas;


    printf("Se pudo leer el archivo de la sopa de letras correctamente\n");
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
        printf("Error al abrir el archivo de las palabras, no se encontro\n");
        exit(1);
    }

    fscanf(file, "%d", &size_words);
    fgetc(file);

    if(size_words == 0){
        printf("No hay letras que obtener, revise el archivo");
        exit(1);
    }

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

    printf("Se pudo leer correctamente el archivo de las palabras\n");
    return array_words;
}

//Entrada: matriz - filas de la matriz - columnas de la matriz 
        // - palabra a buscar - posicion y - posicion x - nombre del archivo donde se gurdaran las palabras
        // - nombre del archivo donde se guardaran las matrices solucion
//Salida: void
//Descripcion: comprueba a la derecha en la sopa de letras si la palabra se encuentra en esa posicion
void comprobation_right(char** matrix, int filas, int columnas,
                        char* word, int y, int x, char* list_name, char* matrix_name) {
    char** copy_matrix = copyArray(matrix, filas, columnas);
    int len_word = strlen(word);

    for (int i = 0; i <= len_word; i++) {
        if(i == len_word){
            write_word(word, y , x, list_name);
            write_matrix(copy_matrix, filas, columnas, matrix_name);
        }
        if (x < 0 || x >= columnas || y < 0 || y >= filas || matrix[y][x] != word[i]) {
            return;
        }
        copy_matrix[y][x] = '*';
        x++;
    }

    free(copy_matrix);
    for(int i = 0; i < columnas; i++){
        free(copy_matrix[i]);
    }
}

//Entrada: matriz - filas de la matriz - columnas de la matriz 
        // - palabra a buscar - posicion y - posicion x - nombre del archivo donde se gurdaran las palabras
        // - nombre del archivo donde se guardaran las matrices solucion
//Salida: void
//Descripcion: comprueba a la derecha y arriba en la sopa de letras si la palabra se encuentra en esa posicion
void comprobation_upper_right(char** matrix, int filas, int columnas,
                              char* word, int y, int x, char* list_name, char* matrix_name) {
    char** copy_matrix = copyArray(matrix, filas, columnas);
    int len_word = strlen(word);
    int y_aux = y;
    int x_aux = x;

    //recorro la palabra
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

    free(copy_matrix);
    for(int i = 0; i < columnas; i++){
        free(copy_matrix[i]);
    }
}

//Entrada: matriz - filas de la matriz - columnas de la matriz 
        // - palabra a buscar - posicion y - posicion x - nombre del archivo donde se gurdaran las palabras
        // - nombre del archivo donde se guardaran las matrices solucion
//Salida: void
//Descripcion: comprueba arriba en la sopa de letras si la palabra se encuentra en esa posicion
void comprobation_upper(char** matrix, int filas, int columnas,
                         char* word, int y, int x, char* list_name, char* matrix_name) {
    char** copy_matrix = copyArray(matrix, filas, columnas);
    int len_word = strlen(word);
    int y_aux = y;
    int x_aux = x;

    //recorro la palabra
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

    free(copy_matrix);
    for(int i = 0; i < columnas; i++){
        free(copy_matrix[i]);
    }
}

//Entrada: matriz - filas de la matriz - columnas de la matriz 
        // - palabra a buscar - posicion y - posicion x - nombre del archivo donde se gurdaran las palabras
        // - nombre del archivo donde se guardaran las matrices solucion
//Salida: void
//Descripcion: comprueba arriba y a la izquierda en la sopa de letras si la palabra se encuentra en esa posicion
void comprobation_upper_left(char** matrix, int filas, int columnas,
                             char* word, int y, int x, char* list_name, char* matrix_name) {
    char** copy_matrix = copyArray(matrix, filas, columnas);
    int len_word = strlen(word);
    int y_aux = y;
    int x_aux = x;

    //recorro la palabra
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

    free(copy_matrix);
    for(int i = 0; i < columnas; i++){
        free(copy_matrix[i]);
    }
}

//Entrada: matriz - filas de la matriz - columnas de la matriz 
        // - palabra a buscar - posicion y - posicion x - nombre del archivo donde se gurdaran las palabras
        // - nombre del archivo donde se guardaran las matrices solucion
//Salida: void
//Descripcion: comprueba a la izquierda en la sopa de letras si la palabra se encuentra en esa posicion
void comprobation_left(char** matrix, int filas, int columnas,
                      char* word, int y, int x, char* list_name, char* matrix_name) {
    char** copy_matrix = copyArray(matrix, filas, columnas);
    int len_word = strlen(word);
    int y_aux = y;
    int x_aux = x;

    //recorro la palabra
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

    free(copy_matrix);
    for(int i = 0; i < columnas; i++){
        free(copy_matrix[i]);
    }
}

//Entrada: matriz - filas de la matriz - columnas de la matriz 
        // - palabra a buscar - posicion y - posicion x - nombre del archivo donde se gurdaran las palabras
        // - nombre del archivo donde se guardaran las matrices solucion
//Salida: void
//Descripcion: comprueba abajo a la izquierda en la sopa de letras si la palabra se encuentra en esa posicion
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

    free(copy_matrix);
    for(int i = 0; i < columnas; i++){
        free(copy_matrix[i]);
    }
}

//Entrada: matriz - filas de la matriz - columnas de la matriz 
        // - palabra a buscar - posicion y - posicion x - nombre del archivo donde se gurdaran las palabras
        // - nombre del archivo donde se guardaran las matrices solucion
//Salida: void
//Descripcion: comprueba abajo en la sopa de letras si la palabra se encuentra en esa posicion
void comprobation_down(char** matrix, int filas, int columnas, 
                        char* word, int y, int x, char* list_name, char* matrix_name) {
    char** copy_matrix = copyArray(matrix, filas, columnas);
    int len_word = strlen(word);
    int y_aux = y;
    int x_aux = x;

    //recorro la palabra
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

    free(copy_matrix);
    for(int i = 0; i < columnas; i++){
        free(copy_matrix[i]);
    }
}

//Entrada: arreglo de arreglos de caracteres - filas de la matriz - columnas de la matriz 
        // - palabra a buscar - posicion y - posicion x - nombre del archivo donde se gurdaran las palabras
        // - nombre del archivo donde se guardaran las matrices solucion
//Salida: void
//Descripcion: comprueba abajo a la derecha en la sopa de letras si la palabra se encuentra en esa posicion
void comprobation_down_right(char** matrix, int filas, int columnas,
                             char* word, int y, int x, char* list_name, char* matrix_name) {
    char** copy_matrix = copyArray(matrix, filas, columnas);
    int len_word = strlen(word);
    int y_aux = y;
    int x_aux = x;

    //recorro la palabra
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

    free(copy_matrix);
    for(int i = 0; i < columnas; i++){
        free(copy_matrix[i]);
    }
}

//Entrada: la matriz - filas de la matriz - columnas de la matriz - arreglo de las palabras - 
        // - tamaño del arreglo de las palabras - nombre del archivo de las palabras - nombre del archivo de las matrices
//Salida: void
//Descripcion: comprueba a la derecha en la sopa de letras si la palabra se encuentra en esa posicion
void findWords(char** matrix, int filas, int columnas, char** array_words, int size_array_words, char* list_name, char* matrix_name){
    for (int k = 0; k < size_array_words; k++){//recorro la lista de las palabras
        //recorro la matriz
        for (int y = 0; y < columnas; y++){
            for (int x = 0; x < filas; x++){
                if(matrix[y][x] == array_words[k][0]){//se buscan las soluciones
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

int main(int argc, char * argv[]) {
    int filas, columnas, size_array_words, final_size_array_words;

    char* matrix_fileName = argv[1];
    char* words_fileName = argv[2];

    //un arreglo que contiene una lista con caracteres
    char** matrix = readFileMatrix(matrix_fileName, &filas, &columnas);

    //un arreglo que contiene una lista de caracteres(las palabras)
    char** array_words = readFileWords(words_fileName, &size_array_words);

    //se crean los nombres de los archivos de salida
    char* matrix_name = strtok(matrix_fileName, ".");
    strcat(matrix_name, ".out");

    char* list_name = strtok(words_fileName, ".");
    strcat( list_name, ".out");

    FILE *file = fopen(list_name, "w");
    fprintf(file, "0\n");
    fclose(file);

    //Encuentras la palabras en la sopa de letras y las manda a su archivo de salida correspondiente
    findWords(matrix, filas, columnas, array_words, size_array_words, list_name, matrix_name);

    file = fopen(list_name, "r");
    fscanf(file, "%d", &final_size_array_words);
    fclose(file);

    printf("Se pudo completar la busqueda exitosamente\n");
    printf("numero de palabras buscadas: %d \nnumero de palabras encoentradas: %d\n", size_array_words, final_size_array_words);
    printf("Los archivos de salida son: %s y %s", matrix_name, list_name);

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