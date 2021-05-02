#include "lista.h"

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

int tamanho(Lista *l)
{
    int cont = 0;
    Lista *aux = NULL;
    for (aux = l; aux != NULL; aux = aux->next)
        cont++;
    return cont;
}

int vazio(Lista *l)
{
    return l == NULL;
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