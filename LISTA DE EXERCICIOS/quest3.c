#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *dados;
    int frente;
    int tras;
    int tamanho;
} Fila;


Fila* inicializaFila(int tamanho) {
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->tamanho = tamanho;
    f->frente = -1;
    f->tras = -1;
    f->dados = (int *)malloc(tamanho * sizeof(int));
    return f;
}


int adicionar(Fila *f, int valor) {
    if (f->tras == f->tamanho - 1) {
        return 0; 
    }
    if (f->frente == -1) {
        f->frente = 0; 
    }
    f->tras++;
    f->dados[f->tras] = valor;
    return 1;
}

int remover(Fila *f) {
    if (f->frente == -1) {
        return -1; 
    }
    int valor = f->dados[f->frente];
    f->frente++;
    if (f->frente > f->tras) {
        f->frente = -1; 
        f->tras = -1;
    }
    return valor;
}

Fila* intercalaFilas(Fila *F1, Fila *F2) {
    Fila *F3 = inicializaFila(F1->tamanho + F2->tamanho);
    
    while (F1->frente != -1 || F2->frente != -1) {
        if (F1->frente != -1) {
            adicionar(F3, remover(F1));
        }
        if (F2->frente != -1) {
            adicionar(F3, remover(F2));
        }
    }
    
    return F3;
}

void imprimeFila(Fila *f) {
    for (int i = f->frente; i <= f->tras; i++) {
        printf("%d ", f->dados[i]);
    }
    printf("\n");
}

int main() {
    Fila *F1 = inicializaFila(5);
    Fila *F2 = inicializaFila(5);
    
    adicionar(F1, 1);
    adicionar(F1, 3);
    adicionar(F1, 5);
    adicionar(F2, 2);
    adicionar(F2, 4);
    adicionar(F2, 6);
    adicionar(F2, 8);
    adicionar(F2, 10);

    Fila *F3 = intercalaFilas(F1, F2);

    printf("Fila intercalada: ");
    imprimeFila(F3);

    return 0;
}
