#include <stdlib.h>
#include <stdio.h>

#include "TADPilha.h"



struct no {
    int info;
    struct no *prox;
};

struct pilha {
    struct no *topo;
};


Pilha* cria(){
    Pilha *p;

    p = (Pilha*) malloc(sizeof(Pilha));
    p->topo = NULL;

    return p;
}

int vazia (Pilha *p){
    return p->topo == NULL;
}

void empilha (Pilha *p, int v){
    No *aux;
    aux = (No*) malloc(sizeof(No));
    aux->info = v;
    aux->prox = p->topo;
    p->topo = aux;

}

int desempilha(Pilha *p){
    int v;
    No *aux;

    if (vazia(p))return -1;

    v = p->topo->info;
    aux = p->topo;
    p->topo = aux->prox;

    free(aux);

    return v;
}
int swap(Pilha *p, int v){
    No *aux;

    aux = p->topo;
    while (aux->prox != NULL){
        if (aux->info == v) return 1;
        aux = aux->prox;
    }

    return 0;
}

void destroi(Pilha *p){
	free(p);
}

