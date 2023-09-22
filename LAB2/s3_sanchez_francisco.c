#include <stdio.h>
#include <stdlib.h>

//Entrada: arreglo de enteros - largo del arreglo
//Salida: arreglo de enteros
//Descripcion: Copio los datos del array dado a uno auxiliar
int* copyArray(int* array, int len){
    int* aux = (int*)malloc(len* sizeof(int));

    for(int i = 0; i < len; i++){
        aux[i] = array[i];
    }

    return aux;
}

//Entrada: arreglo de enteros - largo del arreglo
//Salida: void
//Descripcion: Imprime en pantalla el array dado
void imprimir(int* arreglo, int n){
    int i;
    for(i = 0; i < n; i++){
        printf("%d ", arreglo[i]);
    }
    printf("\n");
}

//Entrada: nombre del archivo - largo del arreglo devuelto
//Salida: arreglo de enteros
//Descripcion: Con el nombre dado, se abre un archivo y se hace una lista con los numeros de este
            //ademas del mismo archivo se saca el largo del arreglo y se almacena en la variable largo
int* leerArchivo(char* fileName, int* largo){
    FILE* fichero;
    fichero = fopen(fileName, "r");
    if(fichero == NULL){
        printf("No se pudo abrir el archivo");
        exit(1);
    }

    int len;
    fscanf(fichero, "%d", &len);
    int* arrayA = (int*)malloc(len * sizeof(int));

    for(int i = 0; i < len; i++){
        fscanf(fichero, "%d", &arrayA[i]);
    }

    fclose(fichero);
    *largo = len;

    return arrayA;
}

//Entrada: arreglo de eteros - indice a - indice b
//Salida: array
//Descripcion: Intercambia posicion a y b en el arreglo dado
int* swap(int* array, int a, int b){
    int aux = array[a];

    array[a] = array[b];
    array[b] = aux;

    return array;
}

//Entrada: arreglo de enteros - largo del arreglo
//Salida: arreglo de enteros
//Descripcion: ordena un arreglo dado
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

//Entrada: arreglo de entero - inicio del arreglo - final del arreglo - dato buscado
//Salida: 1 si el dato se encuentra; 0 si el dato no se encuentra
//Descripcion: Se aplica la busqueda binaria para saber si el dato se encuentra en el arreglo
int busquedaBinaria(int* arrayA, int inicio, int final, int datoBuscado){
    int centro = (inicio + final)/2;

    if(inicio == final){
        return 0;
    }
    if(arrayA[centro] == datoBuscado){
        return 1;
    }else{
        if(arrayA[centro] > datoBuscado){
            return busquedaBinaria(arrayA, inicio, centro -1, datoBuscado);
        }else{
            return busquedaBinaria(arrayA, centro+1, final, datoBuscado);
        }
    }
}

int main(){
    int len_a, len_b, len_c;

    int* arrayA = leerArchivo("S3_10.in", &len_a);
    int* arrayB = leerArchivo("S3_20.in", &len_b);
    int* arrayC = leerArchivo("S3_40.in", &len_c);

    imprimir(arrayA, len_a);
    int* auxA = copyArray(arrayA, len_a);
    int* arrayResultA = ordenamientoBurbuja(auxA, len_a);
    int resultA = busquedaBinaria(arrayResultA, 0, len_a, 6);
    printf("resultadoA: %d\n", resultA);
    imprimir(arrayResultA, len_a);

    imprimir(arrayB, len_b);
    int* auxB = copyArray(arrayB, len_b);
    int* arrayResultB = ordenamientoBurbuja(auxB, len_b);
    imprimir(arrayResultB, len_b);

    imprimir(arrayC, len_c);
    int* auxC = copyArray(arrayC, len_c);
    int* arrayResultC = ordenamientoBurbuja(auxC, len_c);
    imprimir(arrayResultC, len_c);

    return 0;
}