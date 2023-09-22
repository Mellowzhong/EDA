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

void swap(int* array, int a, int b){
    int aux = array[a];

    array[a] = array[b];
    array[b] = aux;
}

int* ordenamiento_seleccion(int* array){
    int n = 8;

    for(int i = 0; i < n - 1; i++){

        int indiceMejor = i;
        int valorMejor = array[i];

        for (int j = i + 1; j < n; j++){
            if(array[j] < valorMejor){
                indiceMejor = j;
                valorMejor = array[j];
            }
        }

        if(indiceMejor > i){
            swap(array, i, indiceMejor);
        }
    }
    return array;
}

int main(){
    int arrayA[8] = {49, 70, 23, 73, 5, 8, 38, 13};
    int arrayB[8] = {11, 13, 24, 35, 47, 58, 59, 80};
    int arrayC[8] = {10, 9, 8, 7, 6, 5, 4, 2};
    
    int* resultA_seleccion = ordenamiento_seleccion(arrayA);
    int* resultB_seleccion = ordenamiento_seleccion(arrayB);
    int* resultC_seleccion = ordenamiento_seleccion(arrayC);

    imprimir(resultA_seleccion, 8);
    imprimir(arrayA, 8);
    imprimir(resultB_seleccion, 8);
    imprimir(resultC_seleccion, 8);

    return 0;
}