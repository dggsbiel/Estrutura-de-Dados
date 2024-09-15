#include <stdio.h>
#include <stdlib.h> 

typedef struct No {
    int valor;
    struct No *proximoNo;
} no;

typedef struct listaencadeada {
    no *head;
    int tamanho;
} le;

void inseririnicio(le *l, int val) {
    printf("Inserindo %d no início\n", val);
    no *novono = (no *)malloc(sizeof(no));
    novono->valor = val;
    novono->proximoNo = l->head;
    l->head = novono;
}

void inserirmeio(le *l,int val,int ref){
    printf("inserindo %d no meio\n");
    no *novono=(no*)malloc(sizeof(no));

    no *nop=l->head;
    while(nop->valor!=ref && nop->proximoNo!=NULL){
        nop=nop->proximoNo;
    }
    novono->proximoNo= nop->proximoNo;
    nop->proximoNo=novono;
    novono->valor = val;

}

void inserirfim(le *l, int val) {
    printf("Inserindo %d no fim\n", val);
    no *novono = (no *)malloc(sizeof(no));
    novono->valor = val;
    novono->proximoNo = NULL;

    if (l->head == NULL) {
        l->head = novono;
    } else {
        no *nop = l->head;
        while (nop->proximoNo != NULL) {
            nop = nop->proximoNo;
        }
        nop->proximoNo = novono;
    }
}

void removerno(le *l, int ref) {
    printf("Removendo nó com valor %d\n", ref);
    no *nop = l->head;
    no *noant = NULL;

    while (nop != NULL && nop->valor != ref) {
        noant = nop;
        nop = nop->proximoNo;
    }

    if (nop != NULL) {
        if (nop == l->head) {
            l->head = nop->proximoNo;
        } else {
            noant->proximoNo = nop->proximoNo;
        }
        free(nop);
    } else {
        printf("Referência %d não encontrada.\n", ref);
    }
}

int imprimirLista(le *l) {
    printf("Imprimindo valores\n");
    if (l->head == NULL) {
        printf("Nenhum nó na lista\n");
        return 0;
    } else {
        no *nop = l->head;
        while (nop != NULL) {
            printf("%d\n", nop->valor);
            nop = nop->proximoNo;
        }
        return 1;
    }
}

int main() {
    le lista1;
    lista1.head = NULL;
    lista1.tamanho = 0;

    inseririnicio(&lista1, 10);
    inseririnicio(&lista1, 20);
    inseririnicio(&lista1, 30);
    inseririnicio(&lista1, 40);
    inserirfim(&lista1, 5);
    inserirfim(&lista1, 4);
    
    imprimirLista(&lista1);
    inserirmeio(&lista1, 100, 20);
    imprimirLista(&lista1);
    removerno(&lista1, 40);
    removerno(&lista1, 30);
    imprimirLista(&lista1);

    return 0;
}
