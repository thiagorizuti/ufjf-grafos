#include "ListaAdjacencia.h"

/******************ESTRUTURAS************************************/
typedef struct Adj_S{
    int vertice;
    double peso;
    struct Adj_S *prox;
}Adj;

struct Grafo_S{
    int vertices;
    int arestas;
    int digrafo;
    Adj  *listaAdj;
};

/******************VARI�VEIS*************************************/
int *visitados;

/********************IMPLEMENTA��ES******************************/
//Nome: ListaAdjacencia
//Fun��o: Inicializa par�metros e aloca mem�ria para uma estrutura de lista de adjac�ncia.
//Entrada: N�mero de v�rtices do grafo/digrafo, identifica��o grafo/digrafo
//Sa�da: Ponteiro para o endere�o de mem�ria da estrutura criada
GrafoListAdj* ListaAdjacencia(int numVertices, int digrafo){
    int i;
    GrafoListAdj *grafo = (GrafoListAdj*) malloc(sizeof(GrafoListAdj));
    grafo->vertices = numVertices;
    grafo->arestas = 0;
    grafo->digrafo = digrafo;

    grafo->listaAdj = (Adj*) malloc(sizeof(Adj) * numVertices);

    for (i=0;i<numVertices;i++){
        grafo->listaAdj[i].vertice = 0;
        grafo->listaAdj[i].prox = NULL;
    }

    return grafo;
}

//Nome: ListaAdjacenciaInsereAresta
//Fun��o: Insere aresta no grafo/digrafo.
//Entrada: Ponteiro para a estrutura do grafo/digrafo, n�s de origem e destino da aresta (no caso de digrafos), peso
//Sa�da: void
void ListaAdjacenciaInsereAresta(GrafoListAdj *grafo, int origem, int destino, double peso){
	Adj *n1 = malloc(sizeof(Adj));
	Adj *aux;
	n1->peso = peso;

	if (grafo->digrafo == TRUE){
		n1->vertice = destino;
		n1->prox = NULL;

		if(grafo->listaAdj[origem].prox == NULL){
			grafo->listaAdj[origem].prox = n1;
		}else{
			aux = grafo->listaAdj[origem].prox;
			while(aux->prox != NULL){
				aux = aux->prox;
			}
			aux->prox = n1;
		}
	}else{
		Adj *n2 = malloc(sizeof(Adj));
		n1->vertice = origem;
		n2->vertice = destino;
		n2->peso = peso;
		if(grafo->listaAdj[origem].prox == NULL){
			grafo->listaAdj[origem].prox = n2;
		}else{
			aux = grafo->listaAdj[origem].prox;
			while(aux->prox != NULL){
				aux = aux->prox;
			}
			aux->prox = n2;
		}

		if(grafo->listaAdj[destino].prox == NULL){
			grafo->listaAdj[destino].prox = n1;
		}else{
			aux = grafo->listaAdj[destino].prox;
			while(aux->prox != NULL){
				aux = aux->prox;
			}
			aux->prox = n1;
		}
	}
}

//Nome: ListaAdjacenciaRemoveAresta
//Fun��o: Remove aresta no grafo/digrafo.
//Entrada: Ponteiro para a estrutura do grafo/digrafo, n�s de origem e destino da aresta (no caso de digrafos)
//Sa�da: void
void ListaAdjacenciaRemoveAresta(GrafoListAdj *grafo, int origem, int destino){
	Adj *aux, *a;

	if (grafo->digrafo){
		aux = grafo->listaAdj[origem].prox;
		if (aux->vertice == destino) {
			free(aux);
			grafo->listaAdj[origem].prox = NULL;
		}else{
			while(aux->prox != NULL){
				if(aux->prox->vertice == destino){
					a = aux->prox;
					aux->prox = a->prox;
					free(a);
				}
			}
		}
	}else{
		aux = grafo->listaAdj[origem].prox;
		if (aux->vertice == destino) {
			a = aux;
			grafo->listaAdj[origem].prox = aux->prox;
			free(a);
		}else{
			while(aux->prox != NULL){
				if(aux->prox->vertice == destino){
					a = aux->prox;
					aux->prox = a->prox;
					free(a);
				}
			}
		}
		aux = grafo->listaAdj[destino].prox;
		if (aux->vertice == origem) {
			a = aux;
			grafo->listaAdj[destino].prox = aux->prox;
			free(a);
		}else{
			while(aux->prox != NULL){
				if(aux->prox->vertice == origem){
					a = aux->prox;
					aux->prox = a->prox;
					free(a);
				}
			}
		}
	}
}

//Nome: ListaAdjacenciaRetornaNumArest
//Fun��o: Retorna n�mero de v�rtices do grafo
//Entrada: Ponteiro para a estrutura do grafo/digrafo
//Sa�da: Inteiro - n�mero de v�rtices
int ListaAdjacenciaRetornaNumArest(GrafoListAdj *grafo){
	return grafo->arestas;
}

//Nome: ListaAdjacenciaRetornaNumVert
//Fun��o: Retorna n�mero de arestas do grafo
//Entrada: Ponteiro para a estrutura do grafo/digrafo
//Sa�da: Inteiro - n�mero de arestas
int ListaAdjacenciaRetornaNumVert(GrafoListAdj *grafo){
	return grafo->vertices;
}

//Nome: ListaAdjacenciaDelta
//Fun��o: Retorna operador Delta aplicado em grafos/digrafos G1 e G2.
//Entrada: Ponteiro para a estrutura de dois grafos/digrafos
//Sa�da: Grafo G3 = G1 delta G2
GrafoListAdj* ListaAdjacenciaDelta(GrafoListAdj *g1, GrafoListAdj *g2){
	GrafoListAdj *g3;
	int i,j;
	Adj *aux1, *aux2;
	int *marca = malloc(sizeof(int)*g1->vertices);


	for (i=0;i<g1->vertices;i++) marca[i] = 0;

	g3 = ListaAdjacencia(g1->vertices+g2->vertices,FALSE);

	for(i=0;i<g1->vertices;i++){
		aux1 = g1->listaAdj[i].prox;
		while (aux1 != NULL){
			marca[aux1->vertice] = 0;
			aux1 = aux1->prox;
		}
		aux1 = g3->listaAdj[i].prox;
		for(j=0;j<g1->vertices;j++){
			Adj *n = malloc(sizeof(Adj));
			if (marca[j] == 0) {
				n->vertice = j;
				aux1 = n;
				aux1 = aux1->prox;
			}
		}
	}

	for(i=0;i<g2->vertices;i++){
		aux1 = g2->listaAdj[i].prox;
		while (aux1 != NULL){
			marca[aux1->vertice] = 0;
			aux1 = aux1->prox;
		}
		aux1 = g3->listaAdj[g1->vertices+i].prox;
		for(j=0;j<g1->vertices;j++){
			Adj *n = malloc(sizeof(Adj));
			if (marca[j] == 0) {
				n->vertice = j;
				aux1 = n;
				aux1 = aux1->prox;
			}
		}
	}




	free(marca);
	return g3;
}

//Nome: ListaAdjacenciaImprime
//Fun��o: Imprime em arquivo a estrutura de um grafo/digrafo
//Entrada: Ponteiro para o arquivo de sa�da, Ponteiro para a estrutura de dois grafos/digrafos
//Sa�da: void
void ListaAdjacenciaImprime(GrafoListAdj *g){
	int i;
	Adj *aux;

	for(i=0;i<g->vertices;i++){
		aux = g->listaAdj[i].prox;
		printf("%d", i+1);
		while (aux != NULL){
			printf("->%d", aux->vertice+1);
			aux = aux->prox;
		}
		printf("\n");
	}
}

//Nome: ListaAdjacenciaBuscaProfund
//Fun��o: Realiza uma busca em profundidade em um grafo a partir de um n�, para descobrir se � conexo
//Entrada: Ponteiro para a estrutura de um grafo, n� inicial
//Sa�da: Retorna TRUE se o grafo � conexo e FALSE caso contr�rio
int ListaAdjacenciaBuscaProfund(GrafoListAdj *grafo, int valor){
	Adj *aux;
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
	    if (grafo->listaAdj[no].prox != NULL){
	    	aux = grafo->listaAdj[no].prox;
			while(aux != NULL){
				if(visitados[aux->vertice] == 0){
					empilha(p, aux->vertice);
				}
				aux = aux->prox;
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

//Nome: ListaAdjacenciaPonte
//Fun��o: Imprime todos as arestas (par de n�s) que s�o ponte em um grafp
//Entrada: Ponteiro para a estrutura de um grafo
//Sa�da: Void
void ListaAdjacenciaPonte(GrafoListAdj *g){
	int i;
	Adj *aux;


}
