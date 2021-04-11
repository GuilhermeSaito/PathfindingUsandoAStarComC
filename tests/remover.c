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

void imprimir(Lista *l)
{
    Lista *aux = l;
    while (aux != NULL)
    {
        printf("X: %d\tY: %d\n", aux->c.p.x, aux->c.p.y);
        aux = aux->next;
    }
}

int main()
{
    Lista *l = criar();

    Ponto p1, p2, p3;
    p1.x = 1;
    p1.y = 2;
    p2.x = 10;
    p2.y = 20;
    p3.x = 100;
    p3.y = 200;

    l = inserir(l, p1);
    //l = inserir(l, p2);
    //l = inserir(l, p3);

    imprimir(l);

    l = remover(l, p1);

    imprimir(l);

    return 0;
}