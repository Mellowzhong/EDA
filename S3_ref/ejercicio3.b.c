#include <stdio.h>

void lienal_function(int* array){
    
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

int main(){
    int array[5] = {1,2,7,2,1};

    function(array);
    return 0;
}