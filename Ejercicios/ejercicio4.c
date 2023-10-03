//ejercicio del arreglo con positivos y negativos intercalados
#include <stdio.h>

void imprimir(int *arreglo, int n){
    int i;
    for(i = 0; i < n; i++){
        printf("%d ", arreglo[i]);
    }
    printf("\n");
}

void intercambiar(int *a, int *b){
    int aux = *a;
    *a = *b;
    *b = aux;
}
//tiempo: 3c

void order(int* array, int array_lenght){
    int last_pos = array_lenght - 1;

    for(int i = 0; i < last_pos; i++){
        if(array[i] < 0){
            intercambiar(&array[i], &array[last_pos]); // no se si contarlo como 3c o como c
            last_pos = last_pos - 1;
        }
    }

    for (int i = last_pos; i < 0; i--){
        if(array[i] < 0){
            intercambiar(&array[i], &array[last_pos]);
            last_pos = last_pos - 1;
        }
    }
    
    for(int i = 0; i < array_lenght; i++){
        if((i % 2 == 0) && (array[i] >= 0)){
            intercambiar(&array[i], &array[last_pos]);
            last_pos = last_pos + 1;
        }
    }
}
//tiempo y complejidad: 
// tiempo : 2c + n(9c) + n(9c) + n(11c)
        //2c + 27cn
//complejidad : O(n),

int main() {

    int array[12] = {-15, 17, 42, 60, -32, 21, 13, -44, -72, 24, -25, 37};

    order(array, 11);

    imprimir(array, 12);

    return 0;
}