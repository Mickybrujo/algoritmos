#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tiempo.h"

int busquedaBinaria(int arr[], int izquierda, int derecha, int x);

int min(int x, int y) { return (x <= y) ? x : y; }

int BusquedaExponencial(int arr[], int n, int x)
{
    // Si x esta presente en la primera ubicacion
    if (arr[0] == x)
        return 0;

    // Encuentra el rango para la b�squeda binaria duplicando repetidamente
    int i = 1;
    while (i < n && arr[i] <= x)
        i = i * 2;

    // Llama a la b�squeda binaria para el rango encontrado.
    return busquedaBinaria(arr, i / 2, min(i + 1, n), x);
}

int busquedaBinaria(int arr[], int izquierda, int derecha, int x)
{
    // Nota: el tama�o del arreglo es necesario porque cuando se recibe
    // como argumento no se puede calcular dentro de la funci�n

    while (derecha > izquierda)
    {
        int mid = (izquierda + (derecha - 1)) / 2;

        // Si el elemento est� presente en el medio
        if (arr[mid] == x)
            return mid;

        // Si el elemento es m�s peque�o que mid, entonces solo puede estar presente en el subarreglo izquierdo
        if (arr[mid] > x)
            derecha = mid - 1;

        // De lo contrario, el elemento solo puede estar presente en el subarreglo derecho
        if (arr[mid] < x)
        {
            izquierda = mid + 1;
        }
    }
    return -1;
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
    int n_datos, numero_buscado;                           //Cantidad de datos que el usuario desea considerar para buscar
    archivo_entrada = fopen("10millones.txt", "r");        //Abrimos el archivo con 10 millones de datos en modo lectura

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
    fclose(archivo_entrada); //Cerramos el archivo de los datos

    //Ejecuta el algoritmo de busqueda
    int indice = BusquedaExponencial(Arreglo, n_datos, numero_buscado);

    //Valida si encuentra el numero y de ser el caso muestra la posicion correspondiente
    if (indice >= 0)
    {
        printf("\nSe encontro %i en el numero del arreglo: %d\n", numero_buscado, indice);
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
