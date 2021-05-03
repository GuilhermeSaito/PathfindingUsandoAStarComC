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
    int f;
    int g;
    int h;
    struct List *vizinhos;
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

Lista *inserirCelula(Lista *lista, Celula *c)
{
    Lista *novo = (Lista *)malloc(sizeof(Lista));
    novo->c = c;

    novo->next = lista;
    novo->prev = NULL;
    return novo;
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
    if (prev == NULL) // Eh o primeiro elemento
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
void imprimir(Lista *lista)
{
    Lista *aux = lista;
    while (aux != NULL)
    {
        printf("X: %d\tY: %d f: %d g: %d h: %d\n", aux->c->p.x, aux->c->p.y,aux->c->f,aux->c->g,aux->c->h);
        aux = aux->next;
    }
    printf("\n\n");
}

int existe(Lista *l, Celula *c)
{
   Lista *aux = l;
    while (aux != NULL)
    {
        // Como nao da para compara uma celula com outra, vou compara os potos
        if ((aux->c->p.x == c->p.x) && (aux->c->p.y == c->p.y))
            return 1;
        aux = aux->next;
    }
    return 0;
}

int main()
{
    Lista *l = criar();

    Celula *p1 = (Celula*)malloc(sizeof(Celula)); 
    Celula *p2 = (Celula*)malloc(sizeof(Celula)); ;
    Celula *p3 = (Celula*)malloc(sizeof(Celula)); ;
    p1->p.x = 1;
    p1->p.y = 2;
    p2->p.x = 10;
    p2->p.y = 20;
    p3->p.x = 100;
    p3->p.y = 200;

    l = inserirCelula(l, p1);
    l = inserirCelula(l, p2);
    l = inserirCelula(l, p3);

    imprimir(l);

    if (existe(l, p1))
        printf(":D\n");
    else
        printf("D:\n");

    l = removerCelula(l, p1);

    if (!existe(l, p1))
        printf(":D\n");
    else
        printf("D:\n");

    imprimir(l);

    return 0;
}