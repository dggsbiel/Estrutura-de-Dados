#include<stdio.h>
#include<stdlib.h>

int *pilha;
int referenciatopo=0;
int tamanhodapilha=5;

void Stack(){
    pilha = (int*)malloc(tamanhodapilha * sizeof(int));
    printf("pilha criada!\n");
}

void push(int *v, int *topo, int val){
    v[*topo] = val;
    *topo += 1;
    printf("valor adicionado!\n");
}

void pop(int *v, int *topo){
    printf("valor %d removido\n", v[*topo - 1]);
    *topo -= 1;
}

void isEmpty(int *topo, int tamMax){
    if(*topo < tamMax){
        printf("%d espaco(s) livre(s)!\n", tamMax - *topo);
    }else{
        printf("pilha cheia\n");
    }
}

void size(int *topo){
    printf("referencia topo:%d\n", *topo);
}

int* invertePilha(int *p1, int topo1) {
    int *p2 = (int*)malloc(topo1 * sizeof(int));  
    int topo2 = 0;

    for(int i = topo1 - 1; i >= 0; i--) {
        push(p2, &topo2, p1[i]); 
    }

    return p2;  
}
int main(){
    printf("programa iniciado!\n");
    Stack();

    push(pilha, &referenciatopo, 10);
    push(pilha, &referenciatopo, 20);
    push(pilha, &referenciatopo, 30);
    pop(pilha, &referenciatopo);
    isEmpty(&referenciatopo, tamanhodapilha);
    size(&referenciatopo);

    printf("Pilha original:\n");
    for(int i = 0; i < referenciatopo; i++){
        printf("pilha[%d] -> %d\n", i, pilha[i]);
    }

    int *pilhaInvertida = invertePilha(pilha, referenciatopo);  
    printf("Pilha invertida:\n");
    for(int i = 0; i < referenciatopo; i++){
        printf("pilhaInvertida[%d] -> %d\n", i, pilhaInvertida[i]);
    }
    
    return 0;
}