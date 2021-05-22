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
    Codifica un fichero utilizando el algoritmo de Huffman.
*/
//Compilación de la libreria: "gcc huffman_coder.c" (Generación del ejecutable)
//*****************************************************************

#include <stdlib.h>
#include <stdio.h>

struct tree
{
    char caracter;
    int repeticiones;
    int etiqueta;
    struct tree *izq, *der;
};

struct list
{
    struct tree *nodo;
    struct list *next;
};

void insertarLista(struct list **lista, int caracter, int dato){
    struct list *nuevo=NULL;
    struct list *inicio=(*lista);
    nuevo=(struct list *)malloc(sizeof(struct list));
    nuevo->nodo=(struct tree *)malloc(sizeof(struct tree ));
    nuevo->nodo->repeticiones=dato;
    if (caracter!=-1)
    {
        nuevo->nodo->caracter = (char) caracter;
    }
    if (!(*lista)||dato<=(*lista)->nodo->repeticiones)
    {
        nuevo->next= (*lista);
        (*lista) = nuevo;
        return;
    }
    while ((*lista)->next)
    {
        if ((*lista)->next->nodo->repeticiones>=dato)
        {
            nuevo->next=(*lista)->next;
            (*lista)->next=nuevo;
            (*lista)=inicio;
            return;
        }
        (*lista)=(*lista)->next;
    }
    nuevo->next=NULL;
    (*lista)->next=nuevo;
    (*lista)=inicio;
}

void mostrarLista (struct list *lista)
{
  while (lista)
    {
      printf ("\n%c\t%i", lista->nodo->caracter,lista->nodo->repeticiones);
      lista = lista->next;
    }
}




int main(int argc, char *argv[])
{
    FILE *archivo_entrada;
    struct list *lista=NULL;
    char *A;
    int tam_archivo;
    int repeticiones[256]={0};                                           
    archivo_entrada = fopen("prueba", "rb"); //prueba: nombre del archivo con extension ej: michis.mp4
    fseek(archivo_entrada, 0L, SEEK_END);
    tam_archivo=ftell(archivo_entrada);
    A=(char *)malloc(sizeof(char) * tam_archivo); //No quitar, se rompe :c
    fseek(archivo_entrada, 0L, SEEK_SET);
    while (!feof(archivo_entrada))
    {
        ++repeticiones[fgetc(archivo_entrada)];
    }
    for (int j = 0; j < 255; j++)
    {
        if(repeticiones[j]!=0){
            insertarLista(&lista,j,repeticiones[j]);
        }
    }
    mostrarLista(lista);
    printf("\n\n\t%d\n",tam_archivo);
    
    fclose(archivo_entrada); //Cerramos el archivo de los datos
    
    return 0;                               //Fin del programa
}