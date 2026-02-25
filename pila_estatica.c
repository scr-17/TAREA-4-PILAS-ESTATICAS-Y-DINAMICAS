#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define TAM 30

int solicitar_entero();

int signo_valido(char);

int validacion_infija(char[]);

int prioridad(char);

void conversion_postfija(char[], char[]);

int main()
{
    char inf[TAM] = {""};
    char pos[TAM] = {""};
    int op = 1;

    do {
        printf("\n\tCONVERSION DE NOTACION INFIJA A POSFIJA\n\n");
        printf("\nIngrese una expresion en notacion infija: ");
        gets(inf);
        if(validacion_infija(inf)) {
            conversion_postfija(inf, pos);
            printf("\nNotacion infija: %s\nNotacion posfija: %s\n\n", inf, pos);
            printf("Desea realizar otra conversion?\n1 - Si\n0 - No\n> ");
            op = solicitar_entero();
            while (op != 1 && op != 0) {
                printf("Valor fuera de rango, favor de ingresar una opcion correcta: ");
                op = solicitar_entero();
            }
        }
        system("pause");
        system("cls");
    }while (op != 0);

    return 0;
}

int solicitar_entero()
{
	char Aux[' '];
	int i, p, y, num;
	do
	{
		fflush(stdin);
		scanf(" %s", Aux); // se lee los datos introducidos
		fflush(stdin);
		y = strlen(Aux);

		for (i = 0; i < y; i++)
		{
			if (isdigit(Aux[i])) /*Con una bandera_signos valida que el caracter leido de una cadena sea un digito*/
				p = 1;
			else
				p = 0;

			if (p == 0)
			{
				printf("\nError, dato mal introducido\nIntroducza una opcion correcta: ");
				break;
			}
		}
		if (y == 0)
			p = 0;
	} while (p == 0);

	num = atoi(Aux); /*Regresa la conversion de la cadena introducida a un digito */
	return num;
}

int signo_valido(char signo)
{
    int es_valido, i;
    char signos_validos[] = {'+', '-', '/', '*', '^', '(', ')', '='};
    es_valido = 0;

    for (i = 0; i < 8; i++)
    {
        if (signo == signos_validos[i])
            es_valido = 1;
    }

    return es_valido;
}

int validacion_infija(char expinf[])
{
    int bandera_signos, bandera_parentesis, parentesis_vacio, num_parentesis, i;
    parentesis_vacio = 0;
    num_parentesis = 0;
    bandera_parentesis = 0;
    bandera_signos = 0;
    i = 0;

    if(expinf[i] == '\0')
    {
        printf("\nExpresion invalida, favor de ingresar una correcta\n");
        return 0;
    }

    while (expinf[i] != '\0')
    {
        if ((i == 0 && (expinf[i] != '(' && (!isalpha(expinf[i])) && expinf[i] != ' ')) 
        || (expinf[i + 1] == '\0' && (expinf[i] != ')' && (!isalpha(expinf[i]) && expinf[i] != ' '))) 
        || (!signo_valido(expinf[i]) && (!isalpha(expinf[i]) && expinf[i] != ' ')))
        {

            printf("\nExpresion invalida, favor de ingresar una correcta\n");
            return 0;
        }

        if (expinf[i] == '(')
        {
            parentesis_vacio = 1;
            bandera_signos++;
            if (bandera_parentesis == 1) 
            {
                printf("\nExpresion invalida, favor de ingresar una correcta\n");
                return 0;
            }
            bandera_parentesis = 0;
            num_parentesis++;
            i++;
            continue;
        }
        else if (expinf[i] == ')')
        {
            if (parentesis_vacio) {
                printf("\nExpresion invalida, favor de ingresar una correcta\n");
                return 0;
            }
            bandera_parentesis = 1;
            num_parentesis--;
            if (num_parentesis < 0)
            {
                printf("\nExpresion invalida, favor de ingresar una correcta\n");
                return 0;
            }
            i++;
            continue;
        }

        if (signo_valido(expinf[i]))
        {
            bandera_parentesis = 0;
            bandera_signos++;
            if (bandera_signos == 2)
            {
                printf("\nExpresion invalida, favor de ingresar una correcta\n");
                return 0;
            }
        }
        else
        {
            bandera_parentesis = 1;
            bandera_signos = 0;
        }

        parentesis_vacio = 0;

        i++;
    }

    if (num_parentesis != 0)
    {
        printf("\nExpresion invalida, favor de ingresar una correcta\n");
        return 0;
    }

    return 1;
}

int prioridad(char signo)
{
    int valor_prioridad;
    switch (signo)
    {
    case '^':
        valor_prioridad = 3;
        break;
    case '*':
        valor_prioridad = 2;
        break;
    case '/':
        valor_prioridad = 2;
        break;
    case '+':
        valor_prioridad = 1;
        break;
    case '-':
        valor_prioridad = 1;
        break;
    case '=':
        valor_prioridad = 0;
        break;
    default:
        valor_prioridad = -1;
    }
    return valor_prioridad;
}

void conversion_postfija(char expinf[], char exppos[])
{
    int top = -1, i = 0, j = 0;
    char pila[TAM];

    while (expinf[i] != '\0')
    {

        if (!ispunct(expinf[i]))
        {
            exppos[j++] = expinf[i];
        }
        else if (expinf[i] == '(')
        {
            pila[++top] = expinf[i];
        }
        else if (expinf[i] == ')')
        {
            while (top != -1 && pila[top] != '(')
            {
                exppos[j++] = pila[top--];
            }

            top--;
        }
        else
        {
            while (top != -1 && pila[top] != '(' &&
                   (prioridad(pila[top]) > prioridad(expinf[i]) ||
                    (prioridad(pila[top]) == prioridad(expinf[i]) && (expinf[i] != '^'))))
            {
                exppos[j++] = pila[top--];
            }
            pila[++top] = expinf[i];
        }

        i++;
    }
    while (top != -1)
        exppos[j++] = pila[top--];

    exppos[j] = '\0';
}