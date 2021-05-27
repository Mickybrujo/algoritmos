#!/bin/bash
gcc huffman_coder.c tiempo.c -o compresor.out

./compresor.out nombreArchivoEntrada.ext archivoComprimido  > resultadosTiempos.txt

gcc huffman_decoder.c tiempo.c -o descompresor.out

./descompresor.out archivoComprimido nombreArchivoSalida.ext  >> resultadosTiempos.txt

