#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

peca gerarPecaAleatoria(int *id) {
    peca novaPeca;
    const char *tiposPecas[] = {"I", "O", "T", "L"};
    int numTipos = 4; // Número de tipos disponíveis
    
    // Sorteia um tipo aleatório
    int indiceAleatorio = rand() % numTipos;
    
    // Copia o nome da peça sorteada
    sprintf(novaPeca.nome, "%s", tiposPecas[indiceAleatorio]);
    novaPeca.ID = (*id)++;
    
    return novaPeca;
}

// Função para gerar várias peças aleatórias iniciais
void gerarPecasIniciais(Fila *f, int quantidade, int *id) {
    //printf("Gerando %d peças aleatórias...\n", quantidade);
    
    for (int i = 0; i < quantidade; i++) {
        if (filaCheia(f)) {
            printf("Fila cheia! Não foi possível gerar todas as peças.\n");
            break;
        }
        peca novaPeca = gerarPecaAleatoria(id);
        inserir(f, novaPeca);
        //printf("Peça gerada: [%s - %d]\n", novaPeca.nome, novaPeca.ID);
    }
}

int main() 
{

    srand(time(NULL));

    Fila fila;
    inicializaFila(&fila);
    int opc;
    int id = 0;

    // Gera 4 peças aleatórias no início
    gerarPecasIniciais(&fila, 4, &id);
    printf("\n");
    imprimirFila(&fila);

    do 
    {
        printf("\nEscolha uma opção:\n1-Inserir peça\n2-Remover peça\n0-Sair\n");
        printf("Opção: ");
        scanf("%d", &opc);

        switch(opc) 
        {
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
                    printf("Fila Vazia\n");
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
