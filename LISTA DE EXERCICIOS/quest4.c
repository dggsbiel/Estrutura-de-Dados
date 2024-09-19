#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int queue[MAX];
    int inicio;
    int fim;
} Fila;


void inicializaFila(Fila *f) {
    f->inicio = 2; 
    f->fim = 2;    
    printf("Fila inicializada!\n");
}

int enfileira(Fila *f, int valor) {
    if (f->fim >= MAX) {
        printf("Fila cheia! Não é possível enfileirar.\n");
        return 0; 
    }
    f->queue[f->fim] = valor;
    f->fim++;
    printf("Valor %d enfileirado!\n", valor);
    return 1; 
}

int desenfileira(Fila *f) {
    if (f->inicio == f->fim) {
        printf("Fila vazia! Não é possível desenfileirar.\n");
        return -1; 
    }
    int valor = f->queue[f->inicio];
    f->inicio++;
    printf("Valor %d desenfileirado!\n", valor);
    return valor; 
}

int filaVazia(Fila *f) {
    return f->inicio == f->fim;
}


void imprimeFila(Fila *f) {
    if (filaVazia(f)) {
        printf("A fila está vazia!\n");
        return;
    }
    printf("Elementos da fila: ");
    for (int i = f->inicio; i < f->fim; i++) {
        printf("%d ", f->queue[i]);
    }
    printf("\n");
}

int main() {
    Fila f;
    inicializaFila(&f);

    enfileira(&f, 10);
    enfileira(&f, 20);
    enfileira(&f, 30);
    imprimeFila(&f);
    desenfileira(&f);
    imprimeFila(&f);
    desenfileira(&f);
    desenfileira(&f);
    desenfileira(&f); 

    return 0;
}
