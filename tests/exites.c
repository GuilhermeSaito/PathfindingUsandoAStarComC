
#include "../src/AlgoritmoAStar.h"
#include "../src/lista.h"
#include <stdio.h>
#include <stdlib.h> 

int main() {
    printf("Novo Teste: \n");

    Celula *celula1 = (Celula *)malloc(sizeof(Celula));
    Celula *celula2 = (Celula *)malloc(sizeof(Celula));
    Celula *celula3 = (Celula *)malloc(sizeof(Celula));
    Celula *celula4 = (Celula *)malloc(sizeof(Celula));

    celula1->p.x = 1;
    celula1->p.y = 1;

    celula1->p.x = 2;
    celula1->p.y = 2;

    celula1->p.x = 3;
    celula1->p.y = 3;

    celula1->p.x = 4;
    celula1->p.y = 4;

    Lista *aberta = criar();
    aberta = inserirCelula(aberta,celula1);
    aberta = inserirCelula(aberta,celula2);
    aberta = inserirCelula(aberta,celula3);
    aberta = inserirCelula(aberta,celula4);
    

    if(!existe(aberta,celula3)){
        printf("0 falhou 1 \n");
        return 0;
    }

    Lista *aux = aberta; 
    while (aux != NULL)
    {
        printf("%d %d \n",aux->c->p.x ,aux->c->p.y) ;
        /* code */
        aux = aux->next;
    }
     printf("\n\n\n") ;
    aberta = removerCelula(aberta,celula3);

    aux = aberta; 
    while (aux != NULL)
    {
        printf("%d %d \n",aux->c->p.x ,aux->c->p.y) ;
        /* code */
        aux = aux->next;
    }

    //ou a função remover não está funcionando ou
    // a função existe esta com problemas
    if(existe(aberta,celula3)){
        printf("0 falhou 2 \n");
        return 0;
    }else{
        printf("1 passou! \n");
        return 1;
    }
}