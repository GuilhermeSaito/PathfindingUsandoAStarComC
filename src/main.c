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

<<<<<<< HEAD
    int rand_x = rand() % (LINHA - 2);
    int rand_y = rand() % (COLUNA - 2);

    inicio = grid[rand_x][rand_y];
    unblockInicioDestino(grid, rand_x, rand_y);
    //unblockInicioDestino(grid, 0, 0);
    //inicio = grid[0][0];
    rand_x = rand() % (LINHA - 2);
    rand_y = rand() % (COLUNA - 2);

    destino = grid[rand_x][rand_y];
    unblockInicioDestino(grid, rand_x, rand_y);
    //unblockInicioDestino(grid, COLUNA - 1, LINHA - 1);
    //destino = grid[COLUNA - 1][LINHA - 1];
=======
    int rand_x = (rand() % ((LINHA - 2) - 1)) + 1;
    int rand_y = (rand() % ((COLUNA - 2) - 1)) + 1;

    //inicio = grid[rand_x][rand_y];
    //unblockInicioDestino(grid, rand_x, rand_y);
    //grid[rand_x][rand_y]->valor = 4;
    unblockInicioDestino(grid, 1, 1);
    inicio = grid[1][1];
    grid[1][1]->valor = 4;
    rand_x = (rand() % ((LINHA - 2) - 1)) + 1;
    rand_y = (rand() % ((COLUNA - 2) - 1)) + 1;

    // destino = grid[rand_x][rand_y];
    // unblockInicioDestino(grid, rand_x, rand_y);
    // grid[rand_x][rand_y]->valor = 8;
    unblockInicioDestino(grid, LINHA - 2, LINHA - 2);
    destino = grid[LINHA - 2][LINHA - 2];
    grid[LINHA - 2][LINHA - 2]->valor = 8;
>>>>>>> 5b1ddecb3d813a47b501f354c246d4d443bcb770
    Lista *listaAberta = criar();
    Lista *listaFechada = criar();

    listaAberta = inserirCelula(listaAberta, inicio);

    // O inicio ja estah na listaAberta!
    if (pathFind(grid, inicio, destino, listaAberta, listaFechada))
        printf("Chegamos no destino!\n");
    else
        printf("Nao achei o caminho!\n");

    liberar(listaAberta);
    liberar(listaFechada);
    freeGrid(grid, LINHA, COLUNA);

    return 0;
}