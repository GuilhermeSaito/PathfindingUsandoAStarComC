#ifndef ALGORITMO_AStar
#define ALGORITMO_AStar

#include "lista.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include <fcntl.h>

#define LINHA 15
#define COLUNA 15

int distancia(Ponto a, Ponto b);
void heuristica(Celula *spot, Ponto inicio, Ponto fim);
double heuristic(Celula *a, Celula *b);
double heuristicDestino(Celula *a, Ponto *p);
void adicionarVizinhos(Celula *spot, Celula ***grid, int linhas, int colunas);
int comparar(Celula a, Celula b);

void initializeGrid(Celula ***grid, int linhas, int colunas);
void unblockInicioDestino(Celula ***grid, int x, int y);
void drawGrid(Celula ***grid, int linhas, int colunas);
void setNumberListaAberta(Lista *listaAberta);
void setNumberListaFechada(Lista *listaFechada);
int isDestino(Celula *atual, Celula *destino);
void freeGrid(Celula ***grid, int linhas, int colunas);

int pathFind(Celula ***grid, Celula *inicio, Celula *destino, Lista *listaAberta, Lista *listaFechada);

#endif