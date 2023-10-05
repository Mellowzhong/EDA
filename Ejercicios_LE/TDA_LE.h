#ifndef TDA_LE_h
#define TDA_LE_h    

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

List* crate_list(){
    List* new_list = (List*)malloc(sizeof(List));
    new_list->head = NULL;
    new_list->count = 0;

    return new_list;
}

Nodo crear_nodo(int data){
    Nodo new_nodo;

    new_nodo.data = data;
    new_nodo.next = NULL;
    
    return new_nodo;
}

Nodo agregar_nodo_ini(List* list, Nodo new_nodo){
    

}

#endif