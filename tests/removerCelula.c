/**
 * 
 *  Curso: Engenharia da Computação - Universidade Técnologica Federal do Paraná
 *  Tema: Pathfinding A*
 *  Autores: Matheus de Camargo Marques , Guilherme Saito , Carolina Fernandes
 * 
 *  @link Repositorio https://github.com/GuilhermeSaito/PathfindingUsandoAStarComC
 *  @copyright - Livre para fim didáticos.
 */

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

Lista *inserirCelula(Lista *lista, Celula c)
{
    Lista *novo = (Lista *)malloc(sizeof(Lista));
    novo->c = c;

    novo->next = lista;
    novo->prev = NULL;
    return novo;
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

    l = removerCelula(l, p1);

    imprimir(l);

    return 0;
}