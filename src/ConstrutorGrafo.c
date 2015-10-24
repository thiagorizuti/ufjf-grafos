/*
 * ConstrutorGrafo.c
 *
 *  Created on: 09/12/2013
 *      Author: luã
 */

#include "ConstrutorGrafo.h"


//Nome: IniMatrizAdj
//Função: Inicializa e preeche uma matriz de adjacência a partir de um arquivo de texto
//Entrada: Ponteiro para arquivo de texto, informação sobre natureza do da estrutura (grafo/digrafo)
//Saída: Ponteiro para o endereço de memória da estrutura criada
GrafoAdj* IniMatrizAdj(FILE *entrada, int digrafo){

	FILE *arquivoEntrada = entrada;
    GrafoAdj *g;
    constroiBuffer(arquivoEntrada);

    int fimArquivo = FALSE;
    int state = 0;
    void iniciaVetorPalavras();
    char caracter = proxCaracter();
    int origem,destino;


    while(fimArquivo == FALSE){
        switch(state){
            case 0:
                switch(caracter){
                    case '\n':
                        state = 1;
                        if (digrafo == TRUE) g = MatrizAdjacencia((int)atoi(retornaVetorPalavras()),TRUE);
                        else g = MatrizAdjacencia((int)atoi(retornaVetorPalavras()),FALSE);
                        reiniciaVetorPalavras();
                        caracter = proxCaracter();
                    break;
                    case EOF: fclose(arquivoEntrada); fimArquivo = TRUE;
					break;
                    default:
                        state = 0;
                        insereLetra(caracter);
                        caracter = proxCaracter();
                    break;
                }
            break;
            case 1:
                switch(caracter){
                    case ' ':
                        state = 2;
                        origem = (int)atoi(retornaVetorPalavras()) - 1;
                        reiniciaVetorPalavras();
                        caracter = proxCaracter();
                    break;
                    case EOF: fclose(arquivoEntrada); fimArquivo = TRUE;
					break;
                    default:
                        state = 1;
                        insereLetra(caracter);
                        caracter = proxCaracter();
                    break;
                }
            break;
            case 2:
                switch(caracter){
                    case '\n':
                        state = 1;
                        destino = (int)atoi(retornaVetorPalavras()) - 1;
                        reiniciaVetorPalavras();
                        caracter = proxCaracter();
                    break;
                    case ' ':
                        state = 3;
                        destino = (int)atoi(retornaVetorPalavras()) - 1;
                        reiniciaVetorPalavras();
                        caracter = proxCaracter();
					break;
                    case EOF:
                    	MatrizAdjacenciaInsereAresta(g, origem, (int)atoi(retornaVetorPalavras()) - 1,1);
                        reiniciaVetorPalavras();
                        fclose(arquivoEntrada);
                        fimArquivo = TRUE;
                    break;
                    default:
                        state = 2;
                        insereLetra(caracter);
                        caracter = proxCaracter();
                    break;
                }
            break;
            case 3:
            	switch(caracter){
            		case '\n':
            			state = 1;
            			MatrizAdjacenciaInsereAresta(g, origem, destino, (double)atof(retornaVetorPalavras()));
            			reiniciaVetorPalavras();
            			caracter = proxCaracter();
            		break;
            		case EOF:
            			MatrizAdjacenciaInsereAresta(g, origem, destino, (double)atof(retornaVetorPalavras()));
                        reiniciaVetorPalavras();
                        fclose(arquivoEntrada);
                        fimArquivo = TRUE;
            		break;
            		default:
            			state = 3;
            			insereLetra(caracter);
            			caracter = proxCaracter();
            		break;
            	}
            break;

        }

    }
    return g;
}

//Nome: IniListaAdj
//Função: Inicializa e preeche uma lista de adjacência a partir de um arquivo de texto
//Entrada: Ponteiro para arquivo de texto, informação sobre natureza do da estrutura (grafo/digrafo)
//Saída: Ponteiro para o endereço de memória da estrutura criada
GrafoListAdj* IniListaAdj(FILE *entrada, int digrafo){

	FILE *arquivoEntrada = entrada;
    GrafoListAdj *g;
    constroiBuffer(arquivoEntrada);

    int fimArquivo = FALSE;
    int state = 0;
    void iniciaVetorPalavras();
    char caracter = proxCaracter();
    int origem,destino;


    while(fimArquivo == FALSE){
        switch(state){
            case 0:
                switch(caracter){
                    case '\n':
                        state = 1;
                        if (digrafo == TRUE) g = ListaAdjacencia((int)atoi(retornaVetorPalavras()),TRUE);
                        else g = ListaAdjacencia((int)atoi(retornaVetorPalavras()),FALSE);
                        reiniciaVetorPalavras();
                        caracter = proxCaracter();
                    break;
                    case EOF: fclose(arquivoEntrada); fimArquivo = TRUE;
					break;
                    default:
                        state = 0;
                        insereLetra(caracter);
                        caracter = proxCaracter();
                    break;
                }
            break;
            case 1:
                switch(caracter){
                    case ' ':
                        state = 2;
                        origem = (int)atoi(retornaVetorPalavras()) - 1;
                        reiniciaVetorPalavras();
                        caracter = proxCaracter();
                    break;
                    case EOF: fclose(arquivoEntrada); fimArquivo = TRUE;
					break;
                    default:
                        state = 1;
                        insereLetra(caracter);
                        caracter = proxCaracter();
                    break;
                }
            break;
            case 2:
                switch(caracter){
                    case '\n':
                        state = 1;
                        destino = (int)atoi(retornaVetorPalavras()) - 1;
                        reiniciaVetorPalavras();
                        caracter = proxCaracter();
                    break;
                    case ' ':
                        state = 3;
                        destino = (int)atoi(retornaVetorPalavras()) - 1;
                        reiniciaVetorPalavras();
                        caracter = proxCaracter();
					break;
                    case EOF:
                    	ListaAdjacenciaInsereAresta(g, origem, (int)atoi(retornaVetorPalavras()) - 1,1);
                        reiniciaVetorPalavras();
                        fclose(arquivoEntrada);
                        fimArquivo = TRUE;
                    break;
                    default:
                        state = 2;
                        insereLetra(caracter);
                        caracter = proxCaracter();
                    break;
                }
            break;
            case 3:
            	switch(caracter){
            		case '\n':
            			state = 1;
            			ListaAdjacenciaInsereAresta(g, origem, destino, (double)atof(retornaVetorPalavras()));
            			reiniciaVetorPalavras();
            			caracter = proxCaracter();
            		break;
            		case EOF:
            			ListaAdjacenciaInsereAresta(g, origem, destino, (double)atof(retornaVetorPalavras()));
                        reiniciaVetorPalavras();
                        fclose(arquivoEntrada);
                        fimArquivo = TRUE;
            		break;
            		default:
            			state = 3;
            			insereLetra(caracter);
            			caracter = proxCaracter();
            		break;
            	}
            break;

        }

    }
    return g;
}
