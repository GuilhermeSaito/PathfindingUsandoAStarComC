#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LINHA 3
#define COLUNA 3

typedef struct Point
{
    int x;
    int y;
} Ponto;

typedef struct Spot
{
    int valor;
    Ponto p;
    double f;
    double g;
    double h;
    struct List *vizinhos;
    // valor booleano
    struct Spot *anterior;
    int muro;
} Celula;

typedef struct List
{
    Celula *c;
    struct List *next;
    struct List *prev;
} Lista;

Lista *criar(void)
{
    return NULL;
}

/*Função para inserir um elemento na cabeça de uma lista encadeada!*/
Lista *inserir(Lista *lista, Ponto elem)
{
    Lista *novo = (Lista *)malloc(sizeof(Lista));
    novo->c->valor = 0;
    novo->c->p = elem;
    novo->c->f = 0.0;
    novo->c->g = 0.0;
    novo->c->h = 0.0;
    novo->c->vizinhos = criar();
    novo->c->anterior = NULL;
    novo->c->muro = 0;

    novo->next = lista;
    novo->prev = NULL;
    return novo;
}

Lista *inserirCelula(Lista *lista, Celula *c)
{
    Lista *novo = (Lista *)malloc(sizeof(Lista));
    novo->c = c;

    novo->next = lista;
    novo->prev = NULL;
    return novo;
}

/*Função para remover um elemento da lista encadeada em qq posição!*/
Lista *remover(Lista *l, Ponto elem)
{
    printf("Entro no remover!\n");
    Lista *prev = NULL, *aux = l;
    while ((aux != NULL) && (aux->c->p.x != elem.x) && (aux->c->p.y != elem.y))
    {
        printf("deveria sair...\n");
        prev = aux;
        aux = aux->next;
    }
    if (aux == NULL) // Nao achou o elemento
    {
        printf("Nao achou o elemento a remover na lista\n");
        return l;
    }
    else if (prev == NULL) // Eh o primeiro elemento
    {
        printf("Seria o primeiro elemento!\n");
        l = l->next;
        if (l != NULL)
            l->prev = NULL;
    }
    else if (aux->next == NULL) // Eh o ultimo elemento
    {
        prev->next = aux->next;
        aux->prev = NULL;
    }
    else
    {
        printf("Seria o ultimo ou algum outro elemento!\n");
        prev->next = aux->next;
        aux->next->prev = prev;
    }
    printf("Ueh\n");
    free(aux);
    return l;
}

Lista *removerCelula(Lista *lista, Celula *c)
{
    Lista *prev = NULL, *aux = lista;
    while ((aux != NULL) && (aux->c->p.x != c->p.x) && (aux->c->p.y != c->p.y))
    {

        prev = aux;
        aux = aux->next;
    }
    if (aux == NULL) // Nao achou o elemento
        return lista;
    else if (prev == NULL) // Eh o primeiro elemento
    {
        lista = lista->next;
        if (lista != NULL)
            lista->prev = NULL;
    }
    else if (aux->next == NULL) // Eh o ultimo elemento
    {
        prev->next = aux->next;
        aux->prev = NULL;
    }
    else
    {
        prev->next = aux->next;
        aux->next->prev = prev;
    }
    free(aux);
    return lista;
}

void imprimir(Lista *l)
{
    Lista *aux = l;
    while (aux != NULL)
    {
        printf("X: %d\tY: %d\n", aux->c->p.x, aux->c->p.y);
        aux = aux->next;
    }
    printf("\n\n");
}

void imprimirVizinhosPonto(Lista *l)
{
    Lista *aux = l;
    while (aux != NULL)
    {
        printf("X: %d\tY: %d\n", aux->c->p.x, aux->c->p.y);
        aux = aux->next;
    }
    printf("\n\n");
}

int existe(Lista *l, Celula c)
{
    Lista *aux = l;
    while (aux != NULL)
    {
        // Como nao da para compara uma celula com outra, vou compara os f, g, h
        if ((aux->c->f == c.f) && (aux->c->g == c.g) && (aux->c->h == c.h))
            return 1;
        aux = aux->next;
    }
    return 0;
}

void adicionarVizinhos(Celula *spot, Celula ***grid, int colunas, int linhas)
{
    int i = spot->p.x;
    int j = spot->p.y;

    if (i < colunas - 1)
    {
        //spot.neighbors.push(grid[i + 1][j]);
        spot->vizinhos = inserirCelula(spot->vizinhos, grid[i + 1][j]);
    }
    if (i > 0)
    {
        //spot.neighbors.push(grid[i - 1][j]);
        spot->vizinhos = inserirCelula(spot->vizinhos, grid[i - 1][j]);
    }
    if (j < linhas - 1)
    {
        //spot.neighbors.push(grid[i][j + 1]);
        spot->vizinhos = inserirCelula(spot->vizinhos, grid[i][j + 1]);
    }
    if (j > 0)
    {
        //spot.neighbors.push(grid[i][j - 1]);
        spot->vizinhos = inserirCelula(spot->vizinhos, grid[i][j - 1]);
    }
}

Celula *procurarMenor(Lista *l)
{
    Lista *aux = l;
    double menorF = aux->c->f;
    Celula *menor = aux->c;
    aux = aux->next;
    while (aux != NULL)
    {
        if (aux->c->f < menorF)
        {
            menorF = aux->c->f;
            menor = aux->c;
        }
        aux = aux->next;
    }
    return menor;
}

int distancia(Ponto a, Ponto b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}

void heuristica(Celula *spot, Ponto inicio, Ponto fim)
{
    // Custo do inicio ateh o atual
    spot->g = round(distancia(spot->p, inicio));
    spot->h = round(distancia(spot->p, fim));
    spot->f = spot->g + spot->h;
}

int main()
{
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
    Lista *l = criar();
    Lista *lFechado = criar();
    l = inserirCelula(l, inicio);

    int contador = 0;
    while (l != NULL && contador <= 10)
    {
        Celula *temp = procurarMenor(l);
        printf("\nCelula: %d\t%d\n", temp->p.x, temp->p.y);
        l = removerCelula(l, temp);
        lFechado = inserirCelula(lFechado, temp);
        imprimirVizinhosPonto(l);
        Lista *aux = temp->vizinhos;
        while (aux != NULL)
        {
            heuristica(aux->c, inicio->p, destino->p);
            l = inserirCelula(l, aux->c);
            aux = aux->next;
        }
        if (temp->p.x == LINHA - 1 && temp->p.y == COLUNA - 1)
        {
            printf("\n\nDeu certo k777!!\n\n");
            break;
        }
        contador++;
    }

    for (i = 0; i < LINHA; i++)
    {
        for (j = 0; j < COLUNA; j++)
            free(grid[i][j]);
        free(grid[i]);
    }
    free(grid);

    return 0;
}