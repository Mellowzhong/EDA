#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MatrixNode{
    char character;
    struct MatrixNode *next;
} MatrixNode;

typedef struct MatrixList{
    MatrixNode *head;
} MatrixList;

//Entrada: la matriz
//Salida: void
//Descripcion: borra el primer nodo de la lista (matriz)
void delateIniMatrix(MatrixList *matrix){
    MatrixNode *auxiliar = matrix->head;
    if (!(matrix->head == NULL)){
        matrix->head = (matrix->head)->next;
        free(auxiliar);
    }
}

//Entrada: la matriz
//Salida: void
//Descripcion: libera la lista (matriz)
void freeMatrixList(MatrixList *matrix){
    while (!(matrix->head == NULL)){
        delateIniMatrix(matrix);
    }
}

//Entrada:void
//Salida: lista (matriz)
//Descripcion: inicializa una lista (matriz)
MatrixList* createMatrix(){
    MatrixList *matrix = (MatrixList *)malloc(sizeof(MatrixList));
    matrix->head = NULL;
    return matrix;
}

//Entrada: la matriz - caracter a agregar
//Salida: void
//Descripcion: agrega un caracter a la lista (matriz)
void insertElementToMatrix(MatrixList *matrix, char dato){
    MatrixNode *nuevo = (MatrixNode *)malloc(sizeof(MatrixNode));
    nuevo->character = dato;
    nuevo->next = NULL;

    if (matrix->head == NULL){
        matrix->head = nuevo;
    }
    else{

        MatrixNode *aux = matrix->head;
        while (aux->next != NULL){
            aux = aux->next;
        }
        aux->next = nuevo;
    }
}

//Entrada: la matriz
//Salida: lista (matriz)
//Descripcion: copia la matriz dada en una nueva
MatrixList* copyMatrix(MatrixList *matrix){
    MatrixList* nuevaLista = createMatrix();
    MatrixNode* current = matrix->head;

    while (current != NULL){
        insertElementToMatrix(nuevaLista, current->character);
        current = current->next;
    }

    return nuevaLista;
}

//Entrada: matriz donde se almacenaran los datos - nombre del archivo - filas - columnas
//Salida: arreglo que contiene una arreglo de caracteres 
//Descripcion: lee un archivo y entrega una matriz con los caracteres dados en este
void readFileMatrix(MatrixList *matrix, char* fileName, int *rows, int *columns){
    FILE* file = fopen(fileName, "r");

    if (file == NULL){
        printf("No se pudo abrir el archivo de la sopa de letras");
        exit(1);
    }

    // Leer las dimensiones (rows y columns)
    fscanf(file, "%d %d", rows, columns);

    // Consumir el salto de línea después de las dimensiones
    fgetc(file);

    char character;
    while ((character = fgetc(file)) != EOF){
        if (character != ' ' && character != '\n' && character != '\t'){
            insertElementToMatrix(matrix, character);
        }
    }

    fclose(file);

    printf("Se pudo leer el archivo de la sopa de letras correctamente\n");
}

//Entrada: matriz - filas de la matriz - columnas de la matriz 
            //- fila en donde se desdea encontrar el caracter - columna en donde se desdea encontrar el caracter
//Salida: caracter encontrado
//Descripcion: va recorriendo la matriz, cuando las columnas y filas coincidan con las actuales devuelve el caracter
char getCharByCoord(MatrixList *matrix, int rows, int columns, int passRow, int passColumn){
    MatrixNode* current = matrix->head;
    int current_row = 0;
    int current_column = 0;
    
    while (current != NULL){
        if (current_row == passRow && current_column == passColumn){
            char aux = current->character;
            current->character = '*';
            return aux;
        }

        // Avanza al siguiente carácter
        current = current->next;
        current_column++;

        if (current_column > columns){
            current_row++;
            current_column = 0;
        }
    }
}