#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int dado;
    struct no* proximono;
} no;


no* criarno(int dado);
void inserir(lista* l, int dado);
void imprimirlista(lista* l);

int main() {
    lista lista1;
    lista1.cabeca = NULL;  // Inicializa a cabeca como NULL
    lista1.tamanho = 0;     // Inicializa o tamanho como 0

    // Adiciona elementos à lista
    inserir(&lista1, 10);
    inserir(&lista1, 20);
    
    // Imprime a lista
    imprimirlista(&lista1);
    
    return 0;
}

no* criarno(int dado) {
    no* novono = (no*)malloc(sizeof(no));
    novono->dado = dado;
    novono->proximono = novoNo;
    return novono;
}

void imprimirlista(lista* l) {
    if (l->cabeca == NULL) return; // Verifica se a lista está vazia

    no* temp = l->cabeca;
    do {
        printf("%d\n", temp->dado);
        temp = temp->proximono;
    } while (temp != l->cabeca);
}

void inserir(lista* l, int val) {
    no* novono = criarno(val);
    if (l->cabeca != NULL) {
        novono->proximono = l->cabeca;

        no* temp = l->cabeca;
        while (temp->proximono != l->cabeca) {
            temp = temp->proximono;
        }
        temp->proximono = novono;
    } else {
        l->cabeca = novono;
        novono->proximono = l->cabeca;
    }
    l->tamanho++;
}

void inserirFim(no** cabeca, int dado){
    No* novoNo = criarNo(dado);
    if (*cabeca == NULL){
        *cabeca = novoNo;
    } else {
        No* temp = *cabeca;
        while (temp->proximo != *cabeca){
            temp->proximo = novoNo;
            novoNo->proximo = *cabeca; 
        }
    }
}