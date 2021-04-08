#include "AlgoritmoAStar.h"

int main()
{
    Ponto inicio, destino;
    inicio.x = 0;
    inicio.y = 0;
    destino.x = LINHA - 1;
    destino.y = COLUNA - 1;

    // Criando o grid aqui a mao, mas da para fazer os obstaculos um com rand
    // A linha e coluna estao definidas no .h incluido, se quiser aumentar ou diminuir alguma dimensao, soh alterar lah
    // 1 = Caminho livre.   0 - Caminho bloqueado
    int grid[LINHA][COLUNA] =
        {
            {1, 1, 0, 1, 0},
            {1, 1, 1, 1, 0},
            {1, 1, 1, 1, 0},
            {1, 1, 0, 1, 0},
            {1, 1, 0, 1, 1}};

    Lista *listaAberta = criar();
    Lista *listaFechada = criar();
    listaAberta = inserir(listaAberta, inicio);
    // Desenha o grid...
    Lista * pathfind = criar();
    int parar;
    int anterior;

    while (!vazio(listaAberta))
    {
        if (tamanho(listaAberta) > 0)
        {
            double ganhador = 0.0;
            ganhador = maiorElementoF(listaAberta);//menor
            Celula atual;
            atual.p = procurarElementoF(listaAberta, ganhador);

            if ((atual.p.x == destino.x) && (atual.p.y == destino.y))
            {
                // Desenhar o caminho
                Celula temp = atual;
                
                //empilhar - push
                pathfind = inserir(pathfind,temp.p) ;

                //
                while(temp.anterior != NULL){
                 //empilhar - push
                 pathfind = inserir(pathfind,temp.anterior.p) ;
                 temp = temp.anterior;
                 //essa funcao nao existe afzer desenhaGrid
                 desenhaGrid();
                }
                //done
                return 0;
            }

            listaAberta = remover(listaAberta, atual.p);
            listaFechada = inserir(listaFechada, atual.p);

            Lista *vizinhos = atual.vizinhos;

            for(
                Lista *aux = vizinhos; 
                aux->next != NULL;
                aux = aux->next
            ){
                Celula vizinho = aux->c; 
                //verifica se vizinho ñ esta na pilha fechada
                //verifica se ñ é muro
                if(!procurarElemento(listaFechada,vizinho) && !vizinho.muro){
                    double tempG = atual.g + heuristic(vizinho,atual);
                    int newPathFind = 0;
                    if(procurarElemento(listaAberta,vizinho)){
                        if(tempG < vizinho.g){
                            vizinho.g = tempG;
                            newPathFind = 1;
                        }
                    }else{
                        vizinho.g = tempG;
                        newPathFind = true;
                        listaAberta = inserir(listaAberta,vizinho);
                    }

                    if(newPathFind){
                        vizinho.h = heuristic(vizinho,destino);
                        vizinho.f = vizinho.g + vizinho.h;
                        vizinho.anterior = atual;
                    }
                    
                }
            }
        }
        else{
        //sem solucao
        }
    }

    return 0;
}