#ifndef LISTA
#define LISTA

#include <stdio.h>
#include <stdlib.h>

typedef struct Point
{
    int x;
    int y;
} Ponto;

typedef struct Spot
{
    int valor;
    Ponto p;
    double f;
    double g;
    double h;
    struct List *vizinhos;
    // valor booleano
    struct Spot anterior;
    int muro;
} Celula;

typedef struct List
{
    Celula c;
    struct List *next;
    struct List *prev;
} Lista;

Lista *criar(void);
Lista *inserir(Lista *lista, Ponto elem);
Lista *remover(Lista *l, Ponto elem);
Ponto procurarElementoF(Lista *l, double f);
int maiorElementoF(Lista *l);
int tamanho(Lista *l);
int vazio(Lista *l);
void imprimir(Lista *lista);
void liberar(Lista *l);

#endif