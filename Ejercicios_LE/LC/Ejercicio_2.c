#include "TDA_LC.h"

int main(){

    List* list = create_list();

    agregar_nodo_ini(list, 2);
    agregar_nodo_final(list, 4);
    agregar_nodo_final(list, 7);
    //agregar_nodo_final(list, 8);
    //agregar_nodo(list, 3, 2);
    show_list(*list);

    return 0;
}