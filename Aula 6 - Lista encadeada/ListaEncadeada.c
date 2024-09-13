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

void inseririnicio(le *l, int val);
void inserirfim(le *l, int val);
void inserirno_meio(le *l, int val, int pos);
int imprimirLista(le *l);

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

    inserirno_meio(&lista1, 25, 0 ); 
    
    printf("Lista após inserção no meio:\n");
    imprimirLista(&lista1);

    return 0;
}

void inseririnicio(le *l, int val) {
    no *novono = (no *)malloc(sizeof(no));
    novono->valor = val;
    novono->proximoNo = l->head;
    l->head = novono;
    l->tamanho++;
}

void inserirfim(le *l, int val) {
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
    l->tamanho++;
}

void inserirno_meio(le *l, int val, int pos) {
    if (pos < 0 || pos > l->tamanho) {
        printf("Posição inválida.\n");
        return;
    }
    
    no *novono = (no *)malloc(sizeof(no));
    novono->valor = val;

    if (pos == 0) {
        novono->proximoNo = l->head;
        l->head = novono;
    } else {
        no *nop = l->head;
        for (int i = 0; i < pos - 1; i++) {
            nop = nop->proximoNo;
        }
        novono->proximoNo = nop->proximoNo;
        nop->proximoNo = novono;
    }
    l->tamanho++;
}

int imprimirLista(le *l) {
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
