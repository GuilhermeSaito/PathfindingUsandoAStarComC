/**
 * 
 *  Curso: Engenharia da Computação - Universidade Técnologica Federal do Paraná
 *  Tema: Pathfinding A*
 *  Autores: Matheus de Camargo Marques , Guilherme Saito , Carolina Fernandes
 * 
 *  @link Repositorio https://github.com/GuilhermeSaito/PathfindingUsandoAStarComC
 *  @copyright - Livre para fim didáticos.
 */

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
    int f;
    int g;
    int h;
    struct List *vizinhos;
    struct Spot *anterior;
    int muro;
} Celula;

typedef struct List
{
    Celula *c;
    struct List *next;
    struct List *prev;
} Lista;

Lista *criar(void);
Lista *inserirCelula(Lista *lista, Celula *c);
Lista *removerCelula(Lista *lista, Celula *c);

int existe(Lista *l, Celula *c);
Celula *procurarMenor(Lista *l);
int tamanho(Lista *l);
int vazio(Lista *l);
void imprimir(Lista *lista);
void liberar(Lista *l);

#endif