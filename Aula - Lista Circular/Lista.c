#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Musica {
    char titulo[50];
    char artista[50];
    int minutos;
    int segundos;
    struct Musica* proximo;
    struct Musica* anterior;
} Musica;

typedef struct {
    Musica* cabeca;
    int tamanho;
} ListaReproducao;

void inicializarLista(ListaReproducao* lista) {
    lista->cabeca = NULL;
    lista->tamanho = 0;
}

Musica* criarMusica(const char* titulo, const char* artista, int minutos, int segundos) {
    Musica* novaMusica = (Musica*)malloc(sizeof(Musica));
    strcpy(novaMusica->titulo, titulo);
    strcpy(novaMusica->artista, artista);
    novaMusica->minutos = minutos;
    novaMusica->segundos = segundos;
    novaMusica->proximo = novaMusica->anterior = novaMusica;
    return novaMusica;
}

void adicionarMusica(ListaReproducao* lista, const char* titulo, const char* artista, int minutos, int segundos) {
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
}

void removerMusica(ListaReproducao* lista, const char* titulo) {
    if (lista->cabeca == NULL) {
        printf("A lista de reprodução está vazia.\n");
        return;
    }
    Musica* atual = lista->cabeca;
    do {
        if (strcmp(atual->titulo, titulo) == 0) {
            if (atual->proximo == atual) {
                lista->cabeca = NULL;
            } else {
                atual->anterior->proximo = atual->proximo;
                atual->proximo->anterior = atual->anterior;
                if (atual == lista->cabeca) {
                    lista->cabeca = atual->proximo;
                }
            }
            free(atual);
            lista->tamanho--;
            printf("Música removida com sucesso!\n");
            return;
        }
        atual = atual->proximo;
    } while (atual != lista->cabeca);
    printf("Música não encontrada.\n");
}

void visualizarMusicas(ListaReproducao* lista) {
    if (lista->cabeca == NULL) {
        printf("Lista de reprodução vazia.\n");
        return;
    }
    Musica* atual = lista->cabeca;
    do {
        printf("Título: %s, Artista: %s, Duração: %02d:%02d\n", atual->titulo, atual->artista, atual->minutos, atual->segundos);
        atual = atual->proximo;
    } while (atual != lista->cabeca);
}

void limparLista(ListaReproducao* lista) {
    while (lista->tamanho > 0) {
        removerMusica(lista, lista->cabeca->titulo);
    }
}

void pesquisarMusica(ListaReproducao* lista, const char* titulo) {
    if (lista->cabeca == NULL) {
        printf("Lista de reprodução vazia.\n");
        return;
    }
    Musica* atual = lista->cabeca;
    do {
        if (strcmp(atual->titulo, titulo) == 0) {
            printf("Música encontrada: Título: %s, Artista: %s, Duração: %02d:%02d\n", atual->titulo, atual->artista, atual->minutos, atual->segundos);
            return;
        }
        atual = atual->proximo;
    } while (atual != lista->cabeca);
    printf("Música não encontrada.\n");
}

void ordenarMusicasPorTitulo(ListaReproducao* lista) {
    if (lista->tamanho < 2) return;
    Musica* atual;
    Musica* seguinte;
    char tempTitulo[50], tempArtista[50];
    int tempMinutos, tempSegundos;
    for (int i = 0; i < lista->tamanho - 1; i++) {
        atual = lista->cabeca;
        seguinte = atual->proximo;
        for (int j = 0; j < lista->tamanho - 1 - i; j++) {
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
            seguinte = seguinte->proximo;
        }
    }
}

int contarMusicas(ListaReproducao* lista) {
    return lista->tamanho;
}

int main() {
    ListaReproducao lista;
    inicializarLista(&lista);
    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Adicionar Música\n");
        printf("2. Remover Música\n");
        printf("3. Visualizar Músicas\n");
        printf("4. Limpar Lista\n");
        printf("5. Pesquisar Música\n");
        printf("6. Ordenar Músicas por Título\n");
        printf("7. Contar Músicas\n");
        printf("8. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer
        char titulo[50], artista[50];
        int minutos, segundos;
        switch (opcao) {
            case 1:
                printf("Digite o título da música: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                printf("Digite o artista: ");
                fgets(artista, sizeof(artista), stdin);
                artista[strcspn(artista, "\n")] = '\0';
                printf("Digite a duração (formato MM:SS): ");
                scanf("%d:%d", &minutos, &segundos);
                getchar(); // Limpar buffer
                adicionarMusica(&lista, titulo, artista, minutos, segundos);
                break;
            case 2:
                printf("Digite o título da música a remover: ");
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
                printf("Digite o título da música a pesquisar: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                pesquisarMusica(&lista, titulo);
                break;
            case 6:
                ordenarMusicasPorTitulo(&lista);
                printf("Músicas ordenadas por título.\n");
                break;
            case 7:
                printf("Total de músicas: %d\n", contarMusicas(&lista));
                break;
            case 8:
                limparLista(&lista);
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 8);
    return 0;
}
