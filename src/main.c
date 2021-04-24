#include "AlgoritmoAStar.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include <unistd.h>
#include <fcntl.h>

#define true 1
#define false 0


void drawGrid(Celula*** grid,int linhas,int colunas){
    
       for (int i = 0; i < LINHA; i++){
            for (int j = 0; j < COLUNA; j++){
                //printf("%d",grid[i][j]->muro);
                if(grid[i][j]->muro){
                    printf(" # ");
                }else if(grid[i][j]->valor == 3){
                    printf(" * ");
                }
                else{
                    printf(" %i ",grid[i][j]->valor);
                }
            }
            printf("\n");
       }
        
    //system("clear");
    printf("\n\n");
}

int main()
{
    srand(time(NULL));
    // Criando o grid aqui a mao, mas da para fazer os obstaculos um com rand
    // A linha e coluna estao definidas no .h incluido, se quiser aumentar ou diminuir alguma dimensao, soh alterar lah
    // 1 = Caminho livre.   0 - Caminho bloqueado

    // Alocando a matrix grid
    int i, j;
    Celula ***grid; // =

    grid = (Celula ***)malloc(LINHA * sizeof(Celula **));
    for (i = 0; i < COLUNA; i++)
        grid[i] = (Celula **)malloc(COLUNA * sizeof(Celula *));

    // Inicializar o grid
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

            //Random de  0 a 10
            //Se random for <=4 diz que muro
            // 
            int random = rand()%10;

            if(random == 0 ){
                grid[i][j]->muro = 1;
            }
            
        }

    // colocando os vizinhos no spot
    for (i = 0; i < LINHA; i++)
        for (j = 0; j < COLUNA; j++)
            adicionarVizinhos(grid[i][j], grid, LINHA, COLUNA);

    Celula *inicio, *destino;
    int rand_x = rand()% (LINHA-1);
    int rand_y = rand()% (COLUNA-1); 


    inicio = grid[rand_x][rand_y];
    
    rand_x = rand()% (LINHA-1);
    rand_y = rand()% (COLUNA-1); 

    destino = grid[rand_x][rand_y];

    Lista *listaAberta  = criar();
    Lista *listaFechada = criar();

    listaAberta = inserirCelula(listaAberta, inicio);
    // Desenha o grid...
    Lista *pathfind;
    int parar;
    int anterior;

    int flag = 0;
    //int contador = 0;
    while (!vazio(listaAberta))
    {
        Celula *atual = procurarMenor(listaAberta);
        //printf("%d %d \n",atual->p.x,atual->p.y);
        //break;

        //desenha pilha fechada
        Lista * aux = listaAberta;

        while(aux != NULL){
            aux->c->valor = 2;
            aux = aux->next;
        }

        //desenha pilha aberta
        aux = listaFechada;

        while(aux != NULL){
            aux->c->valor = 1;
            aux = aux->next;
        }

        system("clear");
        usleep(2000);
        drawGrid(grid,LINHA,COLUNA);
        if ((atual->p.x == destino->p.x) && (atual->p.y == destino->p.y))
        {
            flag = 1;
            //printf("Entro no if de chegada no destino\n");
            //pathfind = criar();
            Celula *aux = atual;
            atual->valor = 3;
            i = 0;
            while (aux->anterior != NULL)
            {
                //drawGrid(grid,LINHA,COLUNA);
                aux = aux->anterior;
                aux->valor = 3;
                //printf("%d %d \n",aux->p.x,aux->p.y);
                i++;

            }
            for (int i = 0; i < LINHA; i++){
            for (int j = 0; j < COLUNA; j++){
                //printf("%d",grid[i][j]->muro);
                if(!grid[i][j]->muro && grid[i][j]->valor != 3){
                    grid[i][j]->valor = 0;
                }
                
            }
            printf("\n");
            }
        
            drawGrid(grid,LINHA,COLUNA);
            printf("\nDEU CERTO K7!!!!\n\n");
            break;
        }

       
        listaAberta = removerCelula(listaAberta, atual);
        listaFechada = inserirCelula(listaFechada, atual);

        Lista *vizinhanca = atual->vizinhos;
        while (vizinhanca != NULL)
        {
            Celula *vizinhosDoAtual = vizinhanca->c;
            // Se nao existir na lista fechada e nao for um muro
            if (!existe(listaFechada, vizinhosDoAtual) && !vizinhosDoAtual->muro)
            {
                //printf("Entro no if do lista fechada\n");
                double tempG = atual->g + heuristic(vizinhosDoAtual, atual);

                int newPathFind = false;

                if (existe(listaAberta, vizinhosDoAtual))
                {
                    if (tempG < vizinhosDoAtual->g)
                    {
                        newPathFind = true;
                        vizinhosDoAtual->g = tempG;
                        
                    }
                }
                else
                {
                    newPathFind = true;
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
    

            //Vizinhança anda pra frente (Percorrendo a Lista)
            vizinhanca = vizinhanca->next;
        }
    }

    if (!flag)
        printf("Nao achei o caminho!\n");

    // Desalocando o grid
    for (i = 0; i < LINHA; i++)
    {
        for (j = 0; j < COLUNA; j++)
            free(grid[i][j]);
        free(grid[i]);
    }
    free(grid);

    return 0;
}