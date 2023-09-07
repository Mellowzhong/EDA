#include <stdio.h>

int iterativo(int base, int expo){
    int acum = 1;

    for(int i = 0; i < expo; i++){
        acum *= base;
    }

    return acum;
}

int recursivo(int base, int expo){
    if(expo == 1){
        return base;
    }else if (expo == 0){
        return 1;
    }else{
        int resultado = base * recursivo(base, expo - 1);

        return resultado;
    }
}

int main(){

    int resultado_iterativo = iterativo(2,3);
    int resultado_recursivo = recursivo(2,3);

    printf("resultado iterativo: %d\n", resultado_iterativo);
    printf("resultado recursivo: %d\n", resultado_recursivo);

    return 0;
}