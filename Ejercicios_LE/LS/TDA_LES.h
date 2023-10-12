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

int is_void_list(List* list){
    if(list->head == NULL){
        return 1;
    }
    return 0;
}

List* crate_list(){
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
    printf("\nData->");
    if(aux != NULL){
        while (aux != NULL){
            printf("%d\n", aux->data);
            aux = aux->next;
        }
    }
}

void agregar_nodo_ini(List* list, int value){
    Nodo* new_nodo = crear_nodo(value);

	if (!(is_void_list(list))){ 
        new_nodo->next= list->head;
	}

	list->head = new_nodo;
	list->count = list->count + 1; 
}

void agregar_nodo_fin(List* list, int value){
    Nodo* aux = list->head;

    while(aux->next != NULL){
        aux = aux->next;
    }

    Nodo* new_nodo = crear_nodo(value);
    aux->next = new_nodo;
    list->count = list->count + 1;
}

void agregar_nodo(List* list, int value, int search_value){
    Nodo* aux = list->head;

    while (aux->data != search_value){
        aux = aux->next;
    }
    Nodo* new_nodo = crear_nodo(value);
    new_nodo->next = aux->next;
    aux->next = new_nodo;
}

void eliminar_nodo_ini(List* list){
    Nodo* aux = list->head;

    if(!is_void_list(list)){
        list->head = list->head->next;
        list->count = list->count - 1;
        aux->next = NULL;
        free(aux);
    }
}

void eliminar_nodo(List* list, int search_value){
    Nodo* aux = list->head;
    Nodo* before = NULL;

    while (aux->data != search_value){
        before = aux;
        aux = aux->next;
    }
    before->next = aux->next;
    free(aux);
}

void buscar_nodo(List* list, int search_value){
    int count = 1;

    if(!is_void_list(list)){
        Nodo* aux = list->head;
        while (aux->data != search_value){
            aux = aux->next;
            count ++;
        }
        printf("se encontro el nodo: %d en la posicion %d", search_value, count);
    }else{
        printf("no se encontro el nodo");
    }
}

#endif