#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define TAMANHO_FILA 5
#define TAMANHO_PILHA 3
#define NUM_TIPOS 5

int proximoID;

typedef struct {
    char tipo;
    int id;
} Peca;

Peca fila[TAMANHO_FILA];
int inicioFila = 0;
int fimFila = 0;
int contFila = 0;

Peca pilha[TAMANHO_PILHA];
int topoPilha = -1;

void inicializarTudo();
char gerarTipoAleatorio();
Peca gerarPeca();
void limparBufferEntrada();
void limparTela();

void enqueue(Peca p);
Peca dequeue();
bool filaCheia();
bool filaVazia();
void mostrarFila();
void jogarPeca();

void push(Peca p);
Peca pop();
bool pilhaCheia();
bool pilhaVazia();
void mostrarPilha();

void enviarParaReserva();
void usarDaReserva();
void trocarFrentePilha();
void trocarTresPrimeiros();

int main() {
    int opcao;

    inicializarTudo();

    printf("--- Desafio Tetris Stack ---\n");

    do {
        limparTela();
        
        printf("\n*** Status Atual ***\n");
        mostrarFila();
        mostrarPilha();
        printf("--------------------\n");
        
        printf("\n--- Menu de Opcoes ---\n");
        printf("1 - Jogar peca (Remover da fila e repor)\n");
        printf("2 - Enviar peca da fila para a reserva (Pilha)\n");
        printf("3 - Usar peca da reserva (Pop da pilha)\n");
        printf("4 - Trocar peca da frente da fila com o topo da pilha\n");
        printf("5 - Trocar 3 primeiros da fila com as 3 da pilha\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
            limparBufferEntrada();
        }
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                jogarPeca();
                break;
            case 2:
                enviarParaReserva();
                break;
            case 3:
                usarDaReserva();
                break;
            case 4:
                trocarFrentePilha();
                break;
            case 5:
                trocarTresPrimeiros();
                break;
            case 0:
                printf("\nFim do jogo. Tchau!\n");
                break;
            default:
                printf("\nOpcao invalida. Tente de novo.\n");
                break;
        }
        
        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...\n");
            getchar();
        }

    } while (opcao != 0);

    return 0;
}

void inicializarTudo() {
    srand(time(NULL));
    proximoID = 1;
    
    for (int i = 0; i < TAMANHO_FILA; i++) {
        enqueue(gerarPeca());
    }
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limparTela() {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

char gerarTipoAleatorio() {
    char tipos[] = {'I', 'O', 'T', 'L', 'J'};
    return tipos[rand() % NUM_TIPOS];
}

Peca gerarPeca() {
    Peca nova;
    nova.tipo = gerarTipoAleatorio();
    nova.id = proximoID++;
    return nova;
}

bool filaCheia() {
    return contFila == TAMANHO_FILA;
}

bool filaVazia() {
    return contFila == 0;
}

void enqueue(Peca p) {
    if (filaCheia()) {
        printf("ERRO: Fila cheia, nao da para colocar mais pecas.\n");
        return;
    }
    fila[fimFila] = p;
    fimFila = (fimFila + 1) % TAMANHO_FILA;
    contFila++;
}

Peca dequeue() {
    if (filaVazia()) {
        printf("ERRO: Fila vazia, nao ha pecas para remover.\n");
        Peca vazia = {'X', 0}; 
        return vazia;
    }
    Peca removida = fila[inicioFila];
    inicioFila = (inicioFila + 1) % TAMANHO_FILA;
    contFila--;
    return removida;
}

void mostrarFila() {
    printf("Fila de Peças Futuras (Cont: %d):\n", contFila);
    if (filaVazia()) {
        printf("  [ VAZIA ]\n");
        return;
    }

    printf("  FRENTE -> ");
    for (int i = 0; i < contFila; i++) {
        int indice = (inicioFila + i) % TAMANHO_FILA;
        printf("[%c-%d] ", fila[indice].tipo, fila[indice].id);
    }
    printf("<- FIM\n");
}

void jogarPeca() {
    if (filaVazia()) {
        printf("Nao ha pecas para jogar!\n");
        return;
    }
    
    Peca jogada = dequeue();
    printf("Peça Jogada (removida): Tipo %c, ID %d.\n", jogada.tipo, jogada.id);

    Peca nova = gerarPeca();
    enqueue(nova);
    printf("Nova peça adicionada à fila: Tipo %c, ID %d.\n", nova.tipo, nova.id);
}

bool pilhaCheia() {
    return topoPilha == TAMANHO_PILHA - 1;
}

bool pilhaVazia() {
    return topoPilha == -1;
}

void push(Peca p) {
    if (pilhaCheia()) {
        printf("ERRO: Pilha de reserva cheia. Nao da para guardar mais.\n");
        return;
    }
    pilha[++topoPilha] = p;
}

Peca pop() {
    if (pilhaVazia()) {
        printf("ERRO: Pilha vazia. Nao ha pecas para usar.\n");
        Peca vazia = {'X', 0}; 
        return vazia;
    }
    return pilha[topoPilha--];
}

void mostrarPilha() {
    printf("Pilha de Reserva (Cont: %d):\n", topoPilha + 1);
    if (pilhaVazia()) {
        printf("  [ VAZIA ]\n");
        return;
    }
    
    for (int i = topoPilha; i >= 0; i--) {
        if (i == topoPilha) {
            printf("  TOPO -> ");
        } else {
            printf("          ");
        }
        printf("[%c-%d]\n", pilha[i].tipo, pilha[i].id);
    }
}

void enviarParaReserva() {
    if (filaVazia()) {
        printf("Falhou: A fila esta vazia. Nao ha o que mover.\n");
        return;
    }
    if (pilhaCheia()) {
        printf("Falhou: A reserva (pilha) esta cheia. Use uma peça primeiro.\n");
        return;
    }

    Peca movida = dequeue();
    push(movida);
    
    Peca nova = gerarPeca();
    enqueue(nova);

    printf("Peça %c-%d enviada para a Reserva (Pilha).\n", movida.tipo, movida.id);
    printf("Peça de reposição %c-%d adicionada à fila.\n", nova.tipo, nova.id);
}

void usarDaReserva() {
    if (pilhaVazia()) {
        printf("Falhou: A reserva (pilha) esta vazia. Nao ha o que usar.\n");
        return;
    }

    Peca usada = pop();
    printf("Peça Usada (removida da pilha): Tipo %c, ID %d.\n", usada.tipo, usada.id);
}

void trocarFrentePilha() {
    if (filaVazia() || pilhaVazia()) {
        printf("Falhou: A fila ou a pilha estao vazias. Precisa de 1 peça em cada.\n");
        return;
    }
    
    int indiceFrente = inicioFila;
    int indiceTopo = topoPilha;
    
    Peca temp = fila[indiceFrente];
    fila[indiceFrente] = pilha[indiceTopo];
    pilha[indiceTopo] = temp;

    printf("Troca realizada: A peça da Frente da Fila e o Topo da Pilha foram trocados.\n");
}

void trocarTresPrimeiros() {
    if (contFila < 3) {
        printf("Falhou: A fila precisa ter pelo menos 3 peças.\n");
        return;
    }
    if (topoPilha != TAMANHO_PILHA - 1) {
        printf("Falhou: A pilha precisa estar COMPLETAMENTE cheia (3 peças).\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        int indiceFila = (inicioFila + i) % TAMANHO_FILA;
        int indicePilha = topoPilha - i;

        Peca temp = fila[indiceFila];
        fila[indiceFila] = pilha[indicePilha];
        pilha[indicePilha] = temp;
    }

    printf("Troca realizada: As 3 primeiras peças da Fila e as 3 da Pilha foram trocadas.\n");
}
