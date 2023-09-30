#include <stdio.h>
//Dom: numero 1 a multiplicar - numero 2 multiplicar - resultado de la operacion
//Rec: void
//Descripcion: Multiplica dos numeros
void multiplicar(int* num1, int* num2, int* resultado){
    *resultado = *num1 * *num2;
}

int main(){
    int resultado;
    int num1 = 100;
    int num2 = 2;

    multiplicar(&num1, &num2, &resultado);

    printf("resultado: %d", resultado);
    return 0;
}