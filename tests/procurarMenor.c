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
    struct Spot *anterior;
    int muro;
} Celula;

typedef struct List
{
    Celula *c;
    struct List *next;
    struct List *prev;
} Lista;

Lista *inserirCelula(Lista *lista, Celula *c)
{
    Lista *novo = (Lista *)malloc(sizeof(Lista));
    novo->c = c;

    novo->next = lista;
    novo->prev = NULL;
    return novo;
}

/*Função para imprimir uma lista encadeada!*/
void imprimir(Lista *lista)
{
    Lista *aux = lista;
    while (aux != NULL)
    {
        printf("X: %d\tY: %d\n", aux->c->p.x, aux->c->p.y);
        aux = aux->next;
    }
    printf("\n\n");
}

/*Função para desalocar uma lista encadeda!*/
void liberar(Lista *l)
{
    Lista *aux;
    while (l != NULL)
    {
        aux = l->next;
        l->next = NULL;
        l->prev = NULL;
        free(l);
        l = aux;
    }
}

Celula *procurarMenor(Lista *l)
{
    Lista *aux = l->next;
    double menorF = l->c->f;
    Celula *menor = l->c;
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

int main(){
    Lista* l = NULL;
    Celula* c1 = (Celula*)malloc(sizeof(Celula));
    c1->p.x = 10;
    c1->p.y = 10;
    c1->valor = 10;
    c1->f = 10;
    Celula* c2 = (Celula*)malloc(sizeof(Celula));
    c2->p.x = 20;
    c2->p.y = 20;
    c2->valor = 20;
    c2->f = 20;
    Celula* c3 = (Celula*)malloc(sizeof(Celula));
    c3->p.x = 30;
    c3->p.y = 30;
    c3->valor = 30;
    c3->f = 30;
    Celula* c4 = (Celula*)malloc(sizeof(Celula));
    c4->p.x = 40;
    c4->p.y = 40;
    c4->valor = 40;
    c4->f = 40;

    l = inserir (l, c1);
    l = inserir (l, c2);
    l = inserir (l, c3);
    l = inserir (l, c4);

    printf ("Menor elemento F: %f\n", procurarMenor(l)->f);
    c1->f = 60;
    printf ("Menor elemento F: %f\n", procurarMenor(l)->f);

    free (c1);
    free (c2);
    free (c3);
    free (c4);
    liberar(l);

    return 0;
}