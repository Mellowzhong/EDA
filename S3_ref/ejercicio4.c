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

void order(int* array, int array_lenght){
    int last_pos = array_lenght - 1;

    for(int i = 0; i < last_pos; i++){
        if(array[i] < 0){
            intercambiar(&array[i], &array[last_pos]);
            last_pos = last_pos - 1;
            imprimir(array, array_lenght);
        }
    }

    for (int i = last_pos; i < 0; i--){
        if(array[i] < 0){
            intercambiar(&array[i], &array[last_pos]);
            last_pos = last_pos - 1;
            imprimir(array, array_lenght);
        }
    }
    printf("last_post before: %d\n", last_pos);
    for(int i = 0; i < array_lenght; i++){
        if((i % 2 == 0) && (array[i] >= 0)){
            intercambiar(&array[i], &array[last_pos]);
            imprimir(array, array_lenght);
            printf("i = %d, lenght: %d, last_pos: %d\n", i, array_lenght, last_pos);
            last_pos = last_pos + 1;
        }
    }
}

int main() {

    int array[12] = {-15, 17, 42, 60, -32, 21, 13, -44, -72, 24, -25, 37};

    order(array, 11);

    imprimir(array, 12);

    return 0;
}