//*****************************************************************
//HUFFMAN_DECODER.C
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
//Mayo 2021
//ESCOM-IPN
//Descripcion:
/*
    Decodifica un fichero codificado con el codigo de Huffman.
*/
//Compilación de la libreria: "gcc huffman_decoder.c tiempo.c" (Generación del ejecutable)
//*****************************************************************

#include <stdlib.h>
#include <stdio.h>
#include "tiempo.h"

struct tree
{
    unsigned char caracter;
    unsigned long int code;
    char tam_code;
    struct tree *izq, *der;
};

void recorridoinorden(struct tree *raiz)
{
    if (raiz) // Verifica si la hoja en la que no es valida y no apunta a NULL
    {
        //Recorrido InOrden usando recursividad
        recorridoinorden(raiz->izq);
        printf("\n\t%c ",raiz->caracter);;
        recorridoinorden(raiz->der);
    }
}

int main(int argc, char const *argv[])
{
    FILE *archivo_salida,*archivo_comprimido;
    double utime0, stime0, wtime0, utime1, stime1, wtime1; //Variables para medición de tiempos
    struct tree *arbol, *hoja, *raiz;
    unsigned long int palabra;
    long int tam_archivo;
    int n_elementos;
    int tam_code;
    unsigned char caracter;
    arbol=(struct tree *)malloc(sizeof(struct tree ));
    arbol->caracter=0;
    arbol->der=NULL;
    arbol->izq=NULL;

    //Si no se introducen exactamente 3 argumentos (Cadena de ejecución y nombres de ficheros)
    if (argc != 3)
    {
        printf("\nIngrese los archivos de entrada y salida - Ejemplo: [user@equipo]$ %s <archivo comprimido> <archivo de salida>\n", argv[0]);
        exit(1);
    }
    //Tomar el nombre de los ficheros
    else
    {
        archivo_comprimido = fopen(argv[1],"rb");
        archivo_salida=fopen(argv[2],"w");
    }

    fread(&tam_archivo,sizeof(long int),1,archivo_comprimido);
    fread(&n_elementos,sizeof(int),1,archivo_comprimido);

    //Iniciar el conteo del tiempo para las evaluaciones de rendimiento
    //******************************************************************
    uswtime(&utime0, &stime0, &wtime0);

    for (int i = 0; i < n_elementos; i++)
    {
        hoja=(struct tree *)malloc(sizeof(struct tree ));
        fread(&hoja->caracter,sizeof(char),1,archivo_comprimido);
        fread(&hoja->code,sizeof(unsigned long int),1,archivo_comprimido);
        fread(&hoja->tam_code,sizeof(char),1,archivo_comprimido);
        hoja->der=NULL;
        hoja->izq=NULL;
        tam_code=1<<(hoja->tam_code-1);
        raiz=arbol;
        while (tam_code>1)
        {
            if (hoja->code & tam_code)
            {
                if (raiz->der)
                {
                    raiz=raiz->der;
                }
                else
                {
                    raiz->der=(struct tree *)malloc(sizeof(struct tree ));
                    raiz=raiz->der;
                    raiz->caracter=0;
                    raiz->der=NULL;
                    raiz->izq=NULL;
                }   
            }
            else
            {
                if (raiz->izq)
                {
                    raiz=raiz->izq;
                }
                else
                {
                    raiz->izq=(struct tree *)malloc(sizeof(struct tree ));
                    raiz=raiz->izq;
                    raiz->caracter=0;
                    raiz->der=NULL;
                    raiz->izq=NULL;
                } 
            }
            tam_code >>=1;
        }
    
        if (hoja->code & 1)
        {
            raiz->der=hoja;
        }
        else
        {
            raiz->izq=hoja;
        }
    }
    palabra=0;
    fread(&caracter,sizeof(char),1,archivo_comprimido);
    palabra|=caracter;
    palabra<<=8;
    fread(&caracter,sizeof(char),1,archivo_comprimido);
    palabra|=caracter;
    palabra<<=8;
    fread(&caracter,sizeof(char),1,archivo_comprimido);
    palabra|=caracter;
    palabra<<=8;
    fread(&caracter,sizeof(char),1,archivo_comprimido);
    palabra|=caracter;
    tam_code=0;
    raiz=arbol;
    while (tam_archivo)
    {
        if (palabra & 0x80000000)
        {
            raiz=raiz->der;
        }
        else
        {
            raiz=raiz->izq;
        }
        palabra <<=1;
        tam_code++; 
        if (tam_code==8)
        {
            fread(&caracter,sizeof(char),1,archivo_comprimido);
            palabra|=caracter;
            tam_code=0;
        }
        if (!raiz->der && !raiz->izq)
        {
            putc(raiz->caracter, archivo_salida);
            tam_archivo--;
            raiz=arbol;
        }
          
    }
    fclose(archivo_comprimido);
    fclose(archivo_salida);
    free(arbol);

    //Evaluar tiempos de ejecucion
    uswtime(&utime1, &stime1, &wtime1);

    //******************************************************************

    printf("\n\tResultados para: %s\n",argv[1]);
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

    return 0;
}

