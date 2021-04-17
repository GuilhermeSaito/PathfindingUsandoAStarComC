#include <stdio.h>
#include <stdlib.h>

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
    Celula c;
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
    novo->c.valor = 0;
    novo->c.p = elem;
    novo->c.f = 0.0;
    novo->c.g = 0.0;
    novo->c.h = 0.0;
    novo->c.vizinhos = criar();
    novo->c.anterior = NULL;
    novo->c.muro = 0;

    novo->next = lista;
    novo->prev = NULL;
    return novo;
}

Lista *inserirCelula(Lista *lista, Celula c)
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
    while ((aux != NULL) && (aux->c.p.x != elem.x) && (aux->c.p.y != elem.y))
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

Lista *removerCelula(Lista *lista, Celula c)
{
    Lista *prev = NULL, *aux = lista;
    while ((aux != NULL) && (aux->c.p.x != c.p.x) && (aux->c.p.y != c.p.y))
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
        printf("X: %d\tY: %d\n", aux->c.p.x, aux->c.p.y);
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
        if ((aux->c.f == c.f) && (aux->c.g == c.g) && (aux->c.h == c.h))
            return 1;
        aux = aux->next;
    }
    return 0;
}

int main()
{
    Lista *l = criar();

    Celula p1, p2, p3;
    p1.p.x = 1;
    p1.p.y = 2;
    p2.p.x = 10;
    p2.p.y = 20;
    p3.p.x = 100;
    p3.p.y = 200;

    l = inserirCelula(l, p1);
    l = inserirCelula(l, p2);
    l = inserirCelula(l, p3);

    imprimir(l);

    if (existe(l, p1))
        printf(":D\n");
    else
        printf("D:\n");

    l = removerCelula(l, p1);

    if (existe(l, p1))
        printf(":D\n");
    else
        printf("D:\n");

    imprimir(l);

    return 0;
}