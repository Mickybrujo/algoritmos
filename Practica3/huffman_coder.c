#include <stdlib.h>
#include <stdio.h>

struct tree
{
    char caracter;
    int repeticiones;
    int etiqueta;
    struct tree *izq, *der;
};


int *readTxt(int cant_datos, FILE *datos) /*editar*/
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


int main(int argc, char *argv[])
{
    FILE *archivo_entrada;
    char *A;
    int tam_archivo;
    int repeticiones[256]={0};                                           
    archivo_entrada = fopen("prueba", "rb"); //prueba: nombre del archivo con extension
    fseek(archivo_entrada, 0L, SEEK_END);
    tam_archivo=ftell(archivo_entrada);
    A=(char *)malloc(sizeof(char) * tam_archivo);
    fseek(archivo_entrada, 0L, SEEK_SET);
    while (!feof(archivo_entrada))
    {
        ++repeticiones[fgetc(archivo_entrada)];
    }
    // for ( int i = 0; i <= tam_archivo; i++)
    // {
    //     ++repeticiones[fgetc(archivo_entrada)];
    // }
    
    for (int j = 0; j < 255; j++)
    {
        if(repeticiones[j]!=0)printf("\n%c\t%i",(char)j,repeticiones[j]);
    }
    printf("\n\n\t%d\n",tam_archivo);
    
    fclose(archivo_entrada); //Cerramos el archivo de los datos
    
    return 0;                               //Fin del programa
}