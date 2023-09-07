//codigo de los conejos, ejercicio 3.
#include <stdio.h>

int recursion1(int pareja_maduros, int pareja_inmaduros, int meses){
    if (meses == 0||meses == 1){

        return pareja_maduros + pareja_inmaduros;
    }
    else {

        return recursion1(pareja_inmaduros + pareja_maduros, pareja_maduros, meses -1);
    }
}

int main(){
    
    int meses;  

    printf("Escribe los meses que quiere\n");
    scanf("%d", &meses);
    
    int conejos = recursion1( 1, 0, meses);

    printf("Catidad de parejas totales son: %d\n", conejos);
    return 0;
}