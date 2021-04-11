#include "AlgoritmoAStar.h"
#include "lista.h"
#define true  1
#define false  1
int main()
{
   

    // Criando o grid aqui a mao, mas da para fazer os obstaculos um com rand
    // A linha e coluna estao definidas no .h incluido, se quiser aumentar ou diminuir alguma dimensao, soh alterar lah
    // 1 = Caminho livre.   0 - Caminho bloqueado
    
    // Alocando a matrix grid
    int i, j;
    Celula** grid; // =
    
    grid = (Celula**)malloc(LINHA * sizeof(Celula*));
    for (i = 0; i < COLUNA; i++)
        grid[i] = (Celula*)malloc(COLUNA * sizeof(Celula));
    
    
    // Inicializar o grid
    for(i = 0; i < LINHA; i++)
        for(j = 0; j < COLUNA; j++)
        {
           // grid[i][j] = (Celula*)malloc(sizeof(Celula));
            grid[i][j].p.x = i;
            grid[i][j].p.y = j;
            grid[i][j].f = 0;
            grid[i][j].g = 0;
            grid[i][j].h = 0;
            grid[i][j].valor = 0;
            grid[i][j].vizinhos = criar();
            grid[i][j].anterior = criar();
            grid[i][j].muro = false;
        }

    // colocando os vizinhos no spot
    for(i = 0; i < LINHA; i++){
        for(j = 0; j < COLUNA; j++)
        {
            adicionarVizinhos(&grid[i][j],grid,LINHA,COLUNA);
        }
    }
    // Ai tem que adicionar as vizinhancas
    Ponto inicio, destino;
    inicio.x = 0;
    inicio.y = 0;
    destino.x = LINHA - 1;
    destino.y = COLUNA - 1;

    Lista *listaAberta = criar();
    Lista *listaFechada = criar();
    listaAberta = inserir(listaAberta, inicio);
    // Desenha o grid...
    Lista * pathfind ;
    int parar;
    int anterior;

    while(!vazio(listaAberta)){
        //procuramos o menor f dos elementa da lista aberta
        Celula atual = procurarMenor(listaAberta);

        //Chagamos ao destino
        if((atual.p.x == destino.x) && (atual.p.y == destino.y)) {
            pathfind = criar();
            Celula* temp = &atual;
            inserir(pathfind, temp->p);
            while(temp != NULL){
                Ponto p = temp->anterior->p;
                inserir(pathfind, p);
                temp = temp->anterior;
                //print grid pathfindind
            }   
        }

        //remover pilha aperta atual e coloca na pilha fechada
        listaAberta = remover(listaAberta,atual.p);
        listaFechada = inserir(listaFechada, atual.p);

        Lista * vizinhanca = atual.vizinhos;
        Lista * aux = vizinhanca;
        while (aux != NULL)
        {
            Celula vizinho = aux->c;

            if(!existe(listaFechada,vizinho) && !vizinho.muro){
                double tempG = atual.g + heuristic(&vizinho,&atual);

                int newPathFind = false;

                if(existe(listaAberta,vizinho)){
                    if(tempG < vizinho.g){
                        vizinho.g = tempG;
                        newPathFind = true;
                    }
                }else{
                    vizinho.g = tempG;
                    newPathFind = true;
                    inserir(listaAberta,vizinho.p);
                }  

                if(newPathFind){
                    vizinho.h = heuristic(&vizinho,&destino);
                    vizinho.f = vizinho.g + vizinho.h;
                    vizinho.anterior = &atual;
                }
            }

            //
            aux = aux->next;
        }
    }
 
    // Desalocando o grid
    for (i = 0; i < LINHA; i++)
        free (grid[i]);
    free(grid);

    return 0;
}