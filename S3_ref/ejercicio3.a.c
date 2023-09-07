#include <stdio.h>
#include <stdlib.h>

int function(int* array){
    int len = 8;

    for(int indice = 0; indice <= len; indice++){

        int suma_izq = 0;
        int suma_der = 0;

        if(indice == len){

            return -1;
        }else{
            for(int i = 0; i < indice; i++){
                suma_izq += array[i];
            }

            for (int j = indice + 1; j < len; j++){
                suma_der += array[j];
            }
            
            if(suma_izq == suma_der){

                return indice;
            }
        }
    }
}

int main(){

    int array[8] = {-3, 5, 1, -3, -1, 3, -1, -2};
    int resultado = function(array);

    printf("la posicion es: %d\n", resultado );

    return 0;
}