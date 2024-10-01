#include <stdio.h>
#include <stdlib.h>

typedef struct integer {
    int item;
    struct integer *next, *prev;
} Integer;

typedef Integer *P_i;

P_i criarNo(int valor) {
    P_i novo = (P_i)malloc(sizeof(Integer));
    novo->item = valor;
    novo->next = NULL;
    novo->prev = NULL;
    return novo;
}

void inserirValor(P_i *lista, int valor) {
    P_i novo = criarNo(valor);
    if (*lista == NULL) {
        *lista = novo;
    } else {
        P_i ultimo = *lista;
        while (ultimo->next != NULL) {
            ultimo = ultimo->next;
        }
        ultimo->next = novo;
        novo->prev = ultimo;
    }
}

void concatenaListas(P_i *lista1, P_i *lista2) {
    if (*lista1 == NULL) {
        *lista1 = *lista2;
        return;
    }

    if (*lista2 == NULL) {
        return;
    }

    Integer *ultimo = *lista1;
    while (ultimo->next != NULL) {
        ultimo = ultimo->next;
    }

    ultimo->next = *lista2;
    (*lista2)->prev = ultimo;
}

void imprimir(P_i lista) {
    Integer *atual = lista;
    while (atual != NULL) {
        printf("%d ", atual->item);
        atual = atual->next;
    }
    printf("\n");
}

int main() {
    
    P_i lista1 = NULL;
    P_i lista2 = NULL;

    inserirValor(&lista1, 10);
    inserirValor(&lista1, 15);
    inserirValor(&lista1, 20);
    inserirValor(&lista2, 25);
    inserirValor(&lista2, 30);
    inserirValor(&lista2, 35);

    printf("Lista 1: ");
    imprimir(lista1);
    printf("Lista 2: ");
    imprimir(lista2);
    concatenaListas(&lista1, &lista2);
    printf("Lista concatenada: ");
    imprimir(lista1);

    return 0;
}
