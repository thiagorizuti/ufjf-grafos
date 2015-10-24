/*
 * MatrizAdjacencia.c
 *
 *  Created on: 07/12/2013
 *      Author: SAA
 */

#include "MatrizAdjacencia.h"
#include <limits.h>
#include <time.h>
#include <math.h>

/******************ESTRUTURAS************************************/
struct GrafoAdj_S{
	int vertices;
	int arestas;
	int digrafo;
	float **matrizAdj;
};


/******************VARI�VEIS*************************************/
int *visitados;
int *indices;

/********************IMPLEMENTA��ES******************************/
//Nome: MatrizAdjacencia
//Fun��o: Inicializa par�metros e aloca mem�ria para uma estrutura de matriz de adjac�ncia.
//Entrada: N�mero de v�rtices do grafo/digrafo, identifica��o grafo/digrafo
//Sa�da: Ponteiro para o endere�o de mem�ria da estrutura criada
GrafoAdj* MatrizAdjacencia(int vertices, int digrafo){
    int i, j;
    GrafoAdj *grafo = (GrafoAdj*) malloc(sizeof(GrafoAdj));

    grafo->arestas = 0;
    grafo->vertices = vertices;
    if (digrafo == TRUE) grafo->digrafo = TRUE;
    else grafo->digrafo = FALSE;

    grafo->matrizAdj = malloc(vertices * sizeof(float*));

    for (i = 0;i < vertices;i++)
        grafo->matrizAdj[i] = malloc(vertices * sizeof(float));
    for (i = 0;i < vertices;i++)
        for (j = 0;j < vertices; j++)
            grafo->matrizAdj[i][j] = 0;

    return grafo;
}

//Nome: MatrizAdjacenciaInsereAresta
//Fun��o: Insere aresta no grafo/digrafo.
//Entrada: Ponteiro para a estrutura do grafo/digrafo, n�s de origem e destino da aresta (no caso de digrafos), peso
//Sa�da: void
void MatrizAdjacenciaInsereAresta(GrafoAdj *grafo, int origem, int destino, double peso){
	if (grafo->digrafo == TRUE){
		grafo->matrizAdj[origem][destino] = peso;
	}else{
			grafo->matrizAdj[destino][origem] = peso;
			grafo->matrizAdj[origem][destino] = peso;
	}
}

//Nome: MatrizAdjacenciaRemoveAresta
//Fun��o: Remove aresta no grafo/digrafo.
//Entrada: Ponteiro para a estrutura do grafo/digrafo, n�s de origem e destino da aresta (no caso de digrafos)
//Sa�da: void
void MatrizAdjacenciaRemoveAresta(GrafoAdj *grafo, int origem, int destino){
	if (grafo->digrafo == TRUE){
		grafo->matrizAdj[origem][destino] = 0;
	}else{
			grafo->matrizAdj[destino][origem] = 0;
			grafo->matrizAdj[origem][destino] = 0;
	}
}

//Nome: MatrizAdjacenciaRemoveNo
//Fun��o: Remove aresta no grafo/digrafo.
//Entrada: Ponteiro para a estrutura do grafo/digrafo, n�s de origem e destino da aresta (no caso de digrafos)
//Sa�da: void
GrafoAdj* MatrizAdjacenciaRemoveNo(GrafoAdj *grafo, int no){
	int i,j;
	GrafoAdj *g;
	g = MatrizAdjacencia(grafo->vertices-1,grafo->digrafo);
	g->arestas = 0;

	for (i = 0;i<g->vertices;i++){
    		for (j = 0;j<g->vertices; j++){
    			if (j >= no){
    				g->matrizAdj[i][j] = grafo->matrizAdj[i][j+1];
    			}else{
    				g->matrizAdj[i][j] = grafo->matrizAdj[i][j];
    			}
        }
    }

    for (j = 0;j<g->vertices;j++){
    		for (i = 0;i<g->vertices; i++){
    			if (i >= no){
    				g->matrizAdj[i][j] = grafo->matrizAdj[i+1][j];
    			}else{
    				g->matrizAdj[i][j] = grafo->matrizAdj[i][j];
    			}
        }
    }

    return g;
}

//Nome: MatrizAdjacenciaApagaGrafo
//Fun��o: Apaga estrutura de um grafo/digrafo da mem�ria
//Entrada: Ponteiro para a estrutura do grafo/digrafo
//Sa�da: void)
void MatrizAdjacenciaApagaGrafo(GrafoAdj *g){
	int i;
	for (i=0;i<g->vertices;i++){
		free(g->matrizAdj[i]);
	}
	free(g->matrizAdj);
	free(g);
}


//Nome: MatrizAdjacenciaRetornaNumVert
//Fun��o: Retorna n�mero de v�rtices do grafo
//Entrada: Ponteiro para a estrutura do grafo/digrafo
//Sa�da: Inteiro - n�mero de v�rtices
int MatrizAdjacenciaRetornaNumVert(GrafoAdj *grafo){
    return grafo->vertices;
}

//Nome: MatrizAdjacenciaRetornaNumArest
//Fun��o: Retorna n�mero de arestas do grafo
//Entrada: Ponteiro para a estrutura do grafo/digrafo
//Sa�da: Inteiro - n�mero de arestas
int MatrizAdjacenciaRetornaNumArest(GrafoAdj *grafo){
    return grafo->arestas;
}

//Nome: MatrizAdjacenciaDelta
//Fun��o: Retorna operador Delta aplicado em grafos/digrafos G1 e G2.
//Entrada: Ponteiro para a estrutura de dois grafos/digrafos
//Sa�da: Grafo G3 = G1 delta G2
GrafoAdj* MatrizAdjacenciaDelta(GrafoAdj *g1, GrafoAdj *g2){
	GrafoAdj *g3;
	int i, j;
	g3 = MatrizAdjacencia(g1->vertices+g2->vertices,FALSE);

	for (i=0;i<g1->vertices;i++){
		for (j=0;j<g1->vertices;j++){
			if (g1->matrizAdj[i][j] != 0) g3->matrizAdj[i][j] = 0;
			else g3->matrizAdj[i][j] = 1;
		}
	}

	for (i=(g1->vertices);i<g1->vertices+g2->vertices;i++){
		for (j=0;j<g1->vertices+g2->vertices;j++){
			if (g2->matrizAdj[i][j] != 0) g3->matrizAdj[i+g1->vertices][j+g1->vertices] = 0;
			else g3->matrizAdj[i+g1->vertices][j+g1->vertices] = 1;
		}
	}
	return g3;
}

//Nome: MatrizAdjacenciaImprime
//Fun��o: Imprime em arquivo a estrutura de um grafo/digrafo
//Entrada: Ponteiro para o arquivo de sa�da, Ponteiro para a estrutura de dois grafos/digrafos
//Sa�da: void
void MatrizAdjacenciaImprime(GrafoAdj *g){
	int i,j;

	for (i=0;i<g->vertices;i++){
		for (j=0;j<g->vertices;j++){
			printf("|%2.1f| ",g->matrizAdj[i][j]);
		}
		printf("\n");
	}
}

//Nome: MatrizAdjacenciaBuscaProfund
//Fun��o: Realiza uma busca em profundidade em um grafo a partir de um n�, para descobrir se � conexo
//Entrada: Ponteiro para a estrutura de um grafo, n� inicial
//Sa�da: Retorna TRUE se o grafo � conexo e FALSE caso contr�rio
int MatrizAdjacenciaBuscaProfund(GrafoAdj *grafo, int valor){
    int marca = 1;
    int i, no;
    int compConex = FALSE;
    Pilha *p = cria();
    visitados = (int*) malloc(sizeof(int) * grafo->vertices);
    for (i = 0; i < grafo->vertices; i++) visitados[i] = 0;

    visitados[valor-1] = marca;
    empilha(p, valor-1);

    //while (compConex == TRUE){
        while (!vazia(p)){
            no = desempilha(p);
            visitados[no] = marca;
            for (i = 0; i < grafo->vertices; i++){
                if (grafo->matrizAdj[no][i] != 0){
                    if(visitados[i] == 0)
                        empilha(p, i);
                }
            }
        }
        compConex = TRUE;
        //marca++;
        for (i = 0; i < grafo->vertices; i++){
            if (visitados[i] == 0) {
                compConex = FALSE;
                break;
            }
        }
        //if (compConex == TRUE) empilha(p, i);
    //}
    free(visitados);
    destroi(p);
    return compConex;
}

//Nome: MatrizAdjacenciaPonte
//Fun��o: Imprime todos as arestas (par de n�s) que s�o ponte em um grafp
//Entrada: Ponteiro para a estrutura de um grafo
//Sa�da: Void
void MatrizAdjacenciaPonte(GrafoAdj *g){
	int i, j,conexo;
	float aux;
	printf("Arestas Ponte:\n");

	for(i=0;i<g->vertices;i++){
		for(j=i+1;j<g->vertices;j++){
			if (g->matrizAdj[i][j] >= 0){
				aux = g->matrizAdj[i][j];
				MatrizAdjacenciaRemoveAresta(g,i,j);
				conexo = MatrizAdjacenciaBuscaProfund(g,1);
				if (conexo == FALSE)printf("(%d,%d)\n",i+1,j+1);
				MatrizAdjacenciaInsereAresta(g,i,j,aux);
			}
		}
	}
}

//Nome: MatrizAdjacenciaArticulacao
//Fun��o: Imprime todos as arestas (par de n�s) que s�o ponte em um grafp
//Entrada: Ponteiro para a estrutura de um grafo
//Sa�da: Void
void MatrizAdjacenciaArticulacao(GrafoAdj *g){
	int i,conexo;
	GrafoAdj *grafo;
	printf("V�rtices de Articula��o:\n");

	for(i=0;i<g->vertices;i++){
		grafo = MatrizAdjacenciaRemoveNo(g,i);
		conexo = MatrizAdjacenciaBuscaProfund(grafo,1);
		if(conexo == FALSE)printf("%d\n",i+1);
	}
}

void quickSort(int valor[], int esquerda, int direita){
    int i, j, x, y, aux;
    i = esquerda;
    j = direita;
    x = valor[(esquerda + direita) / 2];

    while(i <= j){
        while(valor[i] > x && i < direita){
            i++;
        }
        while(valor[j] < x && j > esquerda){
            j--;
        }
        if(i <= j){
            y = valor[i];
			aux = indices[i];
            valor[i] = valor[j];
			indices[i] = indices[j];
            valor[j] = y;
			indices[j] = aux;
            i++;
            j--;
        }
    }
    if(j > esquerda)
        quickSort(valor, esquerda, j);
    if(i < direita)
        quickSort(valor,  i, direita);

}

void MatrizAdjacenciaImprimeAlocacao(GrafoAdj *g, int clusters){
	int i, j;
	int numUsers = g->vertices-clusters;


	for(i=0;i<clusters;i++){
		printf("Cluster %d: ",i+1);
		for(j=0;j<numUsers;j++){
			if(g->matrizAdj[i][j+clusters] > 0) printf("%d ",j+1);
		}
		printf("\n");
	}
}

float MatrizAdjacenciaFuncaoObjetivo(GrafoAdj *g, int clusters){
	float valor = 0, soma;
	int i, j, cont;
	int numUsers = g->vertices-clusters;


	for(i=0;i<clusters;i++){
		cont = 0;
		soma = 0;
		for(j=0;j<numUsers;j++){
			if(g->matrizAdj[i][j+clusters] > 0){
				cont++;
				soma = soma + g->matrizAdj[i][j+clusters];
			}
		}
		if(cont == 0) cont = 1;
		valor = valor + (soma/cont);
	}

	return valor;
}



//Nome: rnd
//Fun��o: Gerar randomicamente um  inteiro entre 0 e um "range" - 1
//Entrada: Inteiro para ajustar os valores gerados
//Sa�da: Inteiro aleat�rio
int rnd(int range) {
    if(range==0){
        return range;
    }
    return (rand() % range);
  }

//Nome: MatrizAdjacenciaHeuristica1
//Fun��o: Heur�stica gulosa de emparelhamento que ordena Clusters pela soma dos SNR de seus usu�rios,
//escolhe o maior e aloca um dos usu�rios que tenha os melhore SNRs nele de acordo com um fator de randomiza��o
//Entrada: Ponteiro para a estrutura de um grafo, n�mero de clusters, fator de randomiza��o
//Sa�da: Ponteiro para um estrutura de gafo emparelhado incompleto sub-otimo
GrafoAdj* MatrizAdjacenciaHeuristica1(GrafoAdj *g, int clusters, float alfa){
	int i, j, bestCluster, randUser, escolhido;
	float **matriz, somaClusters, somaFinal;
	int cont = 0;
	int numUsers = g->vertices-clusters;
    float ordenado[numUsers];
    int eleitos[numUsers];

    //criando grafo de saida
    GrafoAdj *saida;
    saida = MatrizAdjacencia(g->vertices, 0);

    //alocando vetor de indices
    indices = malloc(numUsers * sizeof(int));
    for (i=0;i<clusters;i++)
        indices[i] = i;


    //alocando matriz clustersXUsu�rios para ordena��o
    matriz = malloc(clusters * sizeof(float*));
    for (i=0;i<clusters;i++)
        matriz[i] = malloc(numUsers * sizeof(float));

    //preenchendo matriz com SNRs para ordena��o
    for (i=0;i<clusters;i++){
        for(j=0;j<numUsers;j++){
            matriz[i][j] = g->matrizAdj[i][j+clusters];
        }
    }

    //preenchendo vetor que indica os candidatos que j� foram escolhidos ou n�o
    for (i=0;i<numUsers;i++){
            eleitos[i]=0;
    }

    //ranqueando valores de clusters
    while(cont < numUsers){
        somaFinal = 0;
        for (i=0;i<clusters;i++){
            for(j=0;j<numUsers;j++){
                somaClusters = matriz[i][j] + somaClusters;
            }
            if (somaClusters > somaFinal){
                somaFinal = somaClusters;
                bestCluster = i;
            }
            somaClusters = 0;
        }

        //ordenando matriz de SNR e tabela de indices
        for (i=0;i<numUsers;i++) indices[i] = i;
        for (i=0;i<numUsers;i++) ordenado[i] = matriz[bestCluster][i];
        quickSort(ordenado, 0, numUsers-1);

        escolhido = 0;

        //escolhendo randomicamente um usu�rio para o cluster setado
        while(escolhido == 0){
            randUser=rnd(numUsers*alfa);
            if(eleitos[indices[randUser]] == 0){
                saida->matrizAdj[bestCluster][indices[randUser]+clusters] = ordenado[randUser];
                for (j=0;j<clusters;j++) matriz[j][indices[randUser]] = 0;
                eleitos[indices[randUser]] = 1;
                escolhido = 1;
            }
        }


        cont++;
    }

	return saida;
}

//Nome: MatrizAdjacenciaHeuristica2
//Fun��o: Heur�stica gulosa de emparelhamento que escolhe o usu�rio que tiver a maior diferen�a entre seus SNRs nos clusters
//e o aloca em um dos clusters onde esse usu�rio tem os maiores SNRs de acordo com um fator de randomiza��o
//Entrada: Ponteiro para a estrutura de um grafo, n�mero de clusters, fator de randomiza��o
//Sa�da: Ponteiro para um estrutura de gafo emparelhado incompleto sub-otimo
GrafoAdj* MatrizAdjacenciaHeuristica2(GrafoAdj *g, int clusters, float alfa){
	int  i, j, indice, indCluster, aux, flag, randCluster;
	float **matriz, maiorSNR, menorSNR, maiorDif;
	int cont = 0;
	int numUsers = g->vertices-clusters;
	float cluster[numUsers];
	float dif[numUsers];

    //criando grafo de saida
    GrafoAdj *saida;
    saida = MatrizAdjacencia(g->vertices, 0);

    //alocando vetor de indices
    indices = malloc(numUsers * sizeof(int));
    for (i=0;i<clusters;i++)
        indices[i] = i;


    //alocando matriz clustersXUsu�rios para ordena��o
    matriz = malloc(clusters * sizeof(float*));
    for (i=0;i<clusters;i++)
        matriz[i] = malloc(numUsers * sizeof(float));

    //preenchendo matriz com SNRs para ordena��o
    for (i=0;i<clusters;i++){
        for(j=0;j<numUsers;j++){
            matriz[i][j] = g->matrizAdj[i][j+clusters];
        }
    }

    while(cont < numUsers){
        //ordenando usuarios pela maior diferen�a de SNR
        maiorDif=0;
        for(i=0;i<numUsers;i++){
            maiorSNR = 0;
            menorSNR = 888888;
            flag = 0;
            for (j=0;j<clusters;j++){
                if(matriz[j][i] > maiorSNR){
                    maiorSNR = matriz[j][i];
                    aux = j;

                }
                if(matriz[j][i] < menorSNR && matriz[j][i] != 0){
                    menorSNR = matriz[j][i];
                    flag = 1;
                }
            }
            if (flag == 0) menorSNR = 0;
            if ((maiorSNR - menorSNR) > maiorDif){
				maiorDif = maiorSNR - menorSNR;
				indice = i;
				indCluster = aux;

			}
        }

		//ordenando clusters e tabela de indices
        for (i=0;i<clusters;i++) indices[i] = i;
        for (i=0;i<clusters;i++) cluster[i] = matriz[i][indice];
        quickSort(cluster, 0, clusters-1);

        //escolhendoo cluster para o usuario
        randCluster=rnd(clusters*alfa);
        indCluster=indices[randCluster];

        saida->matrizAdj[indCluster][clusters+indice] = matriz[indCluster][indice];
        for(i=0;i<clusters;i++) matriz[i][indice] = 0;

        cont++;
    }

	return saida;
}

//Nome: MatrizAdjacenciaHeuristica1Gulosa
//Fun��o: Usa a Heuristica 1 com um fator de randomiza��o 0
//e calcula a fun��o objetivo
//Entrada: Ponteiro para a estrutura de um grafo, n�mero de clusters
//Sa�da: Resultado da fun��o objetivo
float MatrizAdjacenciaHeuristica1Gulosa(GrafoAdj *g, int clusters){

    //criando grafo de saida
    GrafoAdj *saida;
    saida = MatrizAdjacencia(g->vertices,0);

    //chama a heuristica 1
    saida = MatrizAdjacenciaHeuristica1(g,clusters,0);

    //retorna o resultado
    return MatrizAdjacenciaFuncaoObjetivo(saida,clusters);


}

//Nome: MatrizAdjacenciaHeuristica2Gulosa
//Fun��o: Usa a Heuristica 2 com um fator de randomiza��o 0
//e calcula a fun��o objetivo
//Entrada: Ponteiro para a estrutura de um grafo, n�mero de clusters
//Sa�da: Resultado da fun��o objetivo
float MatrizAdjacenciaHeuristica2Gulosa(GrafoAdj *g, int clusters){

	//criando grafo de saida
    GrafoAdj *saida;
    saida = MatrizAdjacencia(g->vertices, 0);

    //chama a heuristica 2
    saida = MatrizAdjacenciaHeuristica2(g,clusters,0);

    //retorna o resultado
	return MatrizAdjacenciaFuncaoObjetivo(saida,clusters);
}

//Nome: MatrizAdjacenciaHeuristica1Rand
//Fun��o: Itera 1000 vezes, aplicando a Heuristica 1 com um fator de randomiza��o alfa
//e calcula a fun��o objetivo
//Entrada: Ponteiro para a estrutura de um grafo, n�mero de clusters, fator de randomiza��o
//Sa�da: Melhor resultado nas 1000 itre��es
float MatrizAdjacenciaHeuristica1Rand(GrafoAdj *g, int clusters, float alfa){
	int i;
	float melhorResultado = 0;

	//criando grafo de saida
    GrafoAdj *saida;
    saida = MatrizAdjacencia(g->vertices, 0);

    for(i=0;i<500;i++){
        //chama a heuristica 1
        saida = MatrizAdjacenciaHeuristica1(g,clusters,alfa);

        //atualiza o melhor resultado
        if (MatrizAdjacenciaFuncaoObjetivo(saida,clusters) > melhorResultado){
            melhorResultado = MatrizAdjacenciaFuncaoObjetivo(saida,clusters);
        }
    }

	return melhorResultado;
}

//Nome: MatrizAdjacenciaHeuristica2Rand
//Fun��o: Itera 1000 vezes, aplicando a Heuristica 2 com um fator de randomiza��o alfa
//e calcula a fun��o objetivo
//Entrada: Ponteiro para a estrutura de um grafo, n�mero de clusters, fator de randomiza��o
//Sa�da: Melhor resultado nas 1000 itre��es
float MatrizAdjacenciaHeuristica2Rand(GrafoAdj *g, int clusters, float alfa){
	int i;
	float melhorResultado = 0;

	//criando grafo de saida
    GrafoAdj *saida;
    saida = MatrizAdjacencia(g->vertices, 0);

    for(i=0;i<500;i++){
        //chama a heuristica 2
        saida = MatrizAdjacenciaHeuristica2(g,clusters,alfa);

        //atualiza o melhor resultado
        if (MatrizAdjacenciaFuncaoObjetivo(saida,clusters) > melhorResultado){
            melhorResultado = MatrizAdjacenciaFuncaoObjetivo(saida,clusters);
        }
    }

	return melhorResultado;
}


//Nome: MatrizAdjacenciaHeuristica1RandReativa
//Fun��o: Com v�rios alfas, calcular o resultado da fun��o objetivo para a Heuristica 1 e descobrir
//qual o melhor alfa
//Entrada: Ponteiro para a estrutura de um grafo, n�mero de clusters, vetor de alfas, quantidade de alfas
//Sa�da: Melhor alfa
float MatrizAdjacenciaHeuristica1RandReativa(GrafoAdj *g, int clusters, float *alfas, int quantAlfa){
	int i,j, cont, alfa, bestAlfa, probRand;
	int iteracoes[quantAlfa];
	float probSoma, result;
	float results[quantAlfa], media[quantAlfa], prob[quantAlfa], q[quantAlfa];
	float bestResult = 0;
    float somaq = 0;

    //criando grafo de saida
    GrafoAdj *saida;
    saida = MatrizAdjacencia(g->vertices, 0);

     //inicializando o vetor de resultados e de itera��es
     for(i=0;i<quantAlfa;i++){
            results[i]=0;
            iteracoes[i]=0;
     }

    //populando os vetores
    for (i=0;i<quantAlfa;i++){
        for(j=0;j<10;j++){
                saida = MatrizAdjacenciaHeuristica1(g, clusters, alfas[i]);
                result = MatrizAdjacenciaFuncaoObjetivo(saida, clusters);
                results[i] = results[i]  + result;
                iteracoes[i] = iteracoes[i] + 1;
                if(result > bestResult){
                    bestResult = result;
                    bestAlfa = i;
                }
        }
        media[i] = results[i]/iteracoes[i];
    }
    //calculando as probabilidades e decidindo o alfa pela primeira vez
    for(i=0;i<quantAlfa;i++){
            q[i] = pow(bestResult/media[i],10);
            somaq = somaq + q[i];
    }
    for(i=0;i<quantAlfa;i++){
            prob[i]=q[i]/somaq;
    }
    probSoma = 0;
    probRand = rnd(101);
    cont = 0;
    while(probSoma <= probRand && cont < quantAlfa){
        probSoma = probSoma + prob[cont]*100;
        cont++;
    }
    alfa=cont-1;

    //a cada itera��o, calcula as probabilidades e decide o melhor alfa para a proxima itera��o
    for (i=0;i<1000;i++){
        saida = MatrizAdjacenciaHeuristica1(g, clusters, alfas[alfa]);
        result = MatrizAdjacenciaFuncaoObjetivo(saida, clusters);
        results[alfa] = results[alfa] + result;
        iteracoes[alfa] = iteracoes[alfa] + 1;
        media[alfa] = results[alfa]/iteracoes[alfa]+1;
        if(result > bestResult){
            bestResult = result;
            bestAlfa = alfa;
        }
        for(j=0;j<quantAlfa;j++){
                q[j] = pow(bestResult/media[j],10);
                somaq = somaq + q[j];
        }
        for(j=0;j<quantAlfa;j++){
                prob[j]=q[j]/somaq;
        }
        probSoma = 0;
        probRand = rnd(101);
        cont = 0;
        while(probSoma <= probRand && cont < quantAlfa){
            probSoma = probSoma + prob[cont]*100;
            cont++;
        }
        alfa=cont-1;

   }

   printf("Melhor Resultado: %2.1f", bestResult);
   return alfas[bestAlfa];
}


//Nome: MatrizAdjacenciaHeuristica2RandReativa
//Fun��o: Com v�rios alfas, calcular o resultado da fun��o objetivo para a Heuristica 2 e descobrir
//qual o melhor alfa
//Entrada: Ponteiro para a estrutura de um grafo, n�mero de clusters, vetor de alfas, quantidade de alfas
//Sa�da: Melhor alfa
float MatrizAdjacenciaHeuristica2RandReativa(GrafoAdj *g, int clusters, float *alfas, int quantAlfa){
	int i,j, cont, alfa, bestAlfa, probRand;
	int iteracoes[quantAlfa];
	float probSoma, result;
	float results[quantAlfa], media[quantAlfa], prob[quantAlfa], q[quantAlfa];
	float bestResult = 0;
    float somaq = 0;

    //criando grafo de saida
    GrafoAdj *saida;
    saida = MatrizAdjacencia(g->vertices, 0);

     //inicializando o vetor de resultados e de itera��es
     for(i=0;i<quantAlfa;i++){
            results[i]=0;
            iteracoes[i]=0;
     }

    //populando os vetores
    for (i=0;i<quantAlfa;i++){
        for(j=0;j<10;j++){
                saida = MatrizAdjacenciaHeuristica2(g, clusters, alfas[i]);
                result = MatrizAdjacenciaFuncaoObjetivo(saida, clusters);
                results[i] = results[i]  + result;
                iteracoes[i] = iteracoes[i] + 1;
                if(result > bestResult){
                    bestResult = result;
                    bestAlfa = i;
                }
        }
        media[i] = results[i]/iteracoes[i];
    }
    //calculando as probabilidades e decidindo o alfa pela primeira vez
    for(i=0;i<quantAlfa;i++){
            q[i] = pow(bestResult/media[i],10);
            somaq = somaq + q[i];
    }
    for(i=0;i<quantAlfa;i++){
            prob[i]=q[i]/somaq;
    }
    probSoma = 0;
    probRand = rnd(101);
    cont = 0;
    while(probSoma <= probRand && cont < quantAlfa){
        probSoma = probSoma + prob[cont]*100;
        cont++;
    }
    alfa=cont-1;

    //a cada itera��o, calcula as probabilidades e decide o melhor alfa para a proxima itera��o
    for (i=0;i<1000;i++){
        saida = MatrizAdjacenciaHeuristica2(g, clusters, alfas[alfa]);
        result = MatrizAdjacenciaFuncaoObjetivo(saida, clusters);
        results[alfa] = results[alfa] + result;
        iteracoes[alfa] = iteracoes[alfa] + 1;
        media[alfa] = results[alfa]/iteracoes[alfa]+1;
        if(result > bestResult){
            bestResult = result;
            bestAlfa = alfa;
        }
        for(j=0;j<quantAlfa;j++){
                q[j] = pow(bestResult/media[j],10);
                somaq = somaq + q[j];
        }
        for(j=0;j<quantAlfa;j++){
                prob[j]=q[j]/somaq;
        }
        probSoma = 0;
        probRand = rnd(101);
        cont = 0;
        while(probSoma <= probRand && cont < quantAlfa){
            probSoma = probSoma + prob[cont]*100;
            cont++;
        }
        alfa=cont-1;

   }

   printf("Melhor Resultado: %2.1f", bestResult);
   return alfas[bestAlfa];
}


