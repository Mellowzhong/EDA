#include <stdio.h>

int busquedaSecuencial(int* arreglo, int datoBuscado, int size_array){

    for (int i = 0; i < size_array; i++){
        if(arreglo[i] == datoBuscado){
            return i;
        }   
    }
    return 0;
}

int busquedaBinaria(int* arreglo, int inicio, int final, int datoBuscado){
    int centro = (inicio + final)/2;

    if(inicio == final){
        return -1;
    }
    if(arreglo[centro] == datoBuscado){
        return centro;
    }else{
        if(arreglo[centro] > datoBuscado){
            return busquedaBinaria(arreglo, inicio, centro - 1, datoBuscado);
        }else{
            return busquedaBinaria(arreglo, centro+1 ,final,datoBuscado);
        }
    }
}

int main(){

    return 0;
}