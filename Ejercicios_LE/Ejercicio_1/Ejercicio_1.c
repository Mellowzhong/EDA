#include "TDA_LES.h"


int main(){
    
    List* list = create_list();

    agregar_nodo_ini(list, 9);
    agregar_nodo_fin(list, 11);
    agregar_nodo_fin(list, 32);
    agregar_nodo_fin(list, 6);
    agregar_nodo_fin(list, 13);
    agregar_nodo_fin(list, 20);
    buscar_nodo(list, 6);

    return 0;
}
