#include <stdio.h>

int iterativo(int base, int expo){
    int acum = 1;

    for(int i = 0; i < expo; i++){
        acum *= base;
    }

    return acum;
}
//tiempo y complejidad:
//tiempo: 6c
//complejidad: o(n);

int recursivo(int base, int expo){
    if(expo == 1 && expo > 0){
        
        return base;

    }else{
        int resultado = base * recursivo(base, expo - 1);

        return resultado;
    }
}

//tiempo y complejidad:
//tiempo: 3c, si expo =1
        //6c + t(expo-1) , si expo > 1
        // a = 1, b = 1, k = 0
        // => t(expo-1) + O(n).


int main(){

    int resultado_iterativo = iterativo(2,3);
    int resultado_recursivo = recursivo(2,3);

    printf("resultado iterativo: %d\n", resultado_iterativo);
    printf("resultado recursivo: %d\n", resultado_recursivo);

    return 0;
}