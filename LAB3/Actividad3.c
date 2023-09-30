#include <stdio.h>
//Dom: nuemero a sumar 1
//Rec: void
//Descripcion: Suma 1 al numero pasado
void fucnion1 (int x){
    x = x + 1;
}

//Dom: nuemero a sumar 1
//Rec: void
//Descripcion: Suma 1 al numero pasado
void funcion2(int* x){
    *x = *x + 1;
}

int main(){

    int a = 5;

    funcion1(a); // aqui se suma pero no se cambia el dato debido a que la salida es void
    printf("%d", a);

    funcion1(&a); // aqui da warning debido a que estamos pasando una direccion de memoria
                //a una variable que no es puntero
    printf("%d", a);
    //funcion1(*a); aqui el llamado a la funcion falla debido a que pasamos una direccion de memoria
                //a un puntero y seria como preguntar por la direccion de memoria de la direccion de memoria

    funcion2(a);// aqui da warning debido a que estamos pasando el dato a un puntero
    printf("%d", a);

    funcion2(&a);// aqui se suma pero si se cambia el dato y el a pasa a de 5 a 6
    printf("%d", a);
    //funcion2(*a); aqui el llamado a la funcion falla debido a que pasamos una direccion de memoria
                //a un puntero y seria como preguntar por la direccion de memoria de la direccion de memoria

    return 0;
}