#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct No {
    char valor;
    struct No* prox;
} No;

typedef struct listaencadeada {
    No* head;
    int tamanho;
} le;

// Função para criar um novo nó
No* criarNo(char valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = NULL;
    return novo;
}

// Função para inicializar a lista encadeada
void inicializarLista(le* lista) {
    lista->head = NULL;
    lista->tamanho = 0;
}

// Função para inserir um valor no final da lista
void inserirNoFinal(le* lista, char valor) {
    No* novo = criarNo(valor);
    if (lista->head == NULL) {
        lista->head = novo;
    } else {
        No* temp = lista->head;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = novo;
    }
    lista->tamanho++; // Incrementa o tamanho
}

// Função para exibir os valores da lista
void exibirLista(le lista) {
    No* temp = lista.head;
    while (temp != NULL) {
        printf("%c", temp->valor);
        temp = temp->prox;
    }
    printf("\n");
}

// Função para verificar se o telefone já está formatado corretamente
int telefoneFormatadoCorreto(char* telefone) {
    if (telefone[0] == '(' && telefone[3] == ')' && telefone[4] == ' ' && telefone[10] == '-') {
        return 1; // Formato correto
    }
    return 0; // Formato incorreto
}

// Função para remover caracteres não numéricos
void removerNaoNumericos(char* telefoneLimpo, char* telefoneOriginal) {
    int j = 0;
    for (int i = 0; telefoneOriginal[i] != '\0'; i++) {
        if (isdigit(telefoneOriginal[i])) {
            telefoneLimpo[j++] = telefoneOriginal[i];
        }
    }
    telefoneLimpo[j] = '\0'; // Adiciona o terminador de string
}

// Função para formatar o número de telefone e inserir na lista
void formatarTelefone(char* telefone, le* lista) {
    if (telefoneFormatadoCorreto(telefone)) {
        for (int i = 0; telefone[i] != '\0'; i++) {
            inserirNoFinal(lista, telefone[i]);
        }
    } else {
        char telefoneLimpo[12];
        removerNaoNumericos(telefoneLimpo, telefone);

        inserirNoFinal(lista, '(');
        inserirNoFinal(lista, telefoneLimpo[0]);
        inserirNoFinal(lista, telefoneLimpo[1]);
        inserirNoFinal(lista, ')');
        inserirNoFinal(lista, ' ');
        for (int i = 2; i < 7; i++) {
            inserirNoFinal(lista, telefoneLimpo[i]);
        }
        inserirNoFinal(lista, '-');
        for (int i = 7; i < 11; i++) {
            inserirNoFinal(lista, telefoneLimpo[i]);
        }
    }
}

int main() {
    char telefone[20];
    le lista;
    inicializarLista(&lista); // Inicializa a lista

    while (1) {
        printf("Digite o telefone (formato com 11 dígitos ou (XX) XXXXX-XXXX) ou 'sair' para encerrar: ");
        scanf("%19[^\n]", telefone);
        getchar(); // Limpa o buffer do teclado

        if (strcmp(telefone, "sair") == 0) {
            break;
        }

        char telefoneLimpo[12];
        removerNaoNumericos(telefoneLimpo, telefone);

        if (strlen(telefoneLimpo) == 11) {
            formatarTelefone(telefone, &lista);
            printf("Telefone formatado: ");
            exibirLista(lista);
        } else {
            printf("Telefone inválido! Insira 11 dígitos ou no formato (XX) XXXXX-XXXX.\n");
        }
    }
    return 0;
}
