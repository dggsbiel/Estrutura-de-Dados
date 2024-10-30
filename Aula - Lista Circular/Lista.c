#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Musica {
    char titulo[50];
    char artista[50];
    int minutos;
    int segundos;
    struct Musica* anterior;
    struct Musica* proximo;
} Musica;

typedef struct Lista {
    Musica* cabeca;
    int tamanho;
} Lista;

Musica* criarMusica(char* titulo, char* artista, int minutos, int segundos) {
    Musica* novaMusica = (Musica*)malloc(sizeof(Musica));
    strcpy(novaMusica->titulo, titulo);
    strcpy(novaMusica->artista, artista);
    novaMusica->minutos = minutos;
    novaMusica->segundos = segundos;
    novaMusica->anterior = novaMusica->proximo = novaMusica;
    return novaMusica;
}

void adicionarMusica(Lista* lista, char* titulo, char* artista, int minutos, int segundos) {
    Musica* novaMusica = criarMusica(titulo, artista, minutos, segundos);
    if (lista->cabeca == NULL) {
        lista->cabeca = novaMusica;
    } else {
        Musica* ultimo = lista->cabeca->anterior;
        ultimo->proximo = novaMusica;
        novaMusica->anterior = ultimo;
        novaMusica->proximo = lista->cabeca;
        lista->cabeca->anterior = novaMusica;
    }
    lista->tamanho++;
    printf("Musica '%s' adicionada com sucesso.\n", titulo);
}

void removerMusica(Lista* lista, char* titulo) {
    if (lista->cabeca == NULL) {
        printf("A lista de reprodução está vazia.\n");
        return;
    }
    Musica* atual = lista->cabeca;
    do {
        if (strcmp(atual->titulo, titulo) == 0) {
            if (atual == lista->cabeca && lista->tamanho == 1) {
                lista->cabeca = NULL;
            } else {
                if (atual == lista->cabeca) {
                    lista->cabeca = lista->cabeca->proximo;
                }
                atual->anterior->proximo = atual->proximo;
                atual->proximo->anterior = atual->anterior;
            }
            free(atual);
            lista->tamanho--;
            printf("Musica '%s' removida.\n", titulo);
            return;
        }
        atual = atual->proximo;
    } while (atual != lista->cabeca);
    printf("Musica '%s' não encontrada.\n", titulo);
}

void visualizarMusicas(Lista* lista) {
    if (lista->cabeca == NULL) {
        printf("A lista de reprodução está vazia.\n");
        return;
    }
    Musica* atual = lista->cabeca;
    do {
        printf("Titulo: %s | Artista: %s | Duracao: %02d:%02d\n",
               atual->titulo, atual->artista, atual->minutos, atual->segundos);
        atual = atual->proximo;
    } while (atual != lista->cabeca);
}

void limparLista(Lista* lista) {
    while (lista->cabeca != NULL) {
        removerMusica(lista, lista->cabeca->titulo);
    }
    printf("Lista de reprodução limpa.\n");
}

void pesquisarMusica(Lista* lista, char* titulo) {
    if (lista->cabeca == NULL) {
        printf("A lista de reprodução está vazia.\n");
        return;
    }
    Musica* atual = lista->cabeca;
    do {
        if (strcmp(atual->titulo, titulo) == 0) {
            printf("Musica encontrada: %s - %s | Duracao: %02d:%02d\n",
                   atual->titulo, atual->artista, atual->minutos, atual->segundos);
            return;
        }
        atual = atual->proximo;
    } while (atual != lista->cabeca);
    printf("Musica '%s' não encontrada.\n", titulo);
}

void ordenarMusicas(Lista* lista) {
    if (lista->cabeca == NULL || lista->tamanho == 1) return;

    Musica* i = lista->cabeca;
    do {
        Musica* j = i->proximo;
        while (j != lista->cabeca) {
            if (strcmp(i->titulo, j->titulo) > 0) {
                char tempTitulo[50], tempArtista[50];
                int tempMinutos, tempSegundos;

                strcpy(tempTitulo, i->titulo);
                strcpy(tempArtista, i->artista);
                tempMinutos = i->minutos;
                tempSegundos = i->segundos;

                strcpy(i->titulo, j->titulo);
                strcpy(i->artista, j->artista);
                i->minutos = j->minutos;
                i->segundos = j->segundos;

                strcpy(j->titulo, tempTitulo);
                strcpy(j->artista, tempArtista);
                j->minutos = tempMinutos;
                j->segundos = tempSegundos;
            }
            j = j->proximo;
        }
        i = i->proximo;
    } while (i->proximo != lista->cabeca);
    printf("Músicas ordenadas por título.\n");
}

int contarMusicas(Lista* lista) {
    return lista->tamanho;
}

int main() {
    Lista lista;
    lista.cabeca = NULL;
    lista.tamanho = 0;

    int opcao;
    char titulo[50], artista[50];
    int minutos, segundos;

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar Música\n");
        printf("2. Remover Música\n");
        printf("3. Visualizar Todas as Músicas\n");
        printf("4. Limpar Lista\n");
        printf("5. Pesquisar Música por Título\n");
        printf("6. Ordenar Músicas por Título\n");
        printf("7. Contar Músicas\n");
        printf("8. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Digite o título da música: ");
                fgets(titulo, 50, stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                printf("Digite o artista: ");
                fgets(artista, 50, stdin);
                artista[strcspn(artista, "\n")] = '\0';
                printf("Digite a duração (minutos e segundos): ");
                scanf("%d %d", &minutos, &segundos);
                adicionarMusica(&lista, titulo, artista, minutos, segundos);
                break;
            case 2:
                printf("Digite o título da música para remover: ");
                fgets(titulo, 50, stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                removerMusica(&lista, titulo);
                break;
            case 3:
                visualizarMusicas(&lista);
                break;
            case 4:
                limparLista(&lista);
                break;
            case 5:
                printf("Digite o título da música para pesquisar: ");
                fgets(titulo, 50, stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                pesquisarMusica(&lista, titulo);
                break;
            case 6:
                ordenarMusicas(&lista);
                break;
            case 7:
                printf("Total de músicas: %d\n", contarMusicas(&lista));
                break;
            case 8:
                printf("Saindo...\n");
                limparLista(&lista);
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 8);

    return 0;
}
