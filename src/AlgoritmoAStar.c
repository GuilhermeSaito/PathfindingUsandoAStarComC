#include "AlgoritmoAStar.h"
#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"
int distancia(Ponto a, Ponto b)
{
    int d = abs(a.x - b.x) + abs(a.y - b.y);
    //printf("Vi: %i ",abs(a.x - b.x) + abs(a.y - b.y));
    //printf(" Vd: %d ",d);
    return d;
}
int heuristic(Celula *a, Celula *b)
{
    int h = round(distancia((a->p), (b->p)));
    //printf("Vh: %d\n",h);
    return h;
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
            if (random <= 2)
                grid[i][j]->muro = 1;

            if (i == 0)
            {
                grid[i][j]->muro = 1;
            }

            if (i == COLUNA - 1)
            {
                grid[i][j]->muro = 1;
            }

            if (j == 0)
            {
                grid[i][j]->muro = 1;
            }

            if (j == COLUNA - 1)
            {
                grid[i][j]->muro = 1;
            }

            //colocand a linha
            // if (j == 5)
            //     grid[i][j]->muro = 1;
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
                printf(" %s#%s ", KRED, KNRM);
            else if (grid[i][j]->valor == 3)
                printf(" %s*%s ", KGRN, KNRM);
            else if(grid[i][j]->valor == 0)
                printf("   ");
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

        system("clear");
        usleep(2000);
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
                    if (!grid[i][j]->muro && grid[i][j]->valor != 3 && grid[i][j]->valor != 4 && grid[i][j]->valor != 8)
                        grid[i][j]->valor = 0;
                printf("\n");
            }
            system("clear");
            usleep(2000);
            drawGrid(grid, LINHA, COLUNA);
            return 1;
        }
        //printf("\nLista Aberta antes:\n");
        //imprimir(listaAberta);
        listaAberta = removerCelula(listaAberta, atual); // se nao existe lista fechada insira
        //printf("X:%i Y:%i \n",atual->p.x,atual->p.y);
        //printf("\nLista Aberta depois:\n");
        //imprimir(listaAberta);

        if (existe(listaAberta, atual))
        {
            printf("\nERROR FOUND 1!\n");
            return 0;
        }
        listaFechada = inserirCelula(listaFechada, atual);
        if (!existe(listaFechada, atual))
        {
            printf("\nERROR FOUND 2!\n");
            return 0;
        }

        Lista *vizinhanca = atual->vizinhos;
        while (vizinhanca != NULL)
        {
            Celula *vizinhosDoAtual = vizinhanca->c;
            vizinhosDoAtual->valor = 6;

            // Se nao existir na lista fechada e nao for um muro
            if ((!existe(listaFechada, vizinhosDoAtual)) && (!vizinhosDoAtual->muro))
            {
                int tempG = atual->g + heuristic(vizinhosDoAtual, atual);
                if (!existe(listaAberta, vizinhosDoAtual))
                    listaAberta = inserirCelula(listaAberta, vizinhosDoAtual);
                else if (tempG >= vizinhosDoAtual->g)
                {
                    vizinhanca = vizinhanca->next;
                    continue;
                }

                vizinhosDoAtual->g = tempG;
                vizinhosDoAtual->h = heuristic(vizinhosDoAtual, destino);
                vizinhosDoAtual->f = vizinhosDoAtual->g + vizinhosDoAtual->h;
                vizinhosDoAtual->anterior = atual;
            }
            vizinhanca = vizinhanca->next;
        }
    }
    return 0;
}