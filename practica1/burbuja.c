#include <stdlib.h>
#include <stdio.h>
#include "tiempo.h"

// Funcion para ordenar datos con el mmetodo de la burbuja
int burbuja(int A[], int cant_datos) //Recibe el arreblo y el numero de datos a ordenar
{
    int aux = 0;                             //Auxiliar para intercambiar de posicion los numeros
    for (int i = 0; i < cant_datos - 1; i++) //Recorrido a traves de todo el arreglo
    {
        for (int j = 0; j < (cant_datos - 1) - i; j++) //Recorrido de cada numero comparado con los que le siguen en el arreglo
        {
            if (A[j] > A[j + 1]) //Verifica si el numero en turno es mayor que el que siguiente en el arreglo
            {
                aux = A[j];      //Guarda el numero en turno en la variable auxiliar
                A[j] = A[j + 1]; //Asigna el numero que le sigue en la posicion actual
                A[j + 1] = aux;  //Acomoda el numero de la variable auxiliar en la siguiente posicion
            }
        }
    }
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

//Funcion para guardar los datos ordenados en un archivo
void writeOrd(int cant_datos, FILE *datos, int A[])
{
    for (int i = 0; i < cant_datos; i++)
    {
        fprintf(datos, "%d\n", A[i]); //Guarda un dato por renglon de los datos que fueron ordenados
    }
}

int main(int argc, char *argv[])
{
    FILE *archivo_entrada, *archivo_ordenado;              //Apuntador de archivos para lectura de los datos y escritura del ordenamiento
    double utime0, stime0, wtime0, utime1, stime1, wtime1; //Variables para medición de tiempos
    int *A;                                                //Apuntador a un arreglo de enteros que contendra los datos a ordenar
    int n_datos;                                           //Cantidad de datos que el usuario desea tomar para ordenar
    archivo_entrada = fopen("numeros10millones.txt", "r"); //Abrimos el archivo con 10 millones de datos en modo lectura
    //Validamos si hubo errores al abrir el archivo
    if (archivo_entrada == NULL)
    {
        printf("No se pudo abrir el archivo :C. \n");
        return 1;
    }
    //Si no se introducen exactamente 2 argumentos (Cadena de ejecución y cadena=n)
    if (argc != 2)
    {
        printf("\nIndique el tamanio del algoritmo - Ejemplo: [user@equipo]$ %s 100\n", argv[0]);
        exit(1);
    }
    //Tomar el segundo argumento como tamaño del algoritmo
    else
    {
        n_datos = atoi(argv[1]);
    }

    //Extrae n_datos del archivo y los guarda en A[]
    A = readTxt(n_datos, archivo_entrada);
    fclose(archivo_entrada); //Cerramos el archivo de los datos

    //Iniciar el conteo del tiempo para las evaluaciones de rendimiento
    //******************************************************************
    uswtime(&utime0, &stime0, &wtime0);

    //Ejecuta el algoritmo de ordenamiento bubblesort
    burbuja(A, n_datos);

    //Evaluar tiempos de ejecucion
    uswtime(&utime1, &stime1, &wtime1);

    //******************************************************************

    printf("\n\tResultados para: %i datos.\n", n_datos);
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

    archivo_ordenado = fopen("numerosordenadosburbuja.txt", "w"); //Abrimos o creamos el archivo en el que se guadaran los datos ordenados

    //Validamos si hubo errores al abrir el archivo
    if (archivo_entrada == NULL)
    {
        printf("No se pudo abrir el archivo :C. \n");
        return 1;
    }

    writeOrd(n_datos, archivo_ordenado, A); //Escribimos los datos ordenados en el archivo correspondiente
    fclose(archivo_ordenado);               //Cerramos el archivo con los datos ordenados
    free(A);                                //Liberamos la memoria del arreglo que contuvo los datos
    return 0;                               //Fin del programa
}
