#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//ALTERAR
// Definição da estrutura de um nó (parada de ônibus)
typedef struct No {
    char nome[100];
    struct No *proximoNo;
    struct No *noAnterior;
} No;

// Definição da estrutura da lista duplamente encadeada
typedef struct ListaEncadeada {
    No *head;
    int tamanho;
} ListaEncadeada;

// Função para inserir uma parada de ônibus
void inserirParada(ListaEncadeada *l, char nome[], char paradaAnterior[]) {
    No *novaParada = (No *)malloc(sizeof(No));
    strcpy(novaParada->nome, nome);
    novaParada->proximoNo = NULL;
    novaParada->noAnterior = NULL;

    // Se a lista estiver vazia, inserir no início
    if (l->head == NULL) {
        l->head = novaParada;
    } else {
        No *nop = l->head;
        // Se for inserção no início
        if (strcmp(paradaAnterior, "") == 0) {
            novaParada->proximoNo = l->head;
            l->head->noAnterior = novaParada;
            l->head = novaParada;
        } else {
            // Procurar a parada anterior
            while (nop != NULL && strcmp(nop->nome, paradaAnterior) != 0) {
                nop = nop->proximoNo;
            }
            if (nop == NULL) {
                printf("Parada anterior não encontrada.\n");
                free(novaParada);
                return;
            }
            // Inserir a nova parada
            novaParada->proximoNo = nop->proximoNo;
            novaParada->noAnterior = nop;
            nop->proximoNo = novaParada;
            if (novaParada->proximoNo != NULL) {
                novaParada->proximoNo->noAnterior = novaParada;
            }
        }
    }
    l->tamanho++;
}

// Função para remover uma parada de ônibus pelo nome
void removerParada(ListaEncadeada *l, char nome[]) {
    No *nop = l->head;
    
    // Procurar a parada com o nome fornecido
    while (nop != NULL && strcmp(nop->nome, nome) != 0) {
        nop = nop->proximoNo;
    }

    if (nop == NULL) {
        printf("Parada não encontrada.\n");
        return;
    }

    // Se for a primeira parada
    if (nop == l->head) {
        l->head = nop->proximoNo;
        if (l->head != NULL) {
            l->head->noAnterior = NULL;
        }
    } else {
        nop->noAnterior->proximoNo = nop->proximoNo;
        if (nop->proximoNo != NULL) {
            nop->proximoNo->noAnterior = nop->noAnterior;
        }
    }
    
    free(nop);
    l->tamanho--;
}

// Função para imprimir o percurso de ida
void imprimirPercursoIda(ListaEncadeada *l) {
    if (l->head == NULL) {
        printf("Nenhuma parada na rota.\n");
        return;
    }
    No *nop = l->head;
    while (nop != NULL) {
        printf("%s ", nop->nome);
        nop = nop->proximoNo;
    }
    printf("\n");
}

// Função para imprimir o percurso de volta
void imprimirPercursoVolta(ListaEncadeada *l) {
    if (l->head == NULL) {
        printf("Nenhuma parada na rota.\n");
        return;
    }
    // Ir até o final da lista
    No *nop = l->head;
    while (nop->proximoNo != NULL) {
        nop = nop->proximoNo;
    }
    // Imprimir o percurso de volta
    while (nop != NULL) {
        printf("%s ", nop->nome);
        nop = nop->noAnterior;
    }
    printf("\n");
}

int main() {
    // Inicializando a lista de paradas
    ListaEncadeada paradas;
    paradas.head = NULL;
    paradas.tamanho = 0;

    // Inserindo paradas de ônibus
    inserirParada(&paradas, "Parada 1", "");
    inserirParada(&paradas, "Parada 2", "Parada 1");
    inserirParada(&paradas, "Parada 3", "Parada 2");
    inserirParada(&paradas, "Parada 4", "Parada 3");
    
    // Imprimindo o percurso na ida
    printf("Percurso de ida:\n");
    imprimirPercursoIda(&paradas);
    
    // Imprimindo o percurso na volta
    printf("\nPercurso de volta:\n");
    imprimirPercursoVolta(&paradas);

    // Removendo uma parada
    removerParada(&paradas, "Parada 2");

    // Imprimindo o percurso atualizado na ida
    printf("\nPercurso de ida (após remoção):\n");
    imprimirPercursoIda(&paradas);
    
    return 0;
}
