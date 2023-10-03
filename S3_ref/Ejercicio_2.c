#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int* swap(int* array, int a, int b){
    int aux = array[a];

    array[a] = array[b];
    array[b] = aux;

    return array;
}

int* ordenamientoBurbuja(int* arrayA, int len, int* Dataset){
    for(int i = len; i > 1; i--){
        for(int j = 0; j < i-1; j++){
            if(arrayA[j] > arrayA[j+1]){
                arrayA = swap(arrayA, j, j+1);
                Dataset = swap(Dataset, j , j+1);
            }
        }
    }

    return arrayA;
}

int raizCuadrada(int numero){
    return sqrt(numero);
}

int distancia(int U, int Q){
    int aux = pow((U - Q), 2);

    return(raizCuadrada(aux));
}

int* ranking(int* Dataset, int Q, int size){

    int* array = (int*)malloc(size * sizeof(int));

    for(int i = 0; i < size; i++){
        int aux = distancia(Dataset[i], Q);

        array[i] = aux;
    }

    ordenamientoBurbuja(array, size, Dataset);

    return Dataset;
}

int main(){
    
    int Dataset[5] = {2, 5, 8, 10, 12};
    int Q = 6;
    int size = 5;

    int* array = ranking(Dataset, Q, size);

    for(int i = 0; i < size; i++){

        printf("Ranking:\n");
        printf("%d.- %d\n", i+1, array[i]);
    }
    return 0;
}