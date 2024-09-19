#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *pilha;    
    int referenciatopo;  
    int tamanhodapilha;  
} Pilha;

void Stack(Pilha *p) {
    p->tamanhodapilha = 10;  
    p->referenciatopo = 0;
    p->pilha = (char *)malloc(p->tamanhodapilha * sizeof(char));
    printf("pilha criada!\n");
}

int isFull(Pilha *p) {
    return p->referenciatopo == p->tamanhodapilha;
}

int isEmpty(Pilha *p) {
    return p->referenciatopo == 0;
}

void aumentarTamanhoManual(Pilha *p) {
    int novoTamanho = p->tamanhodapilha * 2;
    char *novaPilha = (char *)malloc(novoTamanho * sizeof(char));  
    for (int i = 0; i < p->referenciatopo; i++) {
        novaPilha[i] = p->pilha[i];  
    }
    
    p->pilha = novaPilha;  
    p->tamanhodapilha = novoTamanho;  
    printf("tamanho da pilha aumentado para %d!\n", p->tamanhodapilha);
}

void push(Pilha *p, char c) {
    if (isFull(p)) {
        aumentarTamanhoManual(p); 
    }
    p->pilha[(p->referenciatopo)++] = c;
}

char pop(Pilha *p) {
    if (!isEmpty(p)) {
        return p->pilha[--(p->referenciatopo)];
    }
    return '\0'; 
}

void apagarTudo(Pilha *p) {
    p->referenciatopo = 0; 
    printf("todos os valores apagados!\n");
}

void imprimePilha(Pilha *p) {
    if (isEmpty(p)) {
        printf("Texto: (vazio)\n");
        return;
    }

    printf("Texto: ");
    for (int i = 0; i < p->referenciatopo; i++) {
        printf("%c", p->pilha[i]);
    }
    printf("\n");
}

int main() {
    Pilha p;
    Stack(&p);
    
    char comando[100];
    printf("Digite os caracteres (use '#' para backspace, '@' para apagar tudo, e '0' para sair):\n");

    while (1) {
        scanf(" %s", comando);

        for (int i = 0; i < strlen(comando); i++) {
            char c = comando[i];
            if (c == '#') {
                char removido = pop(&p);
                if (removido != '\0') {
                    printf("Caractere '%c' removido.\n", removido);
                } else {
                    printf("A pilha já está vazia!\n");
                }
            } else if (c == '@') {
                apagarTudo(&p);
            } else if (c == '0') {
                printf("Saindo...\n");
                return 0;
            } else {
                push(&p, c); 
            }
        }

        imprimePilha(&p); 
    }

    return 0;
}
