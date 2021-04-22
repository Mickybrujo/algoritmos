#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"

int min(int x, int y) { return (x <= y) ? x : y; }
 
int buscarFibonacci(int arr[], int x, int n)
{
	//Inicialización de variables de la serie fibonacci
    int fib2 = 0; 
    int fib1 = 1; 
    int fibM = fib2 + fib1; 
 
 	/*Se les asignan nuevos valores a fib1, fib2, y fibM para el
	 calculo del algoritmo, tomando como límite n*/ 
    while (fibM < n) {
        fib2 = fib1;
        fib1 = fibM;
        fibM = fib2 + fib1;
    }
 
    int offset = -1;

    while (fibM > 1) {
       
	    //Función para determinar qué número es mayor
	    int i = min(offset + fib2, n - 1);
	
		//Si el número buscado es mayor a los números del arreglo
		//antes de la posición "offset + fib2"
	    if (arr[i] < x) {
	        fibM = fib1;
	        fib1 = fib2;
	        fib2 = fibM - fib1;
	        offset = i; 
	    }
	
		//Si el número buscado es menor a los números del arreglo
		//antes de la posición "offset + fib2"
	    else if (arr[i] > x) {
	        fibM = fib2;
	        fib1 = fib1 - fib2;
	        fib2 = fibM - fib1;
	    }
	
	    else
	        return i;
    }
 
 	//Se retorna la posición del arreglo donde se encuentra el número
    if (fib1 && arr[offset + 1] == x)
        return offset + 1;
 
 	//Si no se encuentra, retorna -1
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
		printf("Indique el número a buscar - \tEjemplo: [user@equipo]$ %s 4\n\n",argv[0]);
		exit(-1);
	}  
	x=atoi(argv[1]);
	
	//Si no se introduce correctamente N
	if (argc!=3) 
	{
		printf("\nIndique el tamaño de N - \nEjemplo: [user@equipo]$ %s %s 1000\n",argv[0],argv[1]);
		exit(-1);
	}
	n_datos=atoi(argv[2]);
	
	//Extrae n_datos del archivo y los guarda en A[]
        A = readTxt(n_datos, archivo_entrada);
        fclose(archivo_entrada); //Cerramos el archivo de los datos
    
	
	//Iniciar el conteo del tiempo para las evaluaciones de rendimiento	
	uswtime(&utime0, &stime0, &wtime0);


	//Ejecuta el algoritmo de busqueda de fibonacci
	int ind = buscarFibonacci(A, x, n_datos);
	
  	if(ind>=0){
    	printf("\nSe encontro %i en el numero del arreglo: %d\n",x,ind);
	}
  	else
    	printf("\n%d no se encontro\n",x);

	
	//Evaluar los tiempos de ejecución
	uswtime(&utime1, &stime1, &wtime1);
	
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

