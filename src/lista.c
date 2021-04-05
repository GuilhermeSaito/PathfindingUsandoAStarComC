#include "lista.h"

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
    novo->c.anterior = 0;
    novo->c.muro = 0;

    novo->next = lista;
    novo->prev = NULL;
    return novo;
}

/*Função para remover um elemento da lista encadeada em qq posição!*/
Lista *remover(Lista *l, Ponto elem)
{
    Lista *prev = NULL, *aux = l;
    while ((aux != NULL) && (aux->c.p.x != elem.x) && (aux->c.p.y != elem.y))
    {
        prev = aux;
        aux = aux->next;
    }
    if (aux == NULL)
    {
        printf("Nao achou o elemento a remover na lista\n");
        return l;
    }
    else if (prev == NULL)
    {
        l = l->next;
        l->prev = NULL;
    }
    else
    {
        prev->next = aux->next;
        aux->next->prev = prev;
    }
    free(aux);
    return l;
}

Ponto procurarElementoF(Lista *l, double f)
{
    Lista *aux = l;
    while (aux != NULL)
    {
        if (aux->c.f == f)
            return aux->c.p;
        aux = aux->next;
    }
    printf("Nao achei o elemnto: %lf\tNa lista\n", f);
    Ponto temp;
    temp.x = 0.0;
    temp.y = 0.0;
    return temp;
}

int maiorElementoF(Lista *l)
{
    Lista *aux = l;
    double maior = aux->c.f;
    aux = aux->next;
    while (aux != NULL)
    {
        if (aux->c.f > maior)
            maior = aux->c.f;
        aux = aux->next;
    }
    return maior;
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
    Lista *v; /*var. para percorrer a lista*/
    for (v = lista; v != NULL; v = v->next)
    {
        printf("Valor X: %d\n", v->c.p.x);
        printf("Valor Y: %d\n", v->c.p.y);
    }
}

/*Função para desalocar uma lista encadeda!*/
void liberar(Lista *l)
{
    Lista *aux;
    while (l != NULL)
    {
        aux = l->next;
        free(l);
        l = aux;
    }
}