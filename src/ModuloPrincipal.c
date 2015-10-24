/*
 ============================================================================
 Name        : Grafos2013.c
 Author      : Luã Siveira
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "MatrizAdjacencia.h"
#include "ConstrutorGrafo.h"
#include "ListaAdjacencia.h"
#include <time.h>
#include <math.h>

#define TRUE	1
#define FALSE	0

int main(void) {
	FILE *arquivoEntrada, *arquivoSaida;
	char *entrada = "sistemaPLC_40";
	char *saida = "Saida";
	arquivoEntrada = fopen(entrada, "r");
	arquivoSaida = fopen(saida, "w");
	if (arquivoEntrada == NULL){
		printf("Arquivo de entrada não pôde ser aberto");
		exit(1);
	}

	GrafoAdj *g, *k;
	int i, alfa,j;
	float r;
	float alfas[10]={0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1};
	int quantAlfas = 10;

    srand((unsigned)time(NULL));

	g = IniMatrizAdj(arquivoEntrada,0);
	//MatrizAdjacenciaImprime(g);
    r = MatrizAdjacenciaHeuristica1RandReativa(g,5,alfas,10);
    printf("\nMelhor Alpha: %4.1f\n",r);
	//MatrizAdjacenciaImprime(k);

//	float melhorResult = 0;
//	float variancia = 0, valores[10], media = 0;
//	for (i=0;i<10;i++){
//		valores[i] = MatrizAdjacenciaHeuristica2Rand(g, 5, 0.8);
//		media = media + valores[i];
//		if (valores[i] > melhorResult){
//			melhorResult = valores[i];
//		}
//	}
//
//	media = media/10;
//	printf("Melhor Resultado: %4.1f\n", melhorResult);
//	printf("Média: %4.1f\n", media);
//
//	for (i=0;i<10;i++){
//		variancia = variancia + pow((valores[i] - media),2);
//	}
//
//	variancia = variancia/10;
//	printf("Desvio Padrão: %3.2f\n", sqrt(variancia));


	close(arquivoEntrada);
	close(arquivoSaida);

	return 1;
}
