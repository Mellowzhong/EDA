#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct wordNode{
    char* word;
    struct wordNode *next;
}wordNode;

typedef struct wordList{  
    wordNode* head;
}wordList;

//Entrada: la lista
//Salida: void
//Descripcion: borra el primer nodo de la lista
void delateIniList(wordList* lista){
  wordNode* auxiliar = lista->head;
  if(!(lista->head == NULL)){
    lista->head = (lista->head)->next;
    free(auxiliar);
  }
}

//Entrada: la lista
//Salida: void
//Descripcion: libera la lista
void freeWordList(wordList* lista){
  while (!(lista->head == NULL)){
    delateIniList(lista);
  }
}

//Entrada:void
//Salida: lista
//Descripcion: inicializa una lista
wordList* createWordList(){
    wordList* new_wordList = (wordList*)malloc(sizeof(wordList));
    new_wordList->head = NULL;

    return new_wordList;
}

//Entrada: la lista - palabra a agregar
//Salida: void
//Descripcion: agrega una palabra a la lista
void insertElementToList(wordList* wordLista, char* word) {
    wordNode* nuevo = (wordNode*)malloc(sizeof(wordNode));
    
    nuevo->word = (char*)malloc(strlen(word) + 1);
    strcpy(nuevo->word, word);
    nuevo->next = NULL;

    if (wordLista->head == NULL) {
        wordLista->head = nuevo;
    }else{
        wordNode* aux = wordLista->head;
        while (aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = nuevo;
    }
}

//Entrada: nombre del archivo - largo del arreglo de las palabras
//Salida: arreglo que contiene una arreglo de caracteres
//Descripcion: Lee un archivo y crea un arreglo con las palabras dadas en este mismo
void readFileWords(wordList* wordLista, char* fileName, int* size_array_words){

    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error: No se pudo abrir el archivo de las palabras.\n");
        exit(1);
    }

    char line[100];  // Tamaño máximo de una línea
    int wordCount;

    if (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d", &wordCount);

        for (int i = 0; i < wordCount; i++) {
            if (fgets(line, sizeof(line), file) != NULL) {
                line[strcspn(line, "\n")] = '\0';  // Eliminar el carácter de nueva línea si está presente
                insertElementToList(wordLista, line);
            }
        }
    } 
    fclose(file);

    *size_array_words = wordCount;

    printf("Se pudo leer correctamente el archivo de las palabras\n");
}