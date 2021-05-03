#include "lista.h"

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
    Lista *atual, *anterior;
    atual = lista;
    // Lista vazia. Retorna
    if (lista == NULL)
        return NULL;    

    anterior = NULL;
    while (atual)
    {        
        if (atual->c->p.x == c->p.x && atual->c->p.y == c->p.y)
        {
            if (anterior == NULL)                
            {
                // Remove um elemento do início da lista                  
                lista = lista->next; // Atualiza o início da lista
                free(atual);
                atual = lista;
                continue;                
            } else 
            {
                // Remove um elemento do meio ou final da lista
                anterior->next = atual->next;
                free(atual);                    
                atual = anterior; 
                continue;
            };
        };
        // Caminha para o próximo elemento
        anterior = atual;
        atual = atual->next;
    }
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