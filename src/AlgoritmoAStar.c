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
        spot->vizinhos = inserirCelula(spot->vizinhos, grid[i + 1][j]);
    if (i > 0)
        spot->vizinhos = inserirCelula(spot->vizinhos, grid[i - 1][j]);
    if (j < linhas - 1)
        spot->vizinhos = inserirCelula(spot->vizinhos, grid[i][j + 1]);
    if (j > 0)
        spot->vizinhos = inserirCelula(spot->vizinhos, grid[i][j - 1]);
}

int comparar(Celula a, Celula b)
{
    if (a.f > b.f)
        return -1;
    else if (a.f < b.f)
        return 1;
    return 0;
}

void initializeGrid(Celula ***grid, int linhas, int colunas)
{
    int i, j;
    for (i = 0; i < LINHA; i++)
        for (j = 0; j < COLUNA; j++)
        {
            grid[i][j] = (Celula *)malloc(sizeof(Celula));
            grid[i][j]->p.x = i;
            grid[i][j]->p.y = j;
            grid[i][j]->f = 0;
            grid[i][j]->g = 0;
            grid[i][j]->h = 0;
            grid[i][j]->valor = 0;
            grid[i][j]->vizinhos = NULL;
            grid[i][j]->anterior = NULL;
            grid[i][j]->muro = 0;

            //Random de  0 a 9
            int random = rand() % 10;
            if (random <= 0 && 0)
                grid[i][j]->muro = 1;

            if (i == 0) {
                grid[i][j]->muro = 1;
            }

            if (i == COLUNA - 1) {
               grid[i][j]->muro = 1;
            }

            if (j == 0) {
               grid[i][j]->muro = 1;
            }

            if (j == COLUNA - 1) {
               grid[i][j]->muro = 1;
            }
        }
}

void unblockInicioDestino(Celula ***grid, int x, int y)
{
    grid[x][y]->muro = 0;
}

void drawGrid(Celula ***grid, int linhas, int colunas)
{

    for (int i = 0; i < LINHA; i++)
    {
        for (int j = 0; j < COLUNA; j++)
            if (grid[i][j]->muro)
                printf(" \e[0;33m#\x1b[0m ");
            else if (grid[i][j]->valor == 3)
                printf(" \x1b[31m*\x1b[0m ");
            else
                printf(" %i ", grid[i][j]->valor);
        printf("\n");
    }
    printf("\n\n");
}

void setNumberListaAberta(Lista *listaAberta)
{
    Lista *aux = listaAberta;
    while (aux != NULL)
    {
        aux->c->valor = 2;
        aux = aux->next;
    }
}

void setNumberListaFechada(Lista *listaFechada)
{
    Lista *aux = listaFechada;
    while (aux != NULL)
    {
        aux->c->valor = 1;
        aux = aux->next;
    }
}

int isDestino(Celula *atual, Celula *destino)
{
    return (atual->p.x == destino->p.x) && (atual->p.y == destino->p.y);
}

void freeGrid(Celula ***grid, int linhas, int colunas)
{
    int i, j;
    // Desalocando o grid
    for (i = 0; i < LINHA; i++)
    {
        for (j = 0; j < COLUNA; j++)
            free(grid[i][j]);
        free(grid[i]);
    }
    free(grid);
}

int pathFind(Celula ***grid, Celula *inicio, Celula *destino, Lista *listaAberta, Lista *listaFechada)
{
    while (!vazio(listaAberta))
    {
        Celula *atual = procurarMenor(listaAberta);

        setNumberListaAberta(listaAberta);
        setNumberListaFechada(listaFechada);

        system("cls");
        usleep(3000);
        drawGrid(grid, LINHA, COLUNA);
        if (isDestino(atual, destino))
        {
            Celula *aux = atual;
            atual->valor = 3;
            while (aux->anterior != NULL)
            {
                aux->valor = 3;
                aux = aux->anterior;
            }
            for (int i = 0; i < LINHA; i++)
            {
                for (int j = 0; j < COLUNA; j++)
                    if (!grid[i][j]->muro && grid[i][j]->valor != 3)
                        grid[i][j]->valor = 0;
                printf("\n");
            }

            drawGrid(grid, LINHA, COLUNA);
            return 1;
        }

        listaAberta = removerCelula(listaAberta, atual);
        listaFechada = inserirCelula(listaFechada, atual);

        Lista *vizinhanca = atual->vizinhos;
        while (vizinhanca != NULL)
        {
            Celula *vizinhosDoAtual = vizinhanca->c;
            // Se nao existir na lista fechada e nao for um muro
            if ((!existe(listaFechada, vizinhosDoAtual)) && (!vizinhosDoAtual->muro))
            {
                double tempG = atual->g + heuristic(vizinhosDoAtual, atual);
                //double tempG = heuristic(vizinhosDoAtual, inicio);
                int newPathFind = 0;

                // if (!existe(listaAberta, vizinhosDoAtual))
                // {
                //     vizinhosDoAtual->g = tempG;
                //     vizinhosDoAtual->h = heuristic(vizinhosDoAtual, destino);
                //     vizinhosDoAtual->f = vizinhosDoAtual->g + vizinhosDoAtual->h;
                //     vizinhosDoAtual->anterior = atual;
                //     listaAberta = inserirCelula(listaAberta, vizinhosDoAtual);
                // }
                if (existe(listaAberta, vizinhosDoAtual))
                {
                    if (tempG < vizinhosDoAtual->g)
                    {
                        newPathFind = 1;
                        vizinhosDoAtual->g = tempG;
                    }
                }
                else
                {
                    newPathFind = 1;
                    vizinhosDoAtual->g = tempG;
                    listaAberta = inserirCelula(listaAberta, vizinhosDoAtual);
                }

                if (newPathFind)
                {
                    vizinhosDoAtual->h = heuristic(vizinhosDoAtual, destino);
                    vizinhosDoAtual->f = vizinhosDoAtual->g + vizinhosDoAtual->h;
                    vizinhosDoAtual->anterior = atual;
                }
            }
            vizinhanca = vizinhanca->next;
        }
    }
    return 0;
}