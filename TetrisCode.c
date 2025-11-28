#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CAPACIDADE_MAX 5

typedef struct {
    char nome;
    int id;
} Peca;

typedef struct {
    Peca itens[CAPACIDADE_MAX];
    int inicio;
    int fim;
    int quantidade;
} FilaCircular;

int idGlobalCounter = 0;

Peca gerarPeca();
void inicializarFila(FilaCircular *f);
int filaCheia(FilaCircular *f);
int filaVazia(FilaCircular *f);
void enfileirar(FilaCircular *f);
void desenfileirar(FilaCircular *f);
void exibirFila(FilaCircular *f);
void limparBuffer();

int main() {
    srand(time(NULL));

    FilaCircular filaDePecas;
    int opcao = -1;

    inicializarFila(&filaDePecas);

    printf("--- SISTEMA INICIALIZADO ---\n");
    while (!filaCheia(&filaDePecas)) {
        enfileirar(&filaDePecas);
    }

    do {
        exibirFila(&filaDePecas);

        printf("\n--- ByteBros Control Center ---\n");
        printf("1. Jogar peça atual (Dequeue)\n");
        printf("2. Inserir nova peça (Enqueue)\n");
        printf("0. Sair\n");
        printf("Escolha uma ação: ");

        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
        }
        limparBuffer();

        switch (opcao) {
            case 1:
                desenfileirar(&filaDePecas);
                break;
            case 2:
                enfileirar(&filaDePecas);
                break;
            case 0:
                printf("Encerrando sistema Tetris Stack...\n");
                break;
            default:
                printf("\n[ERRO] Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

Peca gerarPeca() {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    
    nova.nome = tipos[rand() % 4];
    nova.id = idGlobalCounter++;
    
    return nova;
}

void inicializarFila(FilaCircular *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

int filaCheia(FilaCircular *f) {
    return (f->quantidade == CAPACIDADE_MAX);
}

int filaVazia(FilaCircular *f) {
    return (f->quantidade == 0);
}

void enfileirar(FilaCircular *f) {
    if (filaCheia(f)) {
        printf("\n[AVISO] A fila está cheia! Jogue uma peça antes de adicionar outra.\n");
        return;
    }

    Peca p = gerarPeca();

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % CAPACIDADE_MAX;
    f->quantidade++;
    
    printf("\n>>> Nova peça gerada e inserida: [%c %d]\n", p.nome, p.id);
}

void desenfileirar(FilaCircular *f) {
    if (filaVazia(f)) {
        printf("\n[ERRO] Fila vazia! Nenhuma peça para jogar.\n");
        return;
    }

    Peca p = f->itens[f->inicio];

    f->inicio = (f->inicio + 1) % CAPACIDADE_MAX;
    f->quantidade--;

    printf("\n>>> PEÇA JOGADA: [%c %d] (Entrou em jogo!)\n", p.nome, p.id);
}

void exibirFila(FilaCircular *f) {
    printf("\n============================================\n");
    printf("Fila de peças: ");
    
    if (filaVazia(f)) {
        printf("(Vazia)");
    } else {
        for (int i = 0; i < f->quantidade; i++) {
            int indiceReal = (f->inicio + i) % CAPACIDADE_MAX;
            printf("[%c %d] ", f->itens[indiceReal].nome, f->itens[indiceReal].id);
        }
    }
    printf("\n============================================\n");
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}