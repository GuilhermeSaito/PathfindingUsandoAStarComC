#include "AlgoritmoAStar.h"

int distancia(Ponto a, Ponto b)
{
    return abs(a.x - b.x) + abs(a.y - a.y);
}

void heuristica(Celula *spot, Ponto inicio, Ponto fim)
{
    // Custo do inicio ateh o atual
    spot->g = round(distancia(spot->p, inicio));
    spot->h = round(distancia(spot->p, fim));
    spot->f = spot->g + spot->h;
}

double heuristic(Celula a, Celula b)
{
    return round(distancia((a.p), (b.p)));
}

int comparar(Celula a, Celula b)
{
    if (a.f > b.f)
        return -1;
    else if (a.f < b.f)
        return 1;
    return 0;
}