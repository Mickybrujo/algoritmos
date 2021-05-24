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
//Compilación de la libreria: "gcc huffman_decoder.c" (Generación del ejecutable)
//*****************************************************************

#include <stdlib.h>
#include <stdio.h>

struct tree
{
    char caracter;
    int code;
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
    struct tree *arbol, *hoja, *raiz;
    long int tam_archivo;
    int n_elementos;
    int bit;
    unsigned long int palabra;
    int num_bits;
    int tam_code;
    unsigned char caracter;
    arbol=(struct tree *)malloc(sizeof(struct tree ));
    arbol->caracter=0;
    arbol->der=NULL;
    arbol->izq=NULL;
    archivo_comprimido=fopen("comprimido","rb");
    fread(&tam_archivo,sizeof(long int),1,archivo_comprimido);
    fread(&n_elementos,sizeof(int),1,archivo_comprimido);
    //printf("\n%li->%i",tam_archivo,n_elementos);
    for (int i = 0; i < n_elementos; i++)
    {
        hoja=(struct tree *)malloc(sizeof(struct tree ));
        fread(&hoja->caracter,sizeof(char),1,archivo_comprimido);
        fread(&hoja->code,sizeof(int),1,archivo_comprimido);
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
    //recorridoinorden(arbol);
    palabra=0;
    archivo_salida=fopen("des.txt","w");
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
    return 0;
}

