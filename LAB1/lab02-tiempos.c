#include <stdio.h>
#include <time.h>
#include <stdlib.h>

long potenciaIterativa(int base, int exponente){
	int acum = 1;

	if(exponente == 1){
        
        return base;

    }if(exponente == 0){
		
		return 1;
	}if(base == 0 && exponente == 0){

		return -1;
	}else{

		for(int i = 0; i < exponente; i++){
			acum *= base;
    	}
		
    	return acum;
	}
}

long potenciaRecursiva(int base, int exponente){

	if(exponente == 1){
		
		return base;
	}if(exponente == 0){
        
        return 1;
    }if(base == 0 && exponente == 0){

		return -1;
	}else{
        long resultado = base * potenciaRecursiva(base, exponente - 1);

        return resultado;
    }
}

int main (int argc, char * argv[]){

	int base=atoi(argv[1]);
	int exponente=atoi(argv[2]);
	long potIt=0, potRe=0;
	clock_t ciniIt, cfinIt, ciniRe, cfinRe;
	double tiempoIt, tiempoRe;
	
	ciniIt=clock();
	long resultado_iterativa = potenciaIterativa(base, exponente);
	cfinIt=clock();
		printf("fin de linea\n");
	ciniRe=clock();
	long resultado_recursiva = potenciaRecursiva(base, exponente);
	cfinRe=clock();
			printf("no se muere");
	tiempoIt= (double)(cfinIt-ciniIt)/CLOCKS_PER_SEC;
	tiempoRe= (double)(cfinRe-ciniRe)/CLOCKS_PER_SEC;

	printf("%d ^ %d %ld %f %ld %f", base, exponente, resultado_iterativa, tiempoIt, resultado_recursiva, tiempoRe);
	
	return 1;	
} 

