#include <stdio.h>
#include <stdlib.h>

#define CAPACIDADE 10

typedef struct Node {
    int chave;
    int valor;
    struct Node* prox;
} Node;

Node* tabelaHash[CAPACIDADE];

void inicializarTabelaHash() {
    for (int i = 0; i < CAPACIDADE; i++) {
        tabelaHash[i] = NULL;
    }
}

void inserir(int chave, int valor) {
    int indice = funcaoHash(chave);
    Node* novoNode = (Node*)malloc(sizeof(Node));
    novoNode->chave = chave;
    novoNode->valor = valor;
    novoNode->prox = tabelaHash[indice];
    tabelaHash[indice] = novoNode;
}

int funcaoHash(int chave) {
    return chave % CAPACIDADE;
}

void imprimir() {
    for (int i = 0; i < CAPACIDADE; i++) {
        printf("Índice %d: ", i);
        Node* atual = tabelaHash[i];
        while (atual != NULL) {
            printf("[%d, %d] ", atual->chave, atual->valor);
            atual = atual->prox;
        }
        printf("\n");
    }
}

int main() {
    inicializarTabelaHash();
    inserir(1, 100);
    inserir(11, 200);
    inserir(21, 300);
    inserir(2, 400);
    imprimir();
    return 0;
}
