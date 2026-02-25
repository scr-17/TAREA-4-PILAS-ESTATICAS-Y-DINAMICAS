#include <stdio.h>

typedef struct nodo {
    char dato;
    struct nodo *siguiente;
} NODO;

int solicitar_entero();

int signo_valido(char);

int validacion_infija(char[]);

int prioridad(char);

void conversion_postfija(char[], char[]);

int main(){

    return 0;
}