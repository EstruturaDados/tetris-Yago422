#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

typedef struct {
    char nome;
    int id;
} Peca;

typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} FilaCircular;

typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} Pilha;

int idGlobalCounter = 0;

Peca gerarPeca();
void limparBuffer();

void initFila(FilaCircular *f);
int filaCheia(FilaCircular *f);
int filaVazia(FilaCircular *f);
void enfileirar(FilaCircular *f, Peca p);
Peca desenfileirar(FilaCircular *f);

void initPilha(Pilha *p);
int pilhaCheia(Pilha *p);
int pilhaVazia(Pilha *p);
void empilhar(Pilha *p, Peca item);
Peca desempilhar(Pilha *p);

void exibirEstado(FilaCircular *f, Pilha *p);

int main() {
    srand(time(NULL));

    FilaCircular fila;
    Pilha reserva;
    int opcao = -1;
    Peca pecaTemp;

    initFila(&fila);
    initPilha(&reserva);

    while (!filaCheia(&fila)) {
        enfileirar(&fila, gerarPeca());
    }

    do {
        exibirEstado(&fila, &reserva);

        printf("\n--- MENU DE AÇÕES ---\n");
        printf("1. Jogar peça da fila\n");
        printf("2. Reservar peça (Push na Pilha)\n");
        printf("3. Usar peça reservada (Pop da Pilha)\n");
        printf("0. Sair\n");
        printf("Escolha: ");

        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
        }
        limparBuffer();

        switch (opcao) {
            case 1: 
                pecaTemp = desenfileirar(&fila);
                printf("\n>>> PEÇA JOGADA: [%c %d]\n", pecaTemp.nome, pecaTemp.id);
                
                enfileirar(&fila, gerarPeca()); 
                break;

            case 2: 
                if (pilhaCheia(&reserva)) {
                    printf("\n[ERRO] A pilha de reserva está cheia! (Máx: %d)\n", TAM_PILHA);
                } else {
                    pecaTemp = desenfileirar(&fila);
                    empilhar(&reserva, pecaTemp);
                    printf("\n>>> PEÇA RESERVADA: [%c %d]\n", pecaTemp.nome, pecaTemp.id);
                    
                    enfileirar(&fila, gerarPeca());
                }
                break;

            case 3: 
                if (pilhaVazia(&reserva)) {
                    printf("\n[ERRO] Não há peças na reserva para usar.\n");
                } else {
                    pecaTemp = desempilhar(&reserva);
                    printf("\n>>> USANDO PEÇA DA RESERVA: [%c %d]\n", pecaTemp.nome, pecaTemp.id);
                }
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("\nOpção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}

Peca gerarPeca() {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L', 'Z', 'S', 'J'}; 
    nova.nome = tipos[rand() % 7];
    nova.id = idGlobalCounter++;
    return nova;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void initFila(FilaCircular *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

int filaCheia(FilaCircular *f) {
    return (f->quantidade == TAM_FILA);
}

int filaVazia(FilaCircular *f) {
    return (f->quantidade == 0);
}

void enfileirar(FilaCircular *f, Peca p) {
    if (filaCheia(f)) return;
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;
}

Peca desenfileirar(FilaCircular *f) {
    Peca p = {' ', -1};
    if (filaVazia(f)) return p;
    p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;
    return p;
}

void initPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaCheia(Pilha *p) {
    return (p->topo == TAM_PILHA - 1);
}

int pilhaVazia(Pilha *p) {
    return (p->topo == -1);
}

void empilhar(Pilha *p, Peca item) {
    if (pilhaCheia(p)) return;
    p->topo++;
    p->itens[p->topo] = item;
}

Peca desempilhar(Pilha *p) {
    Peca item = {' ', -1};
    if (pilhaVazia(p)) return item;
    item = p->itens[p->topo];
    p->topo--;
    return item;
}

void exibirEstado(FilaCircular *f, Pilha *p) {
    printf("\n============================================\n");
    
    printf("FILA (Próximas): [Saída] ");
    if (filaVazia(f)) {
        printf("(Vazia)");
    } else {
        for (int i = 0; i < f->quantidade; i++) {
            int idx = (f->inicio + i) % TAM_FILA;
            printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
        }
    }
    printf("[Entrada]\n");

    printf("PILHA (Reserva): [Base]  ");
    if (pilhaVazia(p)) {
        printf("(Vazia)");
    } else {
        for (int i = 0; i <= p->topo; i++) {
            printf("[%c %d] ", p->itens[i].nome, p->itens[i].id);
        }
    }
    printf("[Topo] (Capacidade: %d/%d)\n", p->topo + 1, TAM_PILHA);
    
    printf("============================================\n");
}