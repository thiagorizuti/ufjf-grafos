#ifndef TADPILHA_H_INCLUDED
#define TADPILHA_H_INCLUDED

typedef struct pilha Pilha;
typedef struct no No;

Pilha* cria();
int vazia (Pilha *p);
void empilha (Pilha *p, int v);
int desempilha(Pilha *p);
int swap(Pilha *p, int v);
void destroi(Pilha *p);

#endif // TADPILHA_H_INCLUDED
