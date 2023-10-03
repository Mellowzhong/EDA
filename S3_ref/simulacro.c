#include <stdio.h>

// Función para imprimir el arreglo
void imprimir_arreglo(int A[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}


// Función para voltear el arreglo A desde la posición 1 hasta i
void voltear(int A[], int i) {
    int inicio = 0;
    int fin = i - 1;
    while (inicio < fin) {
        // Intercambiar elementos en las posiciones inicio y fin
        int temp = A[inicio];
        A[inicio] = A[fin];
        A[fin] = temp;

        // Moverse hacia el centro del arreglo
        inicio++;
        fin--;
    }
}

// Función para ordenar decrecientemente el arreglo A
void ordenar_decreciente(int A[], int n) {
    for (int i = n; i > 0; i--) {
        // Encontrar la posición del máximo elemento en A[0:i]
        int max_index = 0;
        for (int j = 1; j < i; j++) {

            if (A[j] > A[max_index]) {
                max_index = j;
            }
        }

        // Voltear el segmento desde la posición 1 hasta la posición del máximo
        printf("i: %d, max: %d\n", i, max_index);
        voltear(A, max_index + 1);
        imprimir_arreglo(A, n);

        // Voltear el segmento completo desde la posición 1 hasta i
        printf("i: %d, max: %d\n", i, max_index);
        voltear(A, i);
        imprimir_arreglo(A, n);
    }

    voltear(A, n);
}

int main() {
    int A[] = {4, 2, 8, 5, 1, 3, 7, 6};
    int n = sizeof(A) / sizeof(A[0]);

    printf("Arreglo original: ");
    imprimir_arreglo(A, n);

    ordenar_decreciente(A, n);

    printf("Arreglo ordenado decrecientemente: ");
    imprimir_arreglo(A, n);

    return 0;
}
