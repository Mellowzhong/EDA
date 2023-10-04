#include <stdio.h>

// calcular moda
int moda(int* conjunto, int size){
    int moda = conjunto[0]; 
    int frecuenciaMax = 1;

    int elementoActual = conjunto[0]; 
    int frecuenciaActual = 1;

    for (int i = 1; i < size; ++i) {
        if (conjunto[i] == elementoActual) {

            ++frecuenciaActual;
        } else {
           
            if (frecuenciaActual > frecuenciaMax) {
                moda = elementoActual;
                frecuenciaMax = frecuenciaActual;
            }

            elementoActual = conjunto[i];
            frecuenciaActual = 1;
        }
    }

    if (frecuenciaActual > frecuenciaMax) {
        moda = elementoActual;
    }

    return moda;
}

int main(){

    int conjunto[6] = {4, 6, 2, 4, 3, 1};
    int size = 6;

    int result = moda(conjunto, 6);

    printf("%d\n", result);

    return 0;
}
