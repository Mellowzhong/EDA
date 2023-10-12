#ifndef TDA_LC_h
#define TDA_LC_h

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int data;
    struct nodo *next;
    
}Nodo;

typedef struct list{  
    Nodo* head;
    int count;

}List;

int is_void_list(List* list){
    if(list->head == NULL){
        return 1;
    }
    return 0;
}

List* create_list(){
    List* new_list = (List*)malloc(sizeof(List));
    new_list->head = NULL;
    new_list->count = 0;

    return new_list;
}

Nodo* crear_nodo(int value){
    Nodo* new_nodo = (Nodo*)malloc(sizeof(Nodo));

    new_nodo->data = value;
    new_nodo->next = NULL;
    
    return new_nodo;
}

void show_list(List list){
    Nodo* aux = list.head;
    Nodo* inicio = aux;
    int count = 0;
    printf("\nData->");

    while (count != list.count){
        printf("%d\n", aux->data);
        aux = aux->next;
        count++;
    }
}

void agregar_nodo_ini(List* list, int value){
    Nodo* new_nodo = crear_nodo(value);
    new_nodo->next = list->head;

    list->head = new_nodo;
    list->count = list->count + 1;
}

void agregar_nodo_final(List* list, int value){
    Nodo* aux = list->head;
    printf("nodos: %d", list->count);

    while(aux->next != NULL){
        aux = aux->next;
    }

    Nodo* new_nodo = crear_nodo(value);
    aux->next = new_nodo;
    list->count = list->count + 1;
}

void agregar_nodo(List* list, int value, int search_value){
    Nodo* new_nodo = crear_nodo(value);
    Nodo* aux = list->head;
    Nodo* before = NULL;
    Nodo* inicio = list->head;

    if (!is_void_list(list)){
        while (aux->data != search_value){
            before = aux;
            aux = aux->next;
        }
        before->next = new_nodo;
        new_nodo->next = aux;
    }
}   

#endif