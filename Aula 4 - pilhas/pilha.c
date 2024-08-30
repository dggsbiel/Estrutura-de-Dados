//aula de pilhas
//LIFO(LAST IN,FIRST OUT)
//O PRIMEIRO A ENTRAR É O ULTIMO A SAIR
//PUSH() - PARA INSERIR ALGO
//POP() - PARA REMOVER ALGO DA PILHA
// !!!!SEMPRE É PRECISO TER ACESSO AO TOPO DA PILHA!!!!
//atividade:
//uma funcao pra criar;
//uma pra add;
//uma pra remover;
//uma pra verificar se está vazia;
//uma pra verificar se está cheia;

#include<stdio.h>

int *pilha;
int referenciatopo=0;
int tamanhodapilha=5;

void Stack();
void push();
void pop();
void isEmpty();
void size();


int main(){
    printf("programa iniciado!\n");
    Stack();

    push(pilha,&referenciatopo,10);
    push(pilha,&referenciatopo,20);
    push(pilha,&referenciatopo,30);
    pop(pilha,&referenciatopo);
    isEmpty(&referenciatopo,tamanhodapilha);
    size(&referenciatopo);
    
    for(int i=0;i <referenciatopo;i++){
        printf("pilha[%d] -> %d\n",i,pilha[i]);
    }
    
    return 0;
}


void Stack(){
pilha = (int*)malloc(tamanhodapilha*sizeof(int));
printf("pilha criada!\n");
}

void push(int *v,int *topo,int val){
    v[*topo]=val;
    *topo+=1;
    printf("valor adicionado!\n");
}

void pop(int *v,int *topo){
    printf("valor %d removido\n",v[*topo-1]);
    *topo+= -1;
}

void isEmpty(int *topo,int tamMax){
    if(*topo<tamMax){
        printf("%d espaco(s) livre(s)!\n",tamMax-*topo);
        return 0;
    }else{
        printf("pilha cheia");
        return 1;
    }

}

void size(int *topo){
printf("referencia topo:%d\n",*topo);
}