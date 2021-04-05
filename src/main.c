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

    int parar;
    int anterior;

    while (!vazio(listaAberta))
    {
        if (tamanho(listaAberta) > 0)
        {
            double ganhador = 0.0;
            ganhador = maiorElementoF(listaAberta);
            Celula atual;
            atual.p = procurarElementoF(listaAberta, ganhador);

            if ((atual.p.x == destino.x) && (atual.p.y == destino.y))
            {
                // Desenhar o caminho
            }

            remover(listaAberta, atual.p);
            inserir(listaFechada, atual.p);

            Lista *vizinhos = atual.vizinhos;
        }
    }

    return 0;
}