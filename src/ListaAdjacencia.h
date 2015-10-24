#ifndef LISTAADJACENCIA_H_INCLUDED
#define LISTAADJACENCIA_H_INCLUDED


#include <stdlib.h>
#include <stdio.h>
#include "TADPilha.h"


#define FALSE	0
#define TRUE	1

/**-----------------------ESTRUTURAS----------------------------------*/
typedef struct Grafo_S GrafoListAdj;


/**-----------------------PROTÓTIPOS----------------------------------*/
GrafoListAdj* ListaAdjacencia(int numVertices, int digrafo);
void ListaAdjacenciaInsereAresta(GrafoListAdj *grafo, int origem, int destino, double peso);
int ListaAdjacenciaRetornaNumArest(GrafoListAdj *grafo);
int ListaAdjacenciaRetornaNumVert(GrafoListAdj *grafo);
GrafoListAdj* ListaMatrizAdjacenciaDelta(GrafoListAdj *g1, GrafoListAdj *g2);
void ListaAdjacenciaImprime (GrafoListAdj *g);
int ListaAdjacenciaBuscaProfund(GrafoListAdj *grafo, int valor);
void ListaAdjacenciaPonte(GrafoListAdj *g);


#endif // LISTAADJACENCIA_H_INCLUDED
