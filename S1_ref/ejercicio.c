#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** crar_matriz(int number){
    int** new = (int **)malloc(number * sizeof(int *));

    for (int i = 0; i < number; i++) {
        new[i] = (int *)malloc(number * sizeof(int)); 
    }

    return new;
}

void show_matriz(int** matriz, int n){

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("[%d]", matriz[i][j]);
        }
        printf("\n");
    }
}

void suma_matriz(int** A, int** B){

    int n = 5;

    int** new = crar_matriz(n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            new[i][j] = A[i][j] + B[i][j];
        }
    }

    show_matriz(new, n);

    for (int i = 0; i < n; i++) {
        free(new[i]);
    }
    free(new);
}

void multi_matriz(int** A, int** B){
    int n = 5;

    int** new = crar_matriz(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            new[i][j] = 0;
            for(int k = 0; k < n; k++){
                new[i][j] = new[i][j] + (A[i][k] * B[k][j]);
            }
        }
    }

    show_matriz(new, n);

    for (int i = 0; i < n; i++) {
        free(new[i]);
    }
    free(new);
}

int main() {
    int n = 5;
    srand(time(NULL));
    
    int** matrizA = crar_matriz(n);
    int** matrizB = crar_matriz(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrizA[i][j] = rand() % 10+1;
            matrizB[i][j] = rand() % 10+1;
        }
    }

    double suma_time = 0.0;
    clock_t begin = clock(); 
    suma_matriz(matrizA, matrizB);
    clock_t end = clock();
    suma_time += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("el tiempo de la suma es: %f\n", suma_time);

    printf("---------------------------\n");

    double multi_time = 0.0;
    clock_t begin_2 = clock(); 
    multi_matriz(matrizA, matrizB);
    clock_t end_2 = clock();
    multi_time += (double)(end_2 - begin_2) / CLOCKS_PER_SEC;
    printf("el tiempo de la multiplicacion es: %f\n", multi_time);

    for (int i = 0; i < n; i++) {
        free(matrizA[i]);
        free(matrizB[i]);
    }
    free(matrizA);
    free(matrizB);

    return 0;
}