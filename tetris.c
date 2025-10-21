#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5

typedef struct {
    char nome[20];
    int ID;
} peca;

typedef struct {
    peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

typedef struct 
{   peca itens[3];
    int topo;
} Pilha;


//funções da fila
void inicializaFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}
int filaVazia(Fila *f) {
    return f->total == 0;
}   
int filaCheia(Fila *f) {
    return f->total == MAX;
}
void inserir(Fila *f, peca p) {
    if (filaCheia(f)) {
        printf("Fila cheia!\n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}
void remover(Fila *f, peca *p) {
    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return;
    }
    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
}
void imprimirFila(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return;
    }
    printf("Fila de Peças: ");    
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%s %d] ", f->itens[idx].nome, f->itens[idx].ID);
    }
    printf("\n");
}

peca gerarPecaAleatoria(int *id) {
    peca novaPeca;
    const char *tiposPecas[] = {"I", "O", "T", "L"};
    int numTipos = 4;
    
    int indiceAleatorio = rand() % numTipos;
    sprintf(novaPeca.nome, "%s", tiposPecas[indiceAleatorio]);
    novaPeca.ID = (*id)++;
    
    return novaPeca;
}

void gerarPecas(Fila *f, int quantidade, int *id) {
    for (int i = 0; i < quantidade; i++) {
        if (filaCheia(f)) {
            printf("Fila cheia! Não foi possível gerar todas as peças.\n");
            break;
        }
        peca novaPeca = gerarPecaAleatoria(id);
        inserir(f, novaPeca);
    }
}

//funções da pilha
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}
int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}
int pilhaCheia(Pilha *p) {
    return p->topo == 3 - 1;
}
void push(Pilha *p, peca nova) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia. Não é possível inserir.\n");
        return;
    }
    p->topo++;
    p->itens[p->topo] = nova;
}
void pop(Pilha *p, peca *removida) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia. Não é possível remover.\n");
        return;
    }
    *removida = p->itens[p->topo];
    p->topo--;
}
void mostrarPilha(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("Pilha de Reserva: vazia\n");
        return;
    }
    printf("Pilha de Reserva (Topo -> Base): ");
    for (int i = p->topo; i >= 0; i--) {
        printf("[%s %d] ", p->itens[i].nome, p->itens[i].ID);
    }
    printf("\n");
}

// Função auxiliar para obter peça em uma posição específica da fila
peca obterDaFila(Fila *f, int pos) {
    int idx = (f->inicio + pos) % MAX;
    return f->itens[idx];
}

// Função auxiliar para definir peça em uma posição específica da fila
void definirNaFila(Fila *f, int pos, peca p) {
    int idx = (f->inicio + pos) % MAX;
    f->itens[idx] = p;
}

// Função para trocar peça da frente da fila com o topo da pilha
void TrocarPecaAtual(Fila *fila, Pilha *pilha) {
    if (filaVazia(fila)) {
        printf("Fila vazia! Não é possível trocar.\n");
        return;
    }
    if (pilhaVazia(pilha)) {
        printf("Pilha vazia! Não é possível trocar.\n");
        return;
    }
    
    // Troca direta entre as posições
    peca temp = fila->itens[fila->inicio];
    fila->itens[fila->inicio] = pilha->itens[pilha->topo];
    pilha->itens[pilha->topo] = temp;
    
    printf("Troca realizada entre a frente da fila e o topo da pilha.\n");
}

// Função para trocar os 3 primeiros da fila com as 3 peças da pilha
void trocaMultipla(Fila *fila, Pilha *pilha) {
    if (fila->total < 3) {
        printf("Fila não tem 3 peças! Não é possível trocar.\n");
        return;
    }
    if (pilha->topo < 2) {
        printf("Pilha não tem 3 peças! Não é possível trocar.\n");
        return;
    }
    
    // Pilha auxiliar para armazenar as 3 peças da fila
    Pilha auxFila;
    inicializarPilha(&auxFila);
    
    // Pilha auxiliar para armazenar as 3 peças da pilha
    Pilha auxPilha;
    inicializarPilha(&auxPilha);
    
    // Remove e armazena as 3 primeiras peças da fila
    for (int i = 0; i < 3; i++) {
        peca p;
        remover(fila, &p);
        push(&auxFila, p);
    }
    
    // Remove e armazena as 3 peças da pilha
    for (int i = 0; i < 3; i++) {
        peca p;
        pop(pilha, &p);
        push(&auxPilha, p);
    }
    
    // Insere as peças da pilha original na fila (na ordem correta)
    while (auxPilha.topo >= 0) {
        peca p;
        pop(&auxPilha, &p);
        inserir(fila, p);
    }
    
    // Insere as peças da fila original na pilha (na ordem correta)
    while (auxFila.topo >= 0) {
        peca p;
        pop(&auxFila, &p);
        push(pilha, p);
    }
    
    printf("Troca realizada entre os 3 primeiros da fila e os 3 da pilha.\n");
}

int main() 
{
    peca removida;
    srand(time(NULL));

    Fila fila;
    Pilha pilha;
    inicializaFila(&fila);
    inicializarPilha(&pilha);
    int opc;
    int id = 0;

    // Gera peças iniciais
    gerarPecas(&fila, 5, &id);

        printf("\n=== Estado Atual ===\n");
        imprimirFila(&fila);
        mostrarPilha(&pilha);
        printf("\n");

    do 
    {   
        printf("Opções:\n");
        printf("1 - Jogar peça da frente da fila\n");
        printf("2 - Enviar peça da fila para reserva (pilha)\n");
        printf("3 - Usar peça da reserva (pilha)\n");
        printf("4 - Mostrar estado atual\n");
        printf("5 - Trocar peça da frente da fila com o topo da pilha\n");
        printf("6 - Trocar os 3 primeiros da fila com as 3 peças da pilha\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opc);
        printf("\n");

        switch(opc) 
        {
            case 1: {
                if (filaVazia(&fila))
                {
                    printf("Fila Vazia\n");
                    break;
                }
                remover(&fila, &removida);
                printf("Peça Jogada: [%s %d]\n", removida.nome, removida.ID);
                gerarPecas(&fila, 1, &id);
                break;
            }   
            
            case 2: {
                if (pilhaCheia(&pilha))
                {
                    printf("Pilha de reserva cheia, não é possível reservar mais peças!\n");
                    break;
                }
                if (filaVazia(&fila))
                {
                    printf("Fila vazia! Não há peças para reservar.\n");
                    break;
                }
                remover(&fila, &removida);
                push(&pilha, removida);
                printf("Peça reservada: [%s %d]\n", removida.nome, removida.ID);
                gerarPecas(&fila, 1, &id);
                break;
            }

            case 3: {
                if (pilhaVazia(&pilha))
                {
                    printf("Pilha Vazia!\n");
                    break;
                }
                pop(&pilha, &removida);
                printf("Peça reservada usada: [%s %d]\n", removida.nome, removida.ID);
                break;
            }

            case 4: {
                printf("\n--- Estado Atual ---\n");
                imprimirFila(&fila);
                mostrarPilha(&pilha);
                // Apenas exibe o estado atual novamente
                break;
            }
            
            case 5: {
                TrocarPecaAtual(&fila, &pilha);
                break;
            }
            
            case 6: {
                trocaMultipla(&fila, &pilha);
                break;
            }
            
            case 0:
                printf("Saindo...\n");
                break;            
            
            default:
                printf("Opção inválida!\n");
                break;
        }
        
        if (opc != 0) {
            printf("\n--- Novo Estado ---\n");
            imprimirFila(&fila);
            mostrarPilha(&pilha);
        }
        
    } while (opc != 0);

    return 0;
}