/*
 * buffer.c
 *
 *  Created on: 01/12/2013
 *      Author: SAA
 */


#include "buffer.h"


FILE *arquivo;
char buffer[TAMANHO_BUFFER];
int indiceBuffer, indiceVetor, tamanhoVetor;
char* vetorPalavras;

/** Constói um buffer de tamanho TAMANHO_BUFFER e insere uma sentinela ao final se a quantidade de
caracteres for menor que o tamanho total do mesmo **/
void constroiBuffer(FILE *arquivoentrada){
    arquivo = arquivoentrada;
    indiceBuffer = 0;
    int cont = fread(buffer, sizeof(char), TAMANHO_BUFFER * sizeof(char),arquivo);
        if (cont < TAMANHO_BUFFER){
            buffer[cont] = EOS;
        }
}

void recarregarBuffer(){
    int cont = fread(buffer, sizeof(char), TAMANHO_BUFFER * sizeof(char), arquivo);
        if(cont < TAMANHO_BUFFER){
            buffer[cont] = EOS;
        }
    indiceBuffer = 0;
}

char proxCaracter(){
     if(feof(arquivo) && buffer[indiceBuffer] == EOS){
        return EOF;
    }else if(indiceBuffer >= TAMANHO_BUFFER){
        recarregarBuffer();
        return proxCaracter();
    }else {
        indiceBuffer++;
        return buffer[indiceBuffer-1];
    }
}

void destroiBuffer(){
    fclose(arquivo);
}

void iniciaVetorPalavras(){
	indiceVetor = 0;
	tamanhoVetor = 0;
	vetorPalavras = (char*) malloc(sizeof(char) * TAMANHOVETORPALAVRAS);
}

void insereLetra(char s){
	if(indiceVetor >= tamanhoVetor - 1){
		tamanhoVetor = indiceVetor + TAMANHOVETORPALAVRAS;
		vetorPalavras = (char*) realloc(vetorPalavras, sizeof(char) * (tamanhoVetor));
	}
	vetorPalavras[indiceVetor] = s;
	indiceVetor++;
	vetorPalavras[indiceVetor] = EOS;
}

char* retornaVetorPalavras(){
    return vetorPalavras;
}

void reiniciaVetorPalavras(){
    indiceVetor = 0;
}
