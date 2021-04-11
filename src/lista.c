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

Ponto procurarElementoF(Lista *l, Ponto f)
{
    Lista *aux = l;
    while (aux != NULL)
    {
        if (aux->c.p.x == f.x && aux->c.p.y == f.y)
            return aux->c.p;
        aux = aux->next;
    }
    printf("Nao achei o elmento na lista\n");
    Ponto temp;
    temp.x = 0.0;
    temp.y = 0.0;
    return temp;
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

Celula procurarMenor(Lista *l)
{
    Lista *aux = l;
    double menorF = aux->c.f;
    Celula menor = aux->c;
    aux = aux->next;
    while (aux != NULL)
    {
        if (aux->c.f < menorF)
        {
            menorF = aux->c.f;
            menor = aux->c;
        }

        aux = aux->next;
    }
    return menor;
}

int menorElementoF(Lista *l)
{
    Lista *aux = l;
    double menor = aux->c.f;
    aux = aux->next;
    while (aux != NULL)
    {
        if (aux->c.f < menor)
            menor = aux->c.f;
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