#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nome[1]; 
    int ID;
} peca;

#define MAX 5

typedef struct {
    peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

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
    printf("Fila de peças:\n");    
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%s - %d] ", f->itens[idx].nome, f->itens[idx].ID);
    }
    printf("\n");
}

int main() {
    Fila fila;
    inicializaFila(&fila);
    int opc;
    int id = 0;

    peca p1 = {"T", id++};
    peca p2 = {"O", id++};
    peca p3 = {"L", id++};
    peca p4 = {"I", id++};

    inserir(&fila, p1);
    inserir(&fila, p2);
    inserir(&fila, p3);
    inserir(&fila, p4);

    imprimirFila(&fila);

    do {
        printf("\nEscolha uma opção:\n1-Inserir peça\n2-Remover peça\n0-Sair\n");
        printf("Opção: ");
        scanf("%d", &opc);

        switch(opc) {
            case 1: {
                if (filaCheia(&fila))
                {
                    printf("Fila cheia, não é possível inserir nova peça!\n");
                    break;
                }
                
                peca novaPeca;
                printf("Digite o nome da peça: ");
                scanf("%s", novaPeca.nome);
                novaPeca.ID = id++;
                inserir(&fila, novaPeca);
                imprimirFila(&fila);
                break;
            }   
            
            case 2: {
                if (filaVazia(&fila))
                {
                    printf("Fila Vazia, não é possível remover nova peça!\n");
                    break;
                }
                peca removida;
                remover(&fila, &removida);
                printf("Peça removida: [%s - %d]\n", removida.nome, removida.ID);
                imprimirFila(&fila);
                break;
            }
            
            case 0:
                printf("Saindo...\n");
                break;            
            
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opc != 0);

    return 0;
}
