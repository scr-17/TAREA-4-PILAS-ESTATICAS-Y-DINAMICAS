#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define TAM 60

/*Funcion para validar entrada de enteros para menus*/
int solicitar_entero();

/*Funcion para validar si algun operador es correcto*/
int operador_valido(char);

/*Funcion para validar una cadena y verificar si es infija*/
int validacion_infija(char[]);

/*Funcion para determinar el valor de priorirdad de un operador*/
int prioridad(char);

/*Funcion de conversion de infija a postfija*/
void conversion_postfija(char[], char[]);

int main()
{
    char inf[TAM] = {""};
    char pos[TAM] = {""};
    int op = 1;

    do {
        printf("\n\tCONVERSION DE NOTACION INFIJA A POSFIJA ESTATICA\n\n");
        printf("\nIngrese una expresion en notacion infija (Solo operandos alfabeticos): ");
        fflush(stdin);
        fgets(inf, sizeof(inf), stdin);
        fflush(stdin);
        inf[strcspn(inf, "\n\r")] = '\0';
        /*Validamos si la cadena obtenida es valida*/
        if(validacion_infija(inf)) {
            conversion_postfija(inf, pos);
            printf("\nNotacion infija: %s\nNotacion posfija: %s\n\n", inf, pos);
            printf("Desea realizar otra conversion?\n1 - Si\n0 - No\n> ");
            /*Obtenemos la opcion del menu*/
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
			if (isdigit(Aux[i])) /*Con una bandera valida que el caracter leido de una cadena sea un digito*/
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

int operador_valido(char operador)
{
    int es_valido, i;
    /*Los operadores validos son los vistos en clase, siendo estos los básicos de suma, resta
    multiplicacion, división, exponente, parentesis e igualdad*/
    char operadores_validos[] = {'+', '-', '/', '*', '^', '(', ')', '='};
    es_valido = 0;

    for (i = 0; i < 8; i++)
    {
        if (operador == operadores_validos[i])
            es_valido = 1;
    }

    return es_valido;
}

int validacion_infija(char expinf[])
{
    /*Mediante distintas banderas, validamos la expresion para ver si es correcta*/
    int bandera_operadores, bandera_operandos, bandera_parentesis, parentesis_vacio, num_parentesis, i;
    parentesis_vacio = 0;
    num_parentesis = 0;
    bandera_parentesis = 0;
    bandera_operadores = 0;
    bandera_operandos = 0;
    i = 0;

    /*En caso de que este vacia o sea un solo operando*/
    if(expinf[i] == '\0' || strlen(expinf) == 1)
    {
        printf("\nExpresion invalida, favor de ingresar una correcta\n");
        return 0;
    }

    while (expinf[i] != '\0')
    {
        /*Primera validación por si el primer elemento es un operando
        Segunda valifacion por si el último elemento es un operando
        Tercera validacion por si cualquier elemento no es operador valido ni operando o espacio*/
        if ((i == 0 && (expinf[i] != '(' && (!isalpha(expinf[i])))) 
        || (expinf[i + 1] == '\0' && (expinf[i] != ')' && (!isalpha(expinf[i])))) 
        || (!operador_valido(expinf[i]) && (!isalpha(expinf[i]) && expinf[i] != ' ')))
        {

            printf("\nExpresion invalida, favor de ingresar una correcta\n");
            return 0;
        }

        /*En caso de que el caracter sea un espacio, se continua el recorrido*/
        if(expinf[i] == ' '){
            i++;
            continue;
        }

        /*Si el caracter es un parentesis izquierdo*/
        if (expinf[i] == '(')
        {
            parentesis_vacio = 1;
            bandera_operadores++;
            /*Bandera parentesis checa que el parentesis derecho no vaya antes que el izquiero*/
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
        /*Si el caracter es un parentesis derecho*/
        else if (expinf[i] == ')')
        {
            /*Parentesis vacio checa que haya elementos dentro de un parentesis, caso contario, salta error*/
            if (parentesis_vacio) {
                printf("\nExpresion invalida, favor de ingresar una correcta\n");
                return 0;
            }
            bandera_parentesis = 1;
            num_parentesis--;
            /*Num parentesis checa que no haya pares de parentesis sin su par*/
            if (num_parentesis < 0)
            {
                printf("\nExpresion invalida, favor de ingresar una correcta\n");
                return 0;
            }
            i++;
            continue;
        }

        /*En caso de que el caracter sea un operador*/
        if (operador_valido(expinf[i]))
        {
            bandera_operadores++;
            bandera_parentesis = 0;
            bandera_operandos = 0;
            /*Bandera operadores verifica que no haya dos operadores juntos*/
            if (bandera_operadores == 2)
            {
                printf("\nExpresion invalida, favor de ingresar una correcta\n");
                return 0;
            }
        }
        else if(isalpha(expinf[i]))
        {
            bandera_operandos++;
            bandera_parentesis = 1;
            bandera_operadores = 0;
            /*Bandera operandos verifica que no haya dos operandos juntos*/
            if (bandera_operandos == 2)
            {
                printf("\nExpresion invalida, favor de ingresar una correcta\n");
                return 0;
            }
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

int prioridad(char operador)
{
    /*Les damos la prioridad a los signos de la expresion*/
    int valor_prioridad;
    switch (operador)
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
        /*Si el caracter no es un operador, agregamos el caracter a la expresion*/
        if (!ispunct(expinf[i]))
        {
            exppos[j++] = expinf[i];
        }
        /*Si el caracter es un parentesis izquierdo, lo agregamos a la pila sobre los demás*/
        else if (expinf[i] == '(')
        {
            pila[++top] = expinf[i];
        }
        /*Si el caracter es un parentesis derecho, retiramos todo el contenido de la pila
        hasta encontrar el parentesis izquierdo y lo añadimos a la expresion*/
        else if (expinf[i] == ')')
        {
            while (top != -1 && pila[top] != '(')
            {
                exppos[j++] = pila[top--];
            }

            top--;
        }
        /*Si el caracter es un operador, mediante un ciclo añadimos los caracteres hasta
        que encontremos uno con prioridad igual o mayor*/
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

    /*Añadimos los caracteres restantes a la expresion*/
    while (top != -1)
        exppos[j++] = pila[top--];

    /*Convertimos el ultimo caracter al caracter de fin de cadena*/
    exppos[j] = '\0';
}
