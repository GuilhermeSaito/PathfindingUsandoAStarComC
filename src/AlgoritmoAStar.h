#ifndef ALGORITMO_AStar
#define ALGORITMO_AStar

#include "lista.h"

#include <math.h>

#define LINHA 5
#define COLUNA 5

int distancia(Ponto a, Ponto b);
void heuristica(Celula *spot, Ponto inicio, Ponto fim);
double heuristic(Celula *a, Celula *b);
// nesse adicionarVizinhos, vou usar alguma TAD para ficar incluindo, esse int* vizinhos nao funciona
void adicionarVizinhos(Celula *spot, int grid[][50]);
int comparar(Celula a, Celula b);

#endif