#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tiempo.h"

int busquedaBinaria(int arr[], int x, int n){
    // Nota: el tamaño del arreglo es necesario porque cuando se recibe
    // como argumento no se puede calcular dentro de la función
    
    int izquierda = 0, derecha = n - 1;
    
    while (izquierda <= derecha){
        int indiceDeLaMitad = floor((izquierda + derecha) / 2); 
		// Calcula el valor integral más grande que no sea mayor de x.

        int valorQueEstaEnElMedio = arr[indiceDeLaMitad];

        if (x == valorQueEstaEnElMedio){
            // En caso de encontrar lo que buscamos, terminamos la función
            // y regresamos el índice
            return indiceDeLaMitad;
        }
        
        if (x < valorQueEstaEnElMedio){
            // Entonces está hacia la izquierda
            derecha = indiceDeLaMitad - 1;
        }else{
            // Está hacia la derecha
            izquierda = indiceDeLaMitad + 1;
        }
    }
    // Termina el ciclo y no encontramos nada
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

//Funcion para guardar los datos ordenados en un archivo
void writeOrd(int cant_datos, FILE *datos, int A[])
{
    int i;
    for (i = 0; i < cant_datos; i++)
    {
        fprintf(datos, "%d\n", A[i]); //Guarda un dato por renglon de los datos que fueron ordenados
    }
}


//Programa Principal 
int main (int argc, char* argv[])
{		
	FILE *archivo_entrada;                                     //Apuntador de archivos para lectura de los datos y escritura del ordenamiento
        double utime0, stime0, wtime0, utime1, stime1, wtime1; //Variables para medición de tiempos
        int *A;                                                //Apuntador a un arreglo de enteros que contendra los datos a ordenar
        int n_datos, x;                                        //Cantidad de datos que el usuario desea tomar para ordenar
        archivo_entrada = fopen("10millones.txt", "r");        //Abrimos el archivo con 10 millones de datos en modo lectura
    
	//Validamos si hubo errores al abrir el archivo
	if (archivo_entrada == NULL)
        {
        printf("No se pudo abrir el archivo :C. \n");
        return 1;
        }
    
	//Si se introducen menos de dos argumentos (Cadena de ejecución y cadena=n)
	if (argc<2) 
	{
		printf("Indique el número a buscar \n\n");
		scanf("%d", &x);
		//exit(-1);
	}  
	//x=atoi(argv[1]);
	
	//Si no se introduce correctamente N
	if (argc!=3) 
	{
		printf("\nIndique el tamaño de N \n\n");
		scanf("%d", &n_datos);
		//exit(-1);
	}
	//n_datos=atoi(argv[2]);
	
	//Extrae n_datos del archivo y los guarda en A[]
        A = readTxt(n_datos, archivo_entrada);
        fclose(archivo_entrada); //Cerramos el archivo de los datos
    
	//Inicia el conteo de tiempo para las evaluaciones de rendimiento
	//uswtime(&utime0, &stime0, &wtime0);
	
	//Ejecuta el algoritmo de busqueda Binaria
	
	int ind = busquedaBinaria(A, x, n_datos);
	
  	if(ind>=0){
    	printf("\nSe encontro %i en la lista de numeros\n",x);
	}
  	else
    	printf("\n%d no se encontro\n",x);
    	
	//Evaluar los tiempos de ejecución
	//uswtime(&utime1, &stime1, &wtime1);
	
    //******************************************************************

    printf("\n\tResultados para n: %i datos.\n", n_datos);
	//Cálculo del tiempo de ejecución del programa
	printf("\n");
	printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciÃ³nes de E/S)  %.10f s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	
	//Mostrar los tiempos en formato exponecial
	printf("\n");
	printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciÃ³nes de E/S)  %.10e s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n\n");
	//******************************************************************


    free(A);                                //Liberamos la memoria del arreglo que contuvo los datos
    return 0;                               //Fin del programa	
}


