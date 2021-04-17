#include "AlgoritmoAStar.h"
#include "lista.h"

#define true 1
#define false 0

int main()
{

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
        }

    // colocando os vizinhos no spot
    for (i = 0; i < LINHA; i++)
        for (j = 0; j < COLUNA; j++)
            adicionarVizinhos(grid[i][j], grid, LINHA, COLUNA);

    Celula *inicio, *destino;
    inicio = grid[0][0];
    destino = grid[LINHA - 1][COLUNA - 1];

    Lista *listaAberta = criar();
    Lista *listaFechada = criar();
    listaAberta = inserirCelula(listaAberta, inicio);
    // Desenha o grid...
    Lista *pathfind;
    int parar;
    int anterior;

    //int contador = 0;
    while (!vazio(listaAberta))
    {
        //contador++;
        //procuramos o menor f dos elementa da lista aberta
        //printf("Vai Procupar o menor a matriz\n");
        Celula *atual = procurarMenor(listaAberta);
        printf("\nCelula Atual: %d\t%d\n", atual->p.x, atual->p.y);
        printf("\nDestino: %d\t%d\n", destino->p.x, destino->p.y);
        //Chagamos ao destino
        if ((atual->p.x == destino->p.x) && (atual->p.y == destino->p.y))
        {
            //printf("Entro no if de chegada no destino\n");
            /*pathfind = criar();
            Celula *temp = atual;
            inserir(pathfind, temp->p);
            while (temp != NULL)
            {
                Ponto p = temp->anterior->p;
                inserir(pathfind, p);
                temp = temp->anterior;
                //print grid pathfindind
            }*/
            printf("\nDEU CERTO K7!!!!\n\n");
            break;
        }

        //remover pilha aperta atual e coloca na pilha fechada
        listaAberta = removerCelula(listaAberta, atual);
        //printf("Vai Inserir\n");
        listaFechada = inserirCelula(listaFechada, atual);

        Lista *vizinhanca = atual->vizinhos;
        imprimirVizinhosPonto(vizinhanca);
        //if (vizinhanca == NULL)
        //printf("Vai Inserir\n");
        while (vizinhanca != NULL)
        {
            // Na primeira vez, aqui vai ser os 2 cantos (1,0) (0,1)
            Celula *vizinhosDoAtual = vizinhanca->c;
            //heuristica(vizinhosDoAtual, inicio->p, destino->p);

            // Se nao existir na lista fechada e nao for um muro
            if (!existe(listaFechada, vizinhosDoAtual) && !vizinhosDoAtual->muro)
            {
                //printf("Entro no if do lista fechada\n");
                double tempG = atual->g + heuristic(vizinhosDoAtual, atual);

                int newPathFind = false;

                if (existe(listaAberta, vizinhosDoAtual))
                {
                    //printf("Existe o elemento na lista Aberta\n");
                    if (tempG < vizinhosDoAtual->g)
                    {
                        //printf("temp G < vizinhosDoAtual\n");
                        vizinhosDoAtual->g = tempG;
                        newPathFind = true;

                        /*vizinhosDoAtual->h = heuristic(vizinhosDoAtual, destino);
                        vizinhosDoAtual->f = vizinhosDoAtual->g + vizinhosDoAtual->h;
                        vizinhosDoAtual->anterior = atual;*/
                    }
                }
                else
                {
                    //printf("Vai colocar na lista aberta\n");
                    vizinhosDoAtual->g = tempG;
                    newPathFind = true;

                    /*vizinhosDoAtual->h = heuristic(vizinhosDoAtual, destino);
                    vizinhosDoAtual->f = vizinhosDoAtual->g + vizinhosDoAtual->h;
                    vizinhosDoAtual->anterior = atual;*/

                    listaAberta = inserirCelula(listaAberta, vizinhosDoAtual);
                    printf("\nListaAberta: \n");
                    imprimirVizinhosPonto(listaAberta);
                    printf("\nVizinhso do atual: \n");
                    imprimirVizinhosPonto(vizinhosDoAtual->vizinhos);
                }

                if (newPathFind)
                {
                    vizinhosDoAtual->h = heuristic(vizinhosDoAtual, destino);
                    vizinhosDoAtual->f = vizinhosDoAtual->g + vizinhosDoAtual->h;
                    vizinhosDoAtual->anterior = atual;
                }
            }
            //else if (!existe(listaFechada, vizinhosDoAtual))
            //    listaAberta = inserirCelula(listaAberta, vizinhosDoAtual);

            //
            vizinhanca = vizinhanca->next;
        }
    }

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