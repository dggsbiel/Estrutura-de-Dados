#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Musica {
    char titulo[50];
    char artista[50];
    int minutos;
    int segundos;
    struct Musica* prox;
    struct Musica* ant;
} Musica;

typedef struct listaencadeada{
    Musica* head;
    int tam;
} Lista;

void inicializarLista(Lista* lista) {
    lista->head = NULL;
    lista->tam = 0;
}

Musica* criarMusica(const char* titulo, const char* artista, int minutos, int segundos) {
    Musica* novaMusica = (Musica*)malloc(sizeof(Musica));
    strcpy(novaMusica->titulo, titulo);
    strcpy(novaMusica->artista, artista);
    novaMusica->minutos = minutos;
    novaMusica->segundos = segundos;
    novaMusica->prox = novaMusica->ant = novaMusica;
    return novaMusica;
}

void adicionarMusica(Lista* lista, const char* titulo, const char* artista, int minutos, int segundos) {
    Musica* novaMusica = criarMusica(titulo, artista, minutos, segundos);
    if (lista->head == NULL) {
        lista->head = novaMusica;
    } else {
        Musica* ultimo = lista->head->ant;
        ultimo->prox = novaMusica;
        novaMusica->ant = ultimo;
        novaMusica->prox = lista->head;
        lista->head->ant = novaMusica;
    }
    lista->tam++;
}

void removerMusica(Lista* lista, const char* titulo) {
    if (lista->head == NULL) {
        printf("A lista está vazia.\n");
        return;
    }
    Musica* atual = lista->head;
    do {
        if (strcmp(atual->titulo, titulo) == 0) {
            if (atual->prox == atual) {
                lista->head = NULL;
            } else {
                atual->ant->prox = atual->prox;
                atual->prox->ant = atual->ant;
                if (atual == lista->head) {
                    lista->head = atual->prox;
                }
            }
            free(atual);
            lista->tam--;
            printf("Música removida!\n");
            return;
        }
        atual = atual->prox;
    } while (atual != lista->head);
    printf("Música não encontrada.\n");
}

void visualizarMusicas(Lista* lista) {
    if (lista->head == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    Musica* atual = lista->head;
    do {
        printf("Título: %s, Artista: %s, Duração: %02d:%02d\n", atual->titulo, atual->artista, atual->minutos, atual->segundos);
        atual = atual->prox;
    } while (atual != lista->head);
}

void limparLista(Lista* lista) {
    while (lista->tam > 0) {
        removerMusica(lista, lista->head->titulo);
    }
}

void pesquisarMusica(Lista* lista, const char* titulo) {
    if (lista->head == NULL) {
        printf("Lista está vazia.\n");
        return;
    }
    Musica* atual = lista->head;
    do {
        if (strcmp(atual->titulo, titulo) == 0) {
            printf("Música encontrada: Título: %s, Artista: %s, Duração: %02d:%02d\n", atual->titulo, atual->artista, atual->minutos, atual->segundos);
            return;
        }
        atual = atual->prox;
    } while (atual != lista->head);
    printf("Música não encontrada.\n");
}

void ordenarMusicasPorTitulo(Lista* lista) {
    if (lista->tam < 2) return;
    Musica* atual;
    Musica* seguinte;
    char tempTitulo[50], tempArtista[50];
    int tempMinutos, tempSegundos;
    for (int i = 0; i < lista->tam - 1; i++) {
        atual = lista->head;
        seguinte = atual->prox;
        for (int j = 0; j < lista->tam - 1 - i; j++) {
            if (strcmp(atual->titulo, seguinte->titulo) > 0) {
                strcpy(tempTitulo, atual->titulo);
                strcpy(tempArtista, atual->artista);
                tempMinutos = atual->minutos;
                tempSegundos = atual->segundos;
                strcpy(atual->titulo, seguinte->titulo);
                strcpy(atual->artista, seguinte->artista);
                atual->minutos = seguinte->minutos;
                atual->segundos = seguinte->segundos;
                strcpy(seguinte->titulo, tempTitulo);
                strcpy(seguinte->artista, tempArtista);
                seguinte->minutos = tempMinutos;
                seguinte->segundos = tempSegundos;
            }
            atual = seguinte;
            seguinte = seguinte->prox;
        }
    }
}

int contarMusicas(Lista* lista) {
    return lista->tam;
}

int main() {
    Lista lista;
    inicializarLista(&lista);
    int opcao;
    do {
        printf("\n==============\n");
        printf("MENU PRINCIPAL\n");
        printf("==============\n");
        printf("1-Adicionar Música\n");
        printf("2-Remover Música\n");
        printf("3-Visualizar Músicas\n");
        printf("4-Limpar Lista\n");
        printf("5-Pesquisar Música\n");
        printf("6-Ordenar Músicas por Título\n");
        printf("7-Contar Músicas\n");
        printf("8-Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); 
        char titulo[50], artista[50];
        int minutos, segundos;
        switch (opcao) {
            case 1:
                printf("Título da música: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                printf("Artista: ");
                fgets(artista, sizeof(artista), stdin);
                artista[strcspn(artista, "\n")] = '\0';
                printf("Duração: ");
                scanf("%d:%d", &minutos, &segundos);
                getchar();
                adicionarMusica(&lista, titulo, artista, minutos, segundos);
                break;
            case 2:
                printf("Título da música para a remoção: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                removerMusica(&lista, titulo);
                break;
            case 3:
                visualizarMusicas(&lista);
                break;
            case 4:
                limparLista(&lista);
                printf("Lista de reprodução limpa.\n");
                break;
            case 5:
                printf("Pesquisar música: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                pesquisarMusica(&lista, titulo);
                break;
            case 6:
                ordenarMusicasPorTitulo(&lista);
                printf("Músicas ordenadas.\n");
                break;
            case 7:
                printf("Total de músicas: %d\n", contarMusicas(&lista));
                break;
            case 8:
                limparLista(&lista);
                printf("VALEU!!!\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 8);
    return 0;
}