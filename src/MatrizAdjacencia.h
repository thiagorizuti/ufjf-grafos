#ifndef MATRIZADJACENCIA_H_INCLUDED
#define MATRIZADJACENCIA_H_INCLUDED


#include <stdlib.h>
#include <stdio.h>
#include "TADPilha.h"


#define FALSE	0
#define TRUE	1


/**-----------------------ESTRUTURAS----------------------------------*/

typedef struct GrafoAdj_S GrafoAdj;


/**-----------------------PROTÓTIPOS----------------------------------*/

GrafoAdj* MatrizAdjacencia(int vertices, int digrafo);
void MatrizAdjacenciaInsereAresta(GrafoAdj *grafo, int origem, int destino, double peso);
void MatrizAdjacenciaRemoveAresta(GrafoAdj *grafo, int origem, int destino);
int MatrizAdjacenciaRetornaNumArest(GrafoAdj *grafo);
int MatrizAdjacenciaRetornaNumVert(GrafoAdj *grafo);
GrafoAdj* MatrizAdjacenciaDelta(GrafoAdj *g1, GrafoAdj *g2);
void MatrizAdjacenciaImprime(GrafoAdj *g);
int MatrizAdjacenciaBuscaProfund(GrafoAdj *grafo, int valor);
void MatrizAdjacenciaPonte(GrafoAdj *g);
void MatrizAdjacenciaApagaGrafo(GrafoAdj *g);
GrafoAdj* MatrizAdjacenciaRemoveNo(GrafoAdj *grafo, int no);
void MatrizAdjacenciaArticulacao(GrafoAdj *g);
float MatrizAdjacenciaFuncaoObjetivo(GrafoAdj *g, int clusters);
int rnd(int range);
GrafoAdj* MatrizAdjacenciaHeuristica1(GrafoAdj *g, int clusters, float alfa);
GrafoAdj* MatrizAdjacenciaHeuristica2(GrafoAdj *g, int clusters, float alfa);
float MatrizAdjacenciaHeuristica1Gulosa(GrafoAdj *g, int clusters);
float MatrizAdjacenciaHeuristica2Gulosa(GrafoAdj *g, int clusters);
float MatrizAdjacenciaHeuristica1Rand(GrafoAdj *g, int clusters, float alfa);
float MatrizAdjacenciaHeuristica2Rand(GrafoAdj *g, int clusters, float alfa);
float MatrizAdjacenciaHeuristica1RandReativa(GrafoAdj *g, int clusters, float *alfas, int quantAlfa);
float MatrizAdjacenciaHeuristica2RandReativa(GrafoAdj *g, int clusters, float *alfas, int quantAlfa);


#endif // MATRIZADJACENCIA_H_INCLUDED
