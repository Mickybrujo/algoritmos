#include <stdlib.h>
#include <stdio.h>
#include "tiempo.h"

//Definicion de la estructura del arbol binario
struct tree
{
    struct tree *der, *izq; //definicion de las hojas hijo del AB
    int dato;               // numero que guardara la hoja del AB
};

int posicion = 0; //Contador para posicion del arreglo en la que se insertaran los datos en la funcion guardarRecorridoinorden

//Funcion que inserta valores en un arbo binario
void insertTree(struct tree **raiz, int num)
{
    if ((*raiz) == NULL) //Verifica la hoja en la que se encuentra sea una hoja hijo en la que se puede insertar
    {
        *raiz = malloc(sizeof(struct tree)); //Reserva espacio de memoria para alojar el nodo de un abol
        (*raiz)->dato = num;                 //Pasa el dato que queremos insertar a la hoja creada
        (*raiz)->der = NULL;                 //Apunta los nodos hijo de la hoja creada a NULL
        (*raiz)->izq = NULL;
    }
    else //Si la hoja en la que se encuentra no es una hoja hijo, vuelve a llamar a la funcion para recorrer el abol
    {
        if (num < (*raiz)->dato) //Si el el dato que deseamos insertar es menor que el valor de la hoja actual, checa el hijo izquierdo
        {
            insertTree(&(*raiz)->izq, num);
        }
        else //Si el el dato que deseamos insertar es menor que el valor de la hoja actual, checa el hijo izquierdo
        {
            insertTree(&(*raiz)->der, num);
        }
    }
}

struct tree *llenarArborl(int A[], int cant_datos)
{
    struct tree *arbol = NULL;
    for (int i = 0; i < (cant_datos); i++)
    { //Llenamos el arbol con los datos del arreglo
        insertTree(&arbol, A[i]);
    }
    return arbol; //regresamos el apuntador a la raiz del arbol
}

//Funcion que busca un numero entero entre los nodos de un arbol binario

int busquedaArbol(struct tree *raiz, int numero)
{
    while (raiz != NULL)
    {                             // Si el nodo en el que se encuentra es distinto de NULL continua buscando
        if (raiz->dato == numero) //Si el numero del nodo en el que se encuentra es igual al numero que buscamos regresa el dato del nodo
        {
            return raiz->dato;
        }
        else if (raiz->dato > numero) // Si el numero que buscamos es menor que el dato del nodo, nos movemos a la izquierda en el arbol
        {
            raiz = raiz->izq;
        }
        else if (raiz->dato < numero) // Si el numero que buscamos es mayor que el dato del nodo, nos movemos a la derecha en el arbol
        {
            raiz = raiz->der;
        }
    }
    return -1; // Si se llega a un nodo nulo quiere decir que el dato no se encuntra en el arbol y regresamos -1
}
//Funcion que lee una cantidad de datos de un archivo y regresa un apuntador a un arreglos con los datos
int *readTxt(int cant_datos, FILE *datos)
{
    int *array_datos, i;
    array_datos = (int *)malloc(sizeof(int) * cant_datos); //Reservamos memoria suficiente para la cantidad de datos
    for (i = 0; i < cant_datos; i++)                       //Recorremos los datos y los guardamos en el arreglo
    {
        fscanf(datos, "%d", &array_datos[i]);
    }
    return array_datos; //Regresamos el arreglo con los datos
}

//Programa Principal
int main(int argc, char *argv[])
{
    FILE *archivo_entrada;                                 //Apuntador de archivos para lectura de los datos
    double utime0, stime0, wtime0, utime1, stime1, wtime1; //Variables para medicion de tiempos
    int *Arreglo;                                          //Apuntador a un arreglo de enteros que contienelos datos
    struct tree *abb = NULL;                               //Declaramos la raiz del arbol
    int n_datos, numero_buscado;                           //Cantidad de datos que el usuario desea considerar para buscar
    archivo_entrada = fopen("numeros10millones.txt", "r"); //Abrimos el archivo con 10 millones de datos en modo lectura

    //Iniciar el conteo del tiempo para las evaluaciones de rendimiento
    uswtime(&utime0, &stime0, &wtime0);

    //Validamos si hubo errores al abrir el archivo
    if (archivo_entrada == NULL)
    {
        printf("No se pudo abrir el archivo :C. \n");
        return 1;
    }

    //Valida si se introducen menos de dos argumentos (Cadena de ejecucion y cadena=n)
    if (argc < 2)
    {
        printf("Indique el n�mero a buscar - \tEjemplo: [user@equipo]$ %s 4\n\n", argv[0]);
        exit(-1);
    }
    numero_buscado = atoi(argv[1]); //Recibe el numero a contrar en el archivo

    //Si no se introduce correctamente n
    if (argc != 3)
    {
        printf("\nIndique el tama�o de N - \nEjemplo: [user@equipo]$ %s %s 1000\n", argv[0], argv[1]);
        exit(-1);
    }
    n_datos = atoi(argv[2]); //Recibe el numero de datos a considerar del archivo

    //Extrae n_datos del archivo y los guarda en A[]
    Arreglo = readTxt(n_datos, archivo_entrada);
    fclose(archivo_entrada);              //Cerramos el archivo de los datos
    abb = llenarArborl(Arreglo, n_datos); //llenamos el abb con los datos del archivo

    //Ejecuta el algoritmo de busqueda
    int indice = busquedaArbol(abb, numero_buscado);

    //Valida si encuentra el numero y de ser el caso muestra la posicion correspondiente
    if (indice >= 0)
    {
        printf("\nSe encontro %i en el arreglo.", numero_buscado);
    }
    else
        printf("\n%d no se encontro\n", numero_buscado);

    //Evaluar los tiempos de ejecucion
    uswtime(&utime1, &stime1, &wtime1);

    //******************************************************************

    printf("\n\tResultados para n: %i datos.\n", n_datos);
    //Calculo del tiempo de ejecucion del programa
    printf("\n");
    printf("real (Tiempo total)  %.10f s\n", wtime1 - wtime0);
    printf("user (Tiempo de procesamiento en CPU) %.10f s\n", utime1 - utime0);
    printf("sys (Tiempo en acciónes de E/S)  %.10f s\n", stime1 - stime0);
    printf("CPU/Wall   %.10f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
    printf("\n");

    //Mostrar los tiempos en formato exponecial
    printf("\n");
    printf("real (Tiempo total)  %.10e s\n", wtime1 - wtime0);
    printf("user (Tiempo de procesamiento en CPU) %.10e s\n", utime1 - utime0);
    printf("sys (Tiempo en acciónes de E/S)  %.10e s\n", stime1 - stime0);
    printf("CPU/Wall   %.10f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
    printf("\n\n");
    //******************************************************************

    free(Arreglo); //Liberamos la memoria del arreglo que contuvo los datos
    return 0;      //Fin del programa
}
