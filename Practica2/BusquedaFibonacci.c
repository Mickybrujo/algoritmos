//*****************************************************************
//BUSQUEDAFIBONACCI.C
//*****************************************************************
//*****************************************************************
//Integrantes: Amazul
/*
    2019630068 ANGELES HERNANDEZ JESUS EDUARDO 
    2015060081 BAEZA COLIN ANA KAREN
    2019630052 BECERRA RAMIREZ LUIS ARTURO 
    2018630131 BUSTAMANTE MENDOZA MIGUEL IMANOL
    */
//Curso: Análisis de algoritmos
//Grupo: 3CM12
//Carrera: Ingenieria en Sistemas Computacionales (Plan 2009)
//Abril 2021
//ESCOM-IPN
//Descripcion:
/*
    Busqueda de un numero entero en un arreglo ordenado de enteros utilizando el 
    metodo de busqueda Fibonacci de forma iterativa.
    */
//Compilación de la libreria: "gcc BusquedaFibonacci.c tiempo.c" (Generación del ejecutable)
//*****************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"

int min(int x, int y) { return (x <= y) ? x : y; }

int buscarFibonacci(int arr[], int x, int n)
{
	//Inicializaci�n de variables de la serie fibonacci
	int fib2 = 0;
	int fib1 = 1;
	int fibM = fib2 + fib1;

	/*Se les asignan nuevos valores a fib1, fib2, y fibM para el
	 calculo del algoritmo, tomando como l�mite n*/
	while (fibM < n)
	{
		fib2 = fib1;
		fib1 = fibM;
		fibM = fib2 + fib1;
	}

	int offset = -1;

	while (fibM > 1)
	{

		//Funci�n para determinar qu� n�mero es mayor
		int i = min(offset + fib2, n - 1);

		//Si el n�mero buscado es mayor a los n�meros del arreglo
		//antes de la posici�n "offset + fib2"
		if (arr[i] < x)
		{
			fibM = fib1;
			fib1 = fib2;
			fib2 = fibM - fib1;
			offset = i;
		}

		//Si el n�mero buscado es menor a los n�meros del arreglo
		//antes de la posici�n "offset + fib2"
		else if (arr[i] > x)
		{
			fibM = fib2;
			fib1 = fib1 - fib2;
			fib2 = fibM - fib1;
		}

		else
			return i;
	}

	//Se retorna la posici�n del arreglo donde se encuentra el n�mero
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
	for (i = 0; i < cant_datos; i++)					   //Recorremos los datos y los guardamos en el arreglo
	{
		fscanf(datos, "%d", &array_datos[i]);
	}
	return array_datos; //Regresamos el arreglo con los datos
}

//Programa Principal
int main(int argc, char *argv[])
{
	FILE *archivo_entrada;								   //Apuntador de archivos para lectura de los datos
	double utime0, stime0, wtime0, utime1, stime1, wtime1; //Variables para medicion de tiempos
	int *Arreglo;										   //Apuntador a un arreglo de enteros que contienelos datos
	int n_datos, numero_buscado;						   //Cantidad de datos que el usuario desea considerar para buscar
	archivo_entrada = fopen("10millones.txt", "r");		   //Abrimos el archivo con 10 millones de datos en modo lectura

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
	int indice = buscarFibonacci(Arreglo, numero_buscado, n_datos);

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
	return 0;	   //Fin del programa
}
