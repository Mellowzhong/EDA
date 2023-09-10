#include <stdio.h>
#include <stdbool.h>

void lineal_function(int* array){
    
    int len = 5;
    int min = len/2;
    int maximo = 0;
    bool ciclo = true;

    while(ciclo){
        int indice = 0;
        int i = 0;
        int aux = array[indice];
        int suma = 0;
        
        if(indice == len){
            
            i += 1;
        }else{
            if(aux == array[i]){
                suma += 1;
            }

            indice += 1;
        }
    }
}


void function(int* array){
    int len = 5;
    int min = len/2;
    int maximo = 0;

    for(int indice = 0; indice <=len ; indice++){
        int aux = array[indice];
        int suma = 0;
        for(int i = 0; i < len; i++){
            if(aux == array[i]){
                suma += 1;
            }
        }
        if(suma > maximo){
            maximo = suma;
        }
    }
    if(min < maximo){
        printf("si existe");
    }else{
        printf("no existe");
    }
}
//tiempo y complejidad: 
//tiempo: 4c + n(7c + n(6c)) + 2c => 6c + 7cn + 6cn**2
//compeljidad : O(n**2)

int main(){
    int array[5] = {1,2,7,2,1};

    function(array);
    return 0;
}