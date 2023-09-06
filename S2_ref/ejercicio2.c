#include <stdio.h>
#include <time.h>

int interativo(int number){
    
    int acum = 0;

    for(int i = 1; i <= number; i++){
        acum += i;
    }

    return acum;
}

int recursivo(int number, int acum){

    if(number == 0){
        return acum;

    }else{
        recursivo(number - 1, acum + number);   
    }
}

int main(){

    double iterative_time = 0.0;
    clock_t begin = clock(); 
    int resultado_iterativo = interativo(5);
    clock_t end = clock();
    iterative_time += (double)(end - begin) / CLOCKS_PER_SEC;

    printf("The elapsed iterative time is %f seconds and the result is %d", iterative_time, resultado_iterativo);

    double recursive_time = 0.0;
    clock_t begin_2 = clock(); 
    int resultado_recursivo = recursivo(5, 0);
    clock_t end_2 = clock();
    recursive_time += (double)(end_2 - begin_2) / CLOCKS_PER_SEC;

    printf("The elapsed recursive time is %f seconds and the result is %d", recursive_time, resultado_recursivo);
    return 0;
}