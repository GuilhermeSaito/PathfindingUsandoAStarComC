/**
 * 
 *  Curso: Engenharia da Computação - Universidade Técnologica Federal do Paraná
 *  Tema: Pathfinding A*
 *  Autores: Matheus de Camargo Marques , Guilherme Saito , Carolina Fernandes
 * 
 *  @link Repositorio https://github.com/GuilhermeSaito/PathfindingUsandoAStarComC
 *  @copyright - Livre para fim didáticos.
 */

#include "AlgoritmoAStar.h"



int main()
{
    srand(time(NULL));

    Celula *inicio, *destino;
    Celula ***grid = makeGrid(LINHA,COLUNA);


    initializeGrid(grid, LINHA, COLUNA);
    initializeVizinhanca(grid, LINHA, COLUNA);
    
    /* Setando os pontos de inicio e destino */
    int x,y;
    x = y = 1;
    unblockInicioDestino(grid, x, y);
    inicio = grid[x][y];
    
    
    x = LINHA - 2; y = COLUNA - 2;
    unblockInicioDestino(grid,x,y);
    destino = grid[x][y];
    
    
    /* Inciamos lista aberta e fechada */
    Lista *listaAberta = criar();
    Lista *listaFechada = criar();

    /* Lista aberta não inicia vazia*/
    listaAberta = inserirCelula(listaAberta, inicio);

    
    if (pathFind(grid, inicio, destino, listaAberta, listaFechada))
        printf("Chegamos no destino!\n");
    else
        printf("Nao achei o caminho!\n");

    liberar(listaAberta);
    liberar(listaFechada);
    freeGrid(grid, LINHA, COLUNA);

    return 0;
}