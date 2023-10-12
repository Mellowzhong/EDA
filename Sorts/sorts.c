#include <stdio.h>

int* swap(int* array, int a, int b){
    int aux = array[a];

    array[a] = array[b];
    array[b] = aux;

    return array;
}

int* ordenamiento_seleccion(int* array, int size){
    for(int i = 0; i < size - 1; i++){
        int indiceMejor = i;
        int valorMejor = array[i];

        for (int j = i + 1; j < size; j++){
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

int* ordenamiento_insercion(int* arreglo, int size){
    for (int i = 2; i < size; i++){
        int j = i;
        while ((j >= 2) && (arreglo[j] < arreglo[j-1])){
            arreglo = swap(arreglo, j, j-1);
            j = j-1;
        }
        
    }

    return arreglo;
}

int* ordenamientoBurbuja(int* arrayA, int len){
    for(int i = len; i > 1; i--){
        for(int j = 0; j < i-1; j++){
            if(arrayA[j] > arrayA[j+1]){
                arrayA = swap(arrayA, j, j+1);
            }
        }
    }

    return arrayA;
}

//Se crea esta funcion para revisar los valores de izquierda y derecha
int particiona(int* arreglo, int izquierda, int derecha) {

	//Se crea el pivote
	int pivote = arreglo[izquierda];

	//Se crea el ciclo para revisar los valorea de izquierda y derecha
	while (1) {

		while (arreglo[izquierda] < pivote) {
			
			izquierda++;
		}

		// Mientras el elemento de la derecha sea mayor que el pivote continÃºa avanzando
		while (arreglo[derecha] > pivote) {

			derecha--;
		}
		//Cuando se igualen los lados que retone el derecho
		if (izquierda >= derecha) {
			
			return derecha;
		}

		//Si no se cumple cambio los valores que se intercambien los valores
		else {

			swap(arreglo, izquierda, derecha);

			izquierda++;
			derecha--;
		}
	}
}

void quicksort(int* arreglo, int inicio, int final){
    if(inicio < final){
        int pivote = particiona(arreglo, inicio, final);
        quicksort(arreglo, inicio, pivote);
        quicksort(arreglo, pivote+1, final);
    }
}

int main(){

    return 0;
}