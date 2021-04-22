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

struct tree* llenarArborl(int A[], int cant_datos){
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
    while (raiz!=NULL){ // Si el nodo en el que se encuentra es distinto de NULL continua buscando
        if (raiz->dato==numero)  //Si el numero del nodo en el que se encuentra es igual al numero que buscamos regresa el dato del nodo
        {
            return raiz->dato;
        }
        else if (raiz->dato>numero)  // Si el numero que buscamos es menor que el dato del nodo, nos movemos a la izquierda en el arbol
        {
            raiz=raiz->izq;   
        }
        else if (raiz->dato<numero)  // Si el numero que buscamos es mayor que el dato del nodo, nos movemos a la derecha en el arbol
        {
            raiz=raiz->der;
        }
    }
    return -1; // Si se llega a un nodo nulo quiere decir que el dato no se encuntra en el arbol y regresamos -1
}


//Funcion que lee una cantidad de datos de un archivo y regresa un apuntador a un arreglos con los datos
int *readTxt(int cant_datos, FILE *datos)
{
    int *array_datos;
    array_datos = (int *)malloc(sizeof(int) * cant_datos); //Reservamos memoria suficiente para la cantidad de datos
    for (int i = 0; i < cant_datos; i++)                   //Recorremos los datos y los guardamos en el arreglo
    {
        fscanf(datos, "%d", &array_datos[i]);
    }
    return array_datos; //Regresamos el arreglo con los datos
}



int main(int argc, char *argv[])
{
    FILE *archivo_entrada, *archivo_ordenado;              //Apuntador de archivos para lectura de los datos y escritura del ordenamiento
    double utime0, stime0, wtime0, utime1, stime1, wtime1; //Variables para medición de tiempos
    int *A;                                                //Apuntador a un arreglo de enteros que contendra los datos a ordenar
    int numero,cant_datos,resultado; //Declaramos el numero a buscar, la cantidad de datos que tomaremos del archivo y el resultado de la busqueda
    struct tree *abb=NULL;   //Declaramos la raiz del arbol
    archivo_entrada = fopen("numeros10millones.txt", "r"); //Abrimos el archivo con 10 millones de datos en modo lectura
    //Validamos si hubo errores al abrir el archivo
    if (archivo_entrada == NULL)
    {
        printf("No se pudo abrir el archivo :C. \n");
        return 1;
    }
    //Si no se introducen exactamente 3 argumentos (Cadena de ejecución y cadena=n)
    if (argc != 3)
    {
        printf("\nIndique el tamanio del espacion de busqueda y numero a buscar - Ejemplo: [user@equipo]$ %s 100\n", argv[0]);
        exit(1);
    }
    //Tomar el segundo argumento como tamaño del espacion de busqueda y el tercero como el dato a buscar en el abb
    else
    {
        cant_datos = atoi(argv[1]);
        numero = atoi(argv[2]);
    }

    //Extrae n_datos del archivo y los guarda en A[]
    A = readTxt(cant_datos, archivo_entrada);
    fclose(archivo_entrada); //Cerramos el archivo de los datos
    abb=llenarArborl(A,cant_datos); //llenamos el abb con los datos del archivo

    //Iniciar el conteo del tiempo para las evaluaciones de rendimiento
    //******************************************************************
    uswtime(&utime0, &stime0, &wtime0);

    //Algoritmo:
    
    //Busca el dato en el arbol y almacena el resultado en la variable corresponidente
    resultado=busquedaArbol(abb,numero);
    if (resultado!=-1) // Si resultado != -1 el dato imprimer el dato encontrado
    {
        printf("\nNumero encontrado: %i\n",resultado);
    }
    else{   // Si resultado =-1 el dato no se encontraba en el arbol e imprime un error
        printf("\nNumero no encontrado\n");
    }
    
 
    //Evaluar tiempos de ejecucion
    uswtime(&utime1, &stime1, &wtime1);

    //******************************************************************

    printf("\n\tResultados de buscar %i en %i datos.\n", numero,cant_datos);
    //Cálculo del tiempo de ejecución del programa
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
    printf("\n");
    //******************************************************************
    return 0;                               //Fin del programa
}
