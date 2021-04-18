#ifndef ALGORITMO_AStar
#define ALGORITMO_AStar

#include "lista.h"

#include <math.h>

#define LINHA 10
#define COLUNA 10

int distancia(Ponto a, Ponto b);
void heuristica(Celula *spot, Ponto inicio, Ponto fim);
double heuristic(Celula *a, Celula *b);
double heuristicDestino(Celula *a, Ponto *p);
// nesse adicionarVizinhos, vou usar alguma TAD para ficar incluindo, esse int* vizinhos nao funciona
void adicionarVizinhos(Celula *spot, Celula ***grid, int linhas, int colunas);
int comparar(Celula a, Celula b);

// Apaga essa funcao dps
void imprimirVizinhosPonto(Lista *l);

#endif