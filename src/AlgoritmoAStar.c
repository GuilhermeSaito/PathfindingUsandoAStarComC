#include "AlgoritmoAStar.h"

int distancia(Ponto a, Ponto b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}

void heuristica(Celula *spot, Ponto inicio, Ponto fim)
{
    // Custo do inicio ateh o atual
    spot->g = round(distancia(spot->p, inicio));
    spot->h = round(distancia(spot->p, fim));
    spot->f = spot->g + spot->h;
}

double heuristic(Celula *a, Celula *b)
{
    return round(distancia((a->p), (b->p)));
}
double heuristicDestino(Celula *a, Ponto *p)
{
    return round(distancia((a->p), *p));
}

void adicionarVizinhos(Celula *spot, Celula ***grid, int colunas, int linhas)
{
    int i = spot->p.x;
    int j = spot->p.y;

    if (i < colunas - 1)
    {
        //spot.neighbors.push(grid[i + 1][j]);
        spot->vizinhos = inserirCelula(spot->vizinhos, grid[i + 1][j]);
    }
    if (i > 0)
    {
        //spot.neighbors.push(grid[i - 1][j]);
        spot->vizinhos = inserirCelula(spot->vizinhos, grid[i - 1][j]);
    }
    if (j < linhas - 1)
    {
        //spot.neighbors.push(grid[i][j + 1]);
        spot->vizinhos = inserirCelula(spot->vizinhos, grid[i][j + 1]);
    }
    if (j > 0)
    {
        //spot.neighbors.push(grid[i][j - 1]);
        spot->vizinhos = inserirCelula(spot->vizinhos, grid[i][j - 1]);
    }
}

int comparar(Celula a, Celula b)
{
    if (a.f > b.f)
        return -1;
    else if (a.f < b.f)
        return 1;
    return 0;
}

// Apagar essa funcao dps
void imprimirVizinhosPonto(Lista *l)
{
    Lista *aux = l;
    while (aux != NULL)
    {
        printf("X: %d\tY: %d\n", aux->c->p.x, aux->c->p.y);
        aux = aux->next;
    }
    printf("\n\n");
}