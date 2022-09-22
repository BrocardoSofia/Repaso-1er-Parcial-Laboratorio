#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

//////////////////////////////////////PROTOTIPADOS////////////////////////////////////////////
//carga de pila
void cargarPila(Pila *pilita);

//retorna el menor elemento de la pila y lo elimina
int menorElementoPila(Pila *pilita);

//retorna la cantidad de elementos de la pila
int contarElementosPila(Pila pilita);

//retorna los validos del arreglo
int pilaAarregloOrdenado(Pila pilita, int arreglo[50]);

//muestra el arreglo
void mostrarArreglo(int arreglo[50], int validos);

/////////////////////////////////////////MAIN////////////////////////////////////////////////
int main()
{
    //declaro las variables necesarias para el arreglo
    int numeros[50]={0};//declaro y lo inicializo todo en 0
    int validosNumeros;

    //declaro una pila y la inicializo
    Pila DADA;
    inicpila(&DADA);

    cargarPila(&DADA);//cargo la pila

    //muestro la pila
    printf("PILA DADA\n");
    printf("---------\n");
    mostrar(&DADA);

    //asigno los validos a con el retorno de la llamada a la funcion
    validosNumeros=pilaAarregloOrdenado(DADA, numeros);

    //muestro el arreglo
    mostrarArreglo(numeros, validosNumeros);

    return 0;
}


/**1.
Hacer una función void que cargue muchos elementos en una pila. Tantos como quiera el usuario,
pero menos de 50.
**/
void cargarPila(Pila *pilita)
{
    char mander='s';//variable para parar el ciclo de carga

    while(mander=='s')
    {
        //interaccio con el usuario
        printf("CARGARNDO PILA\n");
        printf("--------------\n");
        leer(pilita);//el usuario carga por teclado el valor

        //pregunto para parar el ciclo de carga
        printf("\nSeguir cargando elementos? (s/n)\n");
        fflush(stdin);//limpio el buffer
        scanf("%c", &mander);

        //limpio pantalla
        system("cls");
    }
}


/**2.
Hacer una función de tipo entero, que encuentre el menor elemento en una pila y lo retorne.
(debe eliminarlo de la pila, el resto de la Pila debe quedar igual)
**/
int menorElementoPila(Pila *pilita)
{
    //declaro variable para guardar el menor
    int menor;
    int menorAnterior;

    //variable de tipo pila para recorrer la pila
    Pila aux;
    inicpila(&aux);//inicializo la pila auxiliar

    //paso el primer elemento de la pila y lo asigno a menor para poder comparar
    menor=desapilar(pilita);//tambien ya lo elimino del tope

    while(!pilavacia(pilita))
    {
        //comparo menor con el tope de pilita
        if(tope(pilita)<menor)
        {
            menorAnterior=menor;//guardo el menor acutal el una variable
            menor=desapilar(pilita);//guardo el nuevo menor en la variable y lo elimino de aux
            apilar(&aux, menorAnterior);//vuelvo a apilar el menor anterior en la pila aux
        }
        else
        {
            //si el tope es mayor lo desapilo y paso al siguiente tope
            apilar(&aux, desapilar(pilita));
        }
    }

    //vuelvo a guardar los elementos en la pila pilita
    while(!pilavacia(&aux))
    {
        apilar(pilita, desapilar(&aux));
    }

    return menor;
}

/**3.
Hacer una función de tipo entero, que cuente la cantidad de elementos de una pila
y lo retorne.
**/
int contarElementosPila(Pila pilita)
{
    //declaro el contador y lo inicializo en 0
    int contador=0;
    //declaro e inicializo una pila auxiliar
    Pila AUX;
    inicpila(&AUX);

    //recorro la pila
    while(!pilavacia(&pilita))
    {
        apilar(&AUX, desapilar(&pilita));
        contador++;
    }

    return contador;//retorno la cantidad de elementos que tiene la pila
}

/**4.
Hacer una función de tipo entero que reciba como parámetro una pila y un arreglo
(de 50 enteros). Esta función debe:
1.	invocar a la función 3 para saber la cantidad de elementos que tiene la pila,
2.	ir sacando de la pila el menor elemento (invocar muchas veces la función 2) e
3.	ir colocándolos en el arreglo de uno en fondo.
De esta forma se obtiene un arreglo ordenado.
**/
int pilaAarregloOrdenado(Pila pilita, int arreglo[50])
{
    //variables
    int contador=0;//cuento los lugares para almacenar en el arreglo
    int validos;//para los validos de la pila

    //variable auxiliare de tipo pila- declaracion e inicializacion
    Pila AUX;
    inicpila(&AUX);

    //cuento los elementos de la pila
    validos=contarElementosPila(pilita);

    //llamo a la funcion que busca el menor elemento de la pila hasta que la pila este vacia
    while(contador<validos)
    {
        //llamo a la funcion que busca el menor
        arreglo[contador]=menorElementoPila(&pilita);
        contador++;
    }
    return contador;//retorno los elementos validos del arreglo
}

/**5.
Hacer una función que recorra el arreglo y lo muestre por pantalla.
**/
void mostrarArreglo(int arreglo[50], int validos)
{
    printf("MOSTRANDO ARREGLO\n");
    printf("-----------------\n");
    for(int i=0; i<validos; i++)
    {
        printf("pos[%d] -> %d\n", i+1, arreglo[i]);
    }
}
