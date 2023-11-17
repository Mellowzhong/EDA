#include "T1_FranciscoSanchez_Matriz.h"
#include "T1_FranciscoSanchez_Palabras.h"
#include <time.h>

// Entrada: arreglo de arreglos de characteres - rows de la matriz - columns de la matriz - nombre del file
// Salida: void
// Descripcion: agrega la matriz solucion al file correspondiente
void write_matrix(MatrixList *matrix, int rows, int columns, char *matrix_name){

    FILE *file = fopen(matrix_name, "a");
    MatrixNode *current = matrix->head;
    int current_rows = 1;
    int current_columns = 1;

    if (file == NULL){ // Si no se logra abrir el file finaliza
        printf("Error al abrir el archivo de salida de la sopa de letras");
        exit(1);
    }

    while (current != NULL){
        fprintf(file, "%c ", current->character);

        current = current->next;
        current_columns++;

        if (current_columns > columns){
            fprintf(file, "\n");
            current_rows++;
            current_columns = 1;
        }
    }

    fprintf(file, "\n");
    fclose(file);
}

// Entrada: palara a agregar - rows de la matriz - columns de la matriz - nombre del file
// Salida: void
// Descripcion: agrega una Palabra al file correspondiente
void write_word(char *word, int y, int x, char *list_name){

    FILE *file = fopen(list_name, "r+");
    int current_count;
    char line[100];

    if (file == NULL){ // Si no se logra abrir el file finaliza
        printf("Error al abrir el archivo de salida de las palabras");
        exit(1);
    }

    if (fscanf(file, "%d", &current_count) != 1){ // si el numero inicial es 0 finaliza
        printf("Error al leer la cantidad current de elementos");
        fclose(file);
        exit(1);
    }

    current_count++;

    // aqui seteo el nuevo contador
    fseek(file, 0, SEEK_SET);
    fprintf(file, "%d", current_count);

    // aqui seteo el nuevo dato a agregar al final del file
    fseek(file, 0, SEEK_END);
    fprintf(file, "%d %d (%s)\n", y + 1, x + 1, word);

    fclose(file);
}

// Entrada: nombre del archivo - palabra a buscar
// Salida: 0 o 1 dependiendo si se encontro la palabra o no
// Descripcion: Lee un archivo para buscar si en este mismo existe ya la palabra dada o no
int comprobation_word(char *list_name, char *word){
    int x, y;
    char word_aux[100];

    FILE *file = fopen(list_name, "r");

    if (file == NULL){
        printf("Error al abrir el file para comprobar si la Palabra existe o no");
        exit(1);
    }

    int size_words;
    fscanf(file, "%d", &size_words);
    fgetc(file);

    wordList *array_words = createWordList();

    // Copia las Palabras del file al arreglo
    char line[100];
    for (int i = 0; i < size_words; i++){
        if (fgets(line, sizeof(line), file) != NULL){
            line[strcspn(line, "\n")] = '\0';

            // sscanf para poder sacar la Palabra
            //  %99: cantidad de characteres a leer
            //[^)] excluye el character de cerrar parentesis
            if (sscanf(line, "%d %d (%99[^)])", &x, &y, word_aux) == 3)
            {
                insertElementToList(array_words, word_aux);
            }
        }
    }

    wordNode *auxiliar = array_words->head;

    while (auxiliar != NULL){
        if (strcmp(word, auxiliar->word) == 0){
            fclose(file);
            return 0;
        }
        printf("%s ", auxiliar->word);
        auxiliar = auxiliar->next;
    }

    fclose(file);

    freeWordList(array_words);

    return 1;
}

// Entrada: matriz - filas de la matriz - columnas de la matriz
//  - palabra a buscar - nombre del archivo donde se gurdaran las palabras
//  - nombre del archivo donde se guardaran las matrices solucion - filas de la matriz - columnas de la matriz
// Salida: void
// Descripcion: comprueba a la derecha en la sopa de letras si la palabra se encuentra en esa posicion
void findWordRight(MatrixList *matrix, int rows, int columns, char *word, char *list_name, char *matrix_name, int passRows, int passColumns){
    MatrixList *copy_matrix = copyMatrix(matrix);
    int len_word = strlen(word);
    int passRows_aux = passRows;
    int passColumns_aux = passColumns;

    for (int i = 0; i < len_word; i++){
        char current_char = word[i];
        char getter_char = getCharByCoord(copy_matrix, rows, columns, passRows_aux, passColumns_aux);
        if (current_char != getter_char){
            freeMatrixList(copy_matrix);
            return;
        }

        passColumns_aux = passColumns_aux + 1;
    }
    write_word(word, passRows, passColumns, list_name);
    write_matrix(copy_matrix, rows, columns, matrix_name);
    freeMatrixList(copy_matrix);
}

// Entrada: matriz - filas de la matriz - columnas de la matriz
//  - palabra a buscar - nombre del archivo donde se gurdaran las palabras
//  - nombre del archivo donde se guardaran las matrices solucion - filas de la matriz - columnas de la matriz
// Salida: void
// Descripcion: comprueba a la derecha y arriba en la sopa de letras si la palabra se encuentra en esa posicion
void findWordUpperRight(MatrixList *matrix, int rows, int columns, char *word, char *list_name, char *matrix_name, int passRows, int passColumns){
    MatrixList *copy_matrix = copyMatrix(matrix);
    int len_word = strlen(word);
    int passRows_aux = passRows;
    int passColumns_aux = passColumns;

    for (int i = 0; i < len_word; i++){
        char current_char = word[i];
        char getter_char = getCharByCoord(copy_matrix, rows, columns, passRows_aux, passColumns_aux);
        if (current_char != getter_char){
            freeMatrixList(copy_matrix);
            return;
        }
        passRows_aux = passRows_aux - 1;
        passColumns_aux = passColumns_aux + 1;
    }
    write_word(word, passRows, passColumns, list_name);
    write_matrix(copy_matrix, rows, columns, matrix_name);
    freeMatrixList(copy_matrix);
}

// Entrada: matriz - filas de la matriz - columnas de la matriz
//  - palabra a buscar - nombre del archivo donde se gurdaran las palabras
//  - nombre del archivo donde se guardaran las matrices solucion - filas de la matriz - columnas de la matriz
// Salida: void
// Descripcion: comprueba arriba en la sopa de letras si la palabra se encuentra en esa posicion
void findWordUpper(MatrixList *matrix, int rows, int columns, char *word, char *list_name, char *matrix_name, int passRows, int passColumns){
    MatrixList *copy_matrix = copyMatrix(matrix);
    int len_word = strlen(word);
    int passRows_aux = passRows;
    int passColumns_aux = passColumns;

    for (int i = 0; i < len_word; i++){
        char current_char = word[i];
        char getter_char = getCharByCoord(copy_matrix, rows, columns, passRows_aux, passColumns_aux);
        if (current_char != getter_char){
            freeMatrixList(copy_matrix);
            return;
        }

        passRows_aux = passRows_aux - 1;
    }
    write_word(word, passRows, passColumns, list_name);
    write_matrix(copy_matrix, rows, columns, matrix_name);
    freeMatrixList(copy_matrix);
}

// Entrada: matriz - filas de la matriz - columnas de la matriz
//  - palabra a buscar - nombre del archivo donde se gurdaran las palabras
//  - nombre del archivo donde se guardaran las matrices solucion - filas de la matriz - columnas de la matriz
// Salida: void
// Descripcion: comprueba a la izquierda y arriba en la sopa de letras si la palabra se encuentra en esa posicion
void findWordUpperLeft(MatrixList *matrix, int rows, int columns, char *word, char *list_name, char *matrix_name, int passRows, int passColumns){
    MatrixList *copy_matrix = copyMatrix(matrix);
    int len_word = strlen(word);
    int passRows_aux = passRows;
    int passColumns_aux = passColumns;

    for (int i = 0; i < len_word; i++){
        char current_char = word[i];
        char getter_char = getCharByCoord(copy_matrix, rows, columns, passRows_aux, passColumns_aux);
        if (current_char != getter_char){
            freeMatrixList(copy_matrix);
            return;
        }
        passRows_aux = passRows_aux - 1;
        passColumns_aux = passColumns_aux - 1;
    }
    write_word(word, passRows, passColumns, list_name);
    write_matrix(copy_matrix, rows, columns, matrix_name);
    freeMatrixList(copy_matrix);
}

// Entrada: matriz - filas de la matriz - columnas de la matriz
//  - palabra a buscar - nombre del archivo donde se gurdaran las palabras
//  - nombre del archivo donde se guardaran las matrices solucion - filas de la matriz - columnas de la matriz
// Salida: void
// Descripcion: comprueba a la izquierda en la sopa de letras si la palabra se encuentra en esa posicion
void findWordLeft(MatrixList *matrix, int rows, int columns, char *word, char *list_name, char *matrix_name, int passRows, int passColumns){
    MatrixList *copy_matrix = copyMatrix(matrix);
    int len_word = strlen(word);
    int passRows_aux = passRows;
    int passColumns_aux = passColumns;

    for (int i = 0; i < len_word; i++){
        char current_char = word[i];
        char getter_char = getCharByCoord(copy_matrix, rows, columns, passRows_aux, passColumns_aux);
        if (current_char != getter_char){
            freeMatrixList(copy_matrix);
            return;
        }

        passColumns_aux = passColumns_aux - 1;
    }
    write_word(word, passRows, passColumns, list_name);
    write_matrix(copy_matrix, rows, columns, matrix_name);
    freeMatrixList(copy_matrix);
}

// Entrada: matriz - filas de la matriz - columnas de la matriz
//  - palabra a buscar - nombre del archivo donde se gurdaran las palabras
//  - nombre del archivo donde se guardaran las matrices solucion - filas de la matriz - columnas de la matriz
// Salida: void
// Descripcion: comprueba a la izquierda y abajo en la sopa de letras si la palabra se encuentra en esa posicion
void findWordDownLeft(MatrixList *matrix, int rows, int columns, char *word, char *list_name, char *matrix_name, int passRows, int passColumns){
    MatrixList *copy_matrix = copyMatrix(matrix);
    int len_word = strlen(word);
    int passRows_aux = passRows;
    int passColumns_aux = passColumns;

    for (int i = 0; i < len_word; i++){
        char current_char = word[i];
        char getter_char = getCharByCoord(copy_matrix, rows, columns, passRows_aux, passColumns_aux);
        if (current_char != getter_char){
            freeMatrixList(copy_matrix);
            return;
        }
        passRows_aux = passRows_aux + 1;
        passColumns_aux = passColumns_aux - 1;
    }
    write_word(word, passRows, passColumns, list_name);
    write_matrix(copy_matrix, rows, columns, matrix_name);
    freeMatrixList(copy_matrix);
}

// Entrada: matriz - filas de la matriz - columnas de la matriz
//  - palabra a buscar - nombre del archivo donde se gurdaran las palabras
//  - nombre del archivo donde se guardaran las matrices solucion - filas de la matriz - columnas de la matriz
// Salida: void
// Descripcion: comprueba abajo en la sopa de letras si la palabra se encuentra en esa posicion
void findWordDown(MatrixList *matrix, int rows, int columns, char *word, char *list_name, char *matrix_name, int passRows, int passColumns){
    MatrixList *copy_matrix = copyMatrix(matrix);
    int len_word = strlen(word);
    int passRows_aux = passRows;
    int passColumns_aux = passColumns;

    for (int i = 0; i < len_word; i++){
        char current_char = word[i];
        char getter_char = getCharByCoord(copy_matrix, rows, columns, passRows_aux, passColumns_aux);
        if (current_char != getter_char){
            freeMatrixList(copy_matrix);
            return;
        }
        passRows_aux = passRows_aux + 1;
    }
    write_word(word, passRows, passColumns, list_name);
    write_matrix(copy_matrix, rows, columns, matrix_name);
    freeMatrixList(copy_matrix);
}

// Entrada: matriz - filas de la matriz - columnas de la matriz
//  - palabra a buscar - nombre del archivo donde se gurdaran las palabras
//  - nombre del archivo donde se guardaran las matrices solucion - filas de la matriz - columnas de la matriz
// Salida: void
// Descripcion: comprueba a la derecha y abajo en la sopa de letras si la palabra se encuentra en esa posicion
void findWordDownRight(MatrixList *matrix, int rows, int columns, char *word, char *list_name, char *matrix_name, int passRows, int passColumns){
    MatrixList *copy_matrix = copyMatrix(matrix);
    int len_word = strlen(word);
    int passRows_aux = passRows;
    int passColumns_aux = passColumns;
    for (int i = 0; i < len_word; i++){
        char current_char = word[i];
        char getter_char = getCharByCoord(copy_matrix, rows, columns, passRows_aux, passColumns_aux);
        if (current_char != getter_char){
            freeMatrixList(copy_matrix);
            return;
        }
        passRows_aux = passRows_aux + 1;
        passColumns_aux = passColumns_aux + 1;
    }

    write_word(word, passRows, passColumns, list_name);
    write_matrix(copy_matrix, rows, columns, matrix_name);
    freeMatrixList(copy_matrix);
}

// Entrada: la matriz - filas de la matriz - columnas de la matriz - lista de las palabras -
//  - nombre del archivo de las palabras - nombre del archivo de las matrices
// Salida: void
// Descripcion: comprueba si una palabra existe en la sopa de letras
void findWords(MatrixList *matrix, int rows, int columns, wordList *array_words, char *list_name, char *matrix_name){
    wordNode *words = array_words->head;
    while (words != NULL){
        MatrixNode *current = matrix->head;
        int current_rows = 0;
        int current_columns = 0;
        while (current != NULL){
            if (current->character == words->word[0]){
                findWordRight(matrix, rows, columns, words->word, list_name, matrix_name, current_rows, current_columns);
                findWordUpperRight(matrix, rows, columns, words->word, list_name, matrix_name, current_rows, current_columns);
                findWordUpper(matrix, rows, columns, words->word, list_name, matrix_name, current_rows, current_columns);
                findWordUpperLeft(matrix, rows, columns, words->word, list_name, matrix_name, current_rows, current_columns);
                findWordLeft(matrix, rows, columns, words->word, list_name, matrix_name, current_rows, current_columns);
                findWordDownLeft(matrix, rows, columns, words->word, list_name, matrix_name, current_rows, current_columns);
                findWordDown(matrix, rows, columns, words->word, list_name, matrix_name, current_rows, current_columns);
                findWordDownRight(matrix, rows, columns, words->word, list_name, matrix_name, current_rows, current_columns);
            }
            current = current->next;
            current_columns++;

            if (current_columns > columns){
                current_rows++;
                current_columns = 0;
            }
        }
        words = words->next;
    }
}

int main(int argc, char *argv[]){
    int rows, columns, size_array_words, final_size_array_words;
    clock_t cini, cfin;
    double tiempo;
    char *matrix_fileName = argv[1];
    char *words_fileName = argv[2];
    MatrixList *matrix = createMatrix();
    wordList *wordList = createWordList();

    readFileWords(wordList, words_fileName, &size_array_words);
    recorrerLista(wordList);
    readFileMatrix(matrix, matrix_fileName, &rows, &columns);

    // se crean los nombres de los files de salida
    char *matrix_name = strtok(matrix_fileName, ".");
    strcat(matrix_name, ".out");

    char *list_name = strtok(words_fileName, ".");
    strcat(list_name, ".out");

    // Abro el file de salida de las Palabras para iniciar el contador
    FILE *file = fopen(list_name, "w");
    fprintf(file, "0\n");
    fclose(file);

    cini = clock();
    findWords(matrix, rows, columns, wordList, list_name, matrix_name);
    cfin = clock();
    tiempo = (double)(cfin - cini) / CLOCKS_PER_SEC;

    printf("El tiempo que se demoro en encontar todas las palabras es: %f\n", tiempo);

    file = fopen(list_name, "r");
    fscanf(file, "%d", &final_size_array_words);
    fclose(file);

    printf("Se pudo completar la busqueda exitosamente\n");
    printf("numero de palabras buscadas: %d \nnumero de palabras encoentradas: %d\n", size_array_words, final_size_array_words);
    printf("Los archivos de salida son: %s y %s", matrix_name, list_name);

    freeWordList(wordList);
    freeMatrixList(matrix);
    return 0;
}