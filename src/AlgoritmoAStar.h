/**
 * 
 *  Curso: Engenharia da Computação - Universidade Técnologica Federal do Paraná
 *  Tema: Pathfinding A*
 *  Autores: Matheus de Camargo Marques , Guilherme Saito , Carolina Fernandes
 * 
 *  @link Repositorio https://github.com/GuilhermeSaito/PathfindingUsandoAStarComC
 *  @copyright - Livre para fim didáticos.
 */

#ifndef ALGORITMO_AStar
#define ALGORITMO_AStar

#include "lista.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include <fcntl.h>

#define LINHA 30
#define COLUNA 30

int distancia(Ponto a, Ponto b);
int heuristic(Celula *a, Celula *b);
void adicionarVizinhos(Celula *spot, Celula ***grid, int linhas, int colunas);

void initializeGrid(Celula ***grid, int linhas, int colunas);
void unblockInicioDestino(Celula ***grid, int x, int y);
void drawGrid(Celula ***grid, int linhas, int colunas);
void setNumberListaAberta(Lista *listaAberta);
void setNumberListaFechada(Lista *listaFechada);
int  isDestino(Celula *atual, Celula *destino);
void freeGrid(Celula ***grid, int linhas, int colunas);

int pathFind(Celula ***grid, Celula *inicio, Celula *destino, Lista *listaAberta, Lista *listaFechada);
Celula *** makeGrid(int linha,int coluna);
void initializeVizinhanca(Celula ***grid,int linha, int coluna);


#endif