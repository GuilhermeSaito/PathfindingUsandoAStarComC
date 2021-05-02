#include "AlgoritmoAStar.h"

int main()
{
    srand(time(NULL));

    int i, j;
    Celula ***grid;

    grid = (Celula ***)malloc(LINHA * sizeof(Celula **));
    for (i = 0; i < COLUNA; i++)
        grid[i] = (Celula **)malloc(COLUNA * sizeof(Celula *));

    initializeGrid(grid, LINHA, COLUNA);

    // colocando os vizinhos no spot
    for (i = 0; i < LINHA; i++)
        for (j = 0; j < COLUNA; j++)
            adicionarVizinhos(grid[i][j], grid, LINHA, COLUNA);

    /* Setando os pontos de inicio e destino */
    Celula *inicio, *destino;

    int rand_x = rand() % (LINHA - 1);
    int rand_y = rand() % (COLUNA - 1);

    inicio = grid[rand_x][rand_y];
    unblockInicioDestino(grid, rand_x, rand_y);
    //unblockInicioDestino(grid, 0, 0);
    //inicio = grid[0][0];
    rand_x = rand() % (LINHA - 1);
    rand_y = rand() % (COLUNA - 1);

    destino = grid[rand_x][rand_y];
    unblockInicioDestino(grid, rand_x, rand_y);
    //unblockInicioDestino(grid, COLUNA - 1, LINHA - 1);
    destino = grid[COLUNA - 1][LINHA - 1];
    Lista *listaAberta = criar();
    Lista *listaFechada = criar();

    listaAberta = inserirCelula(listaAberta, inicio);

    // O inicio ja estah na listaAberta!
    if (pathFind(grid, inicio, destino, listaAberta, listaFechada))
        printf("Chegamos no destino!\n");
    else
        printf("Nao achei o caminho!\n");

    freeGrid(grid, LINHA, COLUNA);

    return 0;
}