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
#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"
#define CLEAR "cls"

Celula ***makeGrid(int linha, int coluna)
{
    Celula ***grid;
    grid = (Celula ***)malloc(LINHA * sizeof(Celula **));
    for (int i = 0; i < COLUNA; i++)
        grid[i] = (Celula **)malloc(COLUNA * sizeof(Celula *));

    return grid;
}

void initializeVizinhanca(Celula ***grid, int linha, int coluna)
{
    // colocando os vizinhos no spot
    for (int i = 0; i < LINHA; i++)
        for (int j = 0; j < COLUNA; j++)
            adicionarVizinhos(grid[i][j], grid, LINHA, COLUNA);
}

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
            //Nossos Pesos
            grid[i][j]->f = 0;
            grid[i][j]->g = 0;
            grid[i][j]->h = 0;

            //Explicação de custos
            grid[i][j]->f = grid[i][j]->g + grid[i][j]->h;

            //Serve mais para testes
            grid[i][j]->valor = 0;

            //É IMPORTANTE
            grid[i][j]->vizinhos = NULL;

            //Heap 
            grid[i][j]->anterior = NULL;


            grid[i][j]->muro = 0;

            //Random de  0 a 9
            int random = rand() % 10;
            if (random <= 2)
                grid[i][j]->muro = 1;


            // Extrimidade colamos muros
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
            else if (grid[i][j]->valor == 0)
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

/**
 *     Em resumo:
 *     A heuristica do algoritmo diz que devemos calcular
 *     F(x) = g(x) + h(x)
 *     sendo g o custo do inicio até o a celula que estamos olhando.
 *     sendo h o custo da celula até o fim .  
 *      
 *     Fizemos algumas mudanças em relação ao calculo de g(x) sendo o custo da celula g(vizinho) = G(atual) + a heuristica de g(vizinho)
 *     g(x) = custo g do inicio + custo g da atual ate o inicio
 *     sendo o inicio sempre a celula anterior
 *     Em pseudocódigo ficaria algo como:
 *  
 *         inicio = celulaComMenorF(ListaAberta)
 *         vizinhanca = vizinhosDe(inicio);  
 *         percorre vizinhanca -> vizinho
 *              vizinhoG = inicioG + heuristica(vizinho,inicio);
 *   
 *     E a príncipio:
 *         O algoritmo se baseia em dar um passo para frente verificar a vizinhanca desse passo e pontuar o menor custo
 *         Lista aberta serve para que possamos ter um aonde verificar
 *         Lista fechada serve para que possamos saber se aonde estamos olhando ja nao foi verificado
 *    
 *           0 - Pegamos da Lista Aberta a celula com menor F
 *           1 - Como vamos verificar essa celula removemos da lista Aberta e adicionamos a Lista fechada, isso serve para não verificarmos novamente ela.
 *           2 - Pegamos a vizinhança da celula que pontamos com o menor F.
 *           3 - Para cada celula vizinha, da celula com menor F
 *           4 - Verificamos se ela esta na lista fechada e se elá não é um muro
 *           5 - Guardamos o custo G da celula atual e somamos com a heuristica -> distancia (depende da implementacao) da ceula atual com celula vizinha
 *           6 - Verificamos Se esse vizinho não esta na listaAberta, se sim inserimos na listaAberta
 *           7 - Se não,  verificamos se a temporaria tem valor maior ou igual do custo g da celula vizinha , se sim verificamos a próxima vizinha
 *           8 - Atribuimos os custos g , h ,f e setamos como celula anterior da celula vizinha a celula atual que estamos olhando.
 *           9 - Se chegarmos no destino percorremos todos os anterios
 *           10 - Se a lista Aberta ficar vazia antes de achar o caminho , significa que o caminho não existe
 *   
 *   FIXX-ME - MELHORIA EM EXPLICAÇÃO @author Matheus C Marques
 */

int pathFind(Celula ***grid, Celula *inicio, Celula *destino, Lista *listaAberta, Lista *listaFechada)
{

    while (!vazio(listaAberta))
    {
        Celula *atual = procurarMenor(listaAberta);

        setNumberListaAberta(listaAberta);
        setNumberListaFechada(listaFechada);

        system(CLEAR);
        //usleep(2000);
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
            system(CLEAR);
            //usleep(2000);
            drawGrid(grid, LINHA, COLUNA);
            return 1;
        }

        listaAberta = removerCelula(listaAberta, atual);
        listaFechada = inserirCelula(listaFechada, atual);

        // Bug Report:
        // Como esse simples debug salvou nosso trabalho caso contrário ficara aqui, pela eternidade
        // (após horas de erros consecutivos a solução do nosso problema estava nas linhas abaixo).
        // Nossa função remover estava com defeitos, e como não removia da lista o bug era que um loop eterno era gerado
        // Os testes de mesa não apontavam para aqui pois a função remover funcionava para alguns casos, então não verificavamos ela
        // Em um ultimo momento esse teste veio a calhar, (que deviamos ter feito desde o inicio).
        // @Mineto - Ideal para exercícios como implemente corretamente ou morra tentando.

        // As linhas abaixo só fazem sentido se a função removerCelula e inserirCelula estiverem com defeitos
        // 
        // if (existe(listaAberta, atual))
        // {
        //     printf("\nERROR FOUND 1!\n");
        //     return 0;
        // }
        // if (!existe(listaFechada, atual))
        // {
        //     printf("\nERROR FOUND 2!\n");
        //     return 0;
        // }

        Lista *vizinhanca = atual->vizinhos;
        while (vizinhanca != NULL)
        {
            Celula *vizinhosDoAtual = vizinhanca->c;

            if (!existe(listaFechada, vizinhosDoAtual) && !vizinhosDoAtual->muro)
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