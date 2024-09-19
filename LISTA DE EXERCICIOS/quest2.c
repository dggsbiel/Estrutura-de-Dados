#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *caracteres; 
    int topo;         
    int capacidade;  
} Pilha;


void inicializaPilha(Pilha *p) {
    p->capacidade = 10; 
    p->topo = -1;
    p->caracteres = (char *)malloc(p->capacidade * sizeof(char));
}

int pilhaCheia(Pilha *p) {
    return p->topo == p->capacidade - 1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void aumentarCapacidade(Pilha *p) {
    p->capacidade *= 2;
    p->caracteres = (char *)realloc(p->caracteres, p->capacidade * sizeof(char));
}


int empilha(Pilha *p, char c) {
    if (pilhaCheia(p)) {
        aumentarCapacidade(p); 
    }
    p->caracteres[++(p->topo)] = c;
    return 1; 
}


char desempilha(Pilha *p) {
    if (!pilhaVazia(p)) {
        return p->caracteres[(p->topo)--];
    }
    return '\0'; 
}


void apagarTudo(Pilha *p) {
    p->topo = -1; 
}

void imprimePilha(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("Texto: (vazio)\n");
        return;
    }

    printf("Texto: ");
    for (int i = 0; i <= p->topo; i++) {
        printf("%c", p->caracteres[i]);
    }
    printf("\n");
}

int main() {
    Pilha p;
    inicializaPilha(&p);
    
    char comando[100];
    printf("Digite os caracteres (use '#' para backspace, '@' para apagar tudo, e '0' para sair):\n");

    while (1) {
        scanf(" %s", comando);

        for (int i = 0; i < strlen(comando); i++) {
            char c = comando[i];
            if (c == '#') {
                char removed = desempilha(&p);
                if (removed != '\0') {
                    printf("Caractere '%c' removido.\n", removed);
                } else {
                    printf("A pilha já está vazia!\n");
                }
            } else if (c == '@') {
                apagarTudo(&p);
                printf("Todos os caracteres apagados.\n");
            } else if (c == '0') {
                printf("Saindo...\n");
                return 0;
            } else {
                empilha(&p, c); 
            }
        }

        imprimePilha(&p); 
    }

    return 0;
}
