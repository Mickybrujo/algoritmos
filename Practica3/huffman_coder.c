//*****************************************************************
//HUFFMAN_CODER.C
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
    Codifica un fichero utilizando el codigo de Huffman.
*/
//Compilación de la libreria: "gcc huffman_coder.c tiempo.c" (Generación del ejecutable)
//*****************************************************************

#include <stdlib.h>
#include <stdio.h>
#include "tiempo.h"

struct tree
{
    unsigned char caracter;
    int repeticiones;
    struct tree *izq, *der;
};

struct list
{
    struct tree *nodo;
    struct list *next;
};

struct table
{
    unsigned char caracter;
    unsigned long int code;
    unsigned char tam_code;
    struct table *next;
};

void insertarLista(struct list **lista, int caracter, int dato, struct tree *hoja_izq, struct tree *hoja_der)
{
    struct list *nuevo = NULL;
    struct list *inicio = (*lista);
    nuevo = (struct list *)malloc(sizeof(struct list));
    nuevo->nodo = (struct tree *)malloc(sizeof(struct tree));
    nuevo->nodo->izq = hoja_izq;
    nuevo->nodo->der = hoja_der;
    nuevo->nodo->repeticiones = dato;
    if (caracter != -1)
    {
        nuevo->nodo->caracter = (char)caracter;
    }
    if (!(*lista) || dato <= (*lista)->nodo->repeticiones)
    {
        nuevo->next = (*lista);
        (*lista) = nuevo;
        return;
    }
    while ((*lista)->next)
    {
        if ((*lista)->next->nodo->repeticiones >= dato)
        {
            nuevo->next = (*lista)->next;
            (*lista)->next = nuevo;
            (*lista) = inicio;
            return;
        }
        (*lista) = (*lista)->next;
    }
    nuevo->next = NULL;
    (*lista)->next = nuevo;
    (*lista) = inicio;
}

void mostrarLista(struct list *lista)
{
    while (lista)
    {
        printf("\n%c\t%i", lista->nodo->caracter, lista->nodo->repeticiones);
        lista = lista->next;
    }
}

void mostrarTabla(struct table *tabla)
{
    while (tabla)
    {
        printf("\n%c\t%li\t%i", tabla->caracter, tabla->code, tabla->tam_code);
        tabla = tabla->next;
    }
}

struct list *extraerLista(struct list **lista)
{
    struct list *aux = (*lista);
    (*lista) = (*lista)->next;
    return aux;
}

struct tree *codigoHuffman(struct list **lista)
{
    struct list *hoja_izq = NULL, *hoja_der = NULL;
    int sum_frec;
    while ((*lista)->next)
    {
        hoja_izq = (struct list *)extraerLista(lista);
        hoja_der = (struct list *)extraerLista(lista);
        sum_frec = hoja_izq->nodo->repeticiones + hoja_der->nodo->repeticiones;
        insertarLista(lista, -1, sum_frec, hoja_izq->nodo, hoja_der->nodo);
    }
    return (*lista)->nodo;
}

void recorridoinorden(struct tree *raiz)
{
    if (raiz) // Verifica si la hoja en la que no es valida y no apunta a NULL
    {
        //Recorrido InOrden usando recursividad
        recorridoinorden(raiz->izq);
        printf("\n\t%i ", raiz->repeticiones);
        ;
        recorridoinorden(raiz->der);
    }
}

void insertarTabla(struct table **tabla, unsigned char caracter, int tam_code, int code)
{
    struct table *nuevo = NULL;
    nuevo = (struct table *)malloc(sizeof(struct table));
    nuevo->caracter = caracter;
    nuevo->code = code;
    nuevo->tam_code = tam_code;
    nuevo->next = (*tabla);
    (*tabla) = nuevo;
}

void generarCodigos(struct table **tabla, struct tree *raiz, int tam_code, int code)
{
    if (raiz->izq)
    {
        generarCodigos(tabla, raiz->izq, tam_code + 1, code << 1);
    }
    if (raiz->der)
    {
        generarCodigos(tabla, raiz->der, tam_code + 1, (code << 1) | 1);
    }
    if (!(raiz->der && raiz->izq))
    {
        insertarTabla(tabla, raiz->caracter, tam_code, code);
    }
}

void escribirTabla(struct table *tabla, FILE *archivo)
{
    while (tabla)
    {
        fwrite(&tabla->caracter, sizeof(char), 1, archivo);
        fwrite(&tabla->code, sizeof(unsigned long int), 1, archivo);
        fwrite(&tabla->tam_code, sizeof(char), 1, archivo);
        tabla = tabla->next;
    }
}

struct table *buscarTabla(struct table *tabla, unsigned char caracter)
{
    while (tabla)
    {
        if (tabla->caracter == caracter)
        {
            return tabla;
        }
        tabla = tabla->next;
    }
    return NULL; //Regresa NULL si no se encuentra, caso que sucede cuando feof(archivo)=TRUE
}

int main(int argc, char *argv[])
{
    FILE *archivo_entrada, *archivo_comprimido;
    double utime0, stime0, wtime0, utime1, stime1, wtime1; //Variables para medición de tiempos
    struct list *lista = NULL;
    struct table *tabla = NULL;
    struct table *elem_tabla = NULL;
    struct tree *arbol = NULL;
    char *A, caracter;
    long int tam_archivo;
    int n_elementos = 0;
    int num_bits = 0;
    unsigned long int palabra = 0;
    int repeticiones[256] = {0};

    //Si no se introducen exactamente 3 argumentos (Cadena de ejecución y nombres de ficheros)
    if (argc != 3)
    {
        printf("\nIngrese los archivos de entrada y salida - Ejemplo: [user@equipo]$ %s <archivo de entrada> <archivo comprimido>\n", argv[0]);
        exit(1);
    }
    //Tomar el nombre de los ficheros
    else
    {
        archivo_entrada = fopen(argv[1], "r"); //prueba: nombre del archivo con extension ej: michis.mp4
        archivo_comprimido = fopen(argv[2], "wb");
    }

    if (archivo_entrada == NULL)
    {
        printf("No se pudo abrir el archivo. \n");
        return 1;
    }

    fseek(archivo_entrada, 0L, SEEK_END);
    tam_archivo = ftell(archivo_entrada);
    A = (char *)malloc(sizeof(char) * tam_archivo); //No quitar, se rompe :c
    fseek(archivo_entrada, 0L, SEEK_SET);

    //Iniciar el conteo del tiempo para las evaluaciones de rendimiento
    //******************************************************************
    uswtime(&utime0, &stime0, &wtime0);

    while (!feof(archivo_entrada))
    {
        ++repeticiones[fgetc(archivo_entrada)];
    }
    for (int j = 0; j < 256; j++)
    {
        if (repeticiones[j] != 0)
        {
            n_elementos++;
            insertarLista(&lista, j, repeticiones[j], NULL, NULL);
        }
    }
    arbol = codigoHuffman(&lista);
    generarCodigos(&tabla, arbol, 0, 0);
    fwrite(&tam_archivo, sizeof(long int), 1, archivo_comprimido);
    fwrite(&n_elementos, sizeof(int), 1, archivo_comprimido);
    escribirTabla(tabla, archivo_comprimido);
    fseek(archivo_entrada, 0L, SEEK_SET);
    while (!feof(archivo_entrada))
    {
        caracter = fgetc(archivo_entrada);
        elem_tabla = buscarTabla(tabla, caracter);
        if (elem_tabla == NULL)
            break; // Termina si no se encontro elemento (eof)
        while (num_bits + elem_tabla->tam_code > 32)
        {
            caracter = palabra >> (num_bits - 8);
            fwrite(&caracter, sizeof(char), 1, archivo_comprimido);
            num_bits -= 8;
        }
        palabra <<= elem_tabla->tam_code;
        palabra |= elem_tabla->code;
        num_bits += elem_tabla->tam_code;
    }
    while (num_bits > 0)
    {
        if (num_bits >= 8)
        {
            caracter = palabra >> (num_bits - 8);
        }
        else
        {
            caracter = palabra << (8 - num_bits);
        }
        fwrite(&caracter, sizeof(char), 1, archivo_comprimido);
        num_bits -= 8;
    }
    fclose(archivo_entrada); //Cerramos el archivo de los datos
    fclose(archivo_comprimido);

    //Evaluar tiempos de ejecucion
    uswtime(&utime1, &stime1, &wtime1);

    //******************************************************************

    printf("\n\tResultados de tiempos para comprimir el archivo: %s \n", argv[1]);
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

    return 0; //Fin del programa
}