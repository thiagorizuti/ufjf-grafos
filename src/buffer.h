/*
 * buffer.h
 *
 *  Created on: 01/12/2013
 *      Author: SAA
 */

#ifndef BUFFER_H_INCLUDED
#define BUFFER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_BUFFER 1
#define EOS '\0'
#define TAMANHOVETORPALAVRAS  2

void constroiBuffer(FILE *arquivo);
char proxCaracter();
void destroiBuffer();
void iniciaVetorPalavras();
void insereLetra(char s);
char* retornaVetorPalavras();
void reiniciaVetorPalavras();


#endif // BUFFER_H_INCLUDED

