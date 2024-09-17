#include <stdio.h>
#include <stdlib.h> 

typedef struct No {
    int valor;
    struct No *proximoNo;
    struct No *anteriorNo;
} no;

typedef struct listaencadeada {
    no *head;
    no *tail;
    int tamanho;
} le;

void inseririnicio(le *l, int val) {
    printf("Inserindo %d no início\n", val);
    no *novono = (no *)malloc(sizeof(no));
    novono->valor = val;
    novono->proximoNo = l->head;
    novono->anteriorNo = NULL;

    if (l->head != NULL){
        l->head->anteriorNo = novono;
    }
    l->head = novono;

    if (l->tail == NULL){
        l->tail = novono;
    }
    l->tamanho++;
}

void inserirmeio(le *l, int val, int ref) {
    printf("Inserindo %d no meio\n", val); 
    no *novono = (no *)malloc(sizeof(no));
    novono->valor = val;
    no *nop = l->head;

    while (nop != NULL && nop->valor != ref) { 
        nop = nop->proximoNo;
    }

    if (nop != NULL) {
        novono->proximoNo = nop->proximoNo;
        novono->anteriorNo = nop;
        if (nop->proximoNo != NULL) {
            nop->proximoNo->anteriorNo = novono;
        }
        nop->proximoNo = novono;
        if (l->tail == nop) {
            l->tail = novono;
        }
        l->tamanho++;
    } else {
        printf("Referência %d não encontrada\n", ref);
    }
}

void inserirfim(le *l, int val) {
    printf("Inserindo %d no fim\n", val);
    no *novono = (no *)malloc(sizeof(no));
    novono->valor = val;
    novono->proximoNo = NULL;
    novono->anteriorNo = l->tail;

    if (l->tail != NULL) {
        l->tail->proximoNo = novono;
    }
    l->tail = novono;

    if (l->head == NULL) {
        l->head = novono;
    }
    l->tamanho++;
}

void removerno(le *l, int ref) {
    printf("Removendo nó com valor %d\n", ref);
    no *nop = l->head;

    while (nop != NULL && nop->valor != ref) {
        nop = nop->proximoNo;
    }

    if (nop != NULL) {
        if (nop->anteriorNo != NULL) {
            nop->anteriorNo->proximoNo = nop->proximoNo;
        } else {
            l->head = nop->proximoNo;
        }
        if (nop->proximoNo != NULL) {
            nop->proximoNo->anteriorNo = nop->anteriorNo;
        } else {
            l->tail = nop->anteriorNo;
        }
        l->tamanho--;
    } else {
        printf("Nó com valor %d não encontrado\n", ref);
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
    lista1.tail = NULL;
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
