#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 50 // tamanho da string "data"

typedef struct Node {
    char data[TAM];
    struct Node* next;
} Node;

Node* head = NULL;
Node* tail = NULL;
int tamanho_fila = 0;

// prototipos das funções
void inicializarFila();
Node* criarNo(const char* valor);
void mostrarPrimeiro();
void mostrarUltimo();
void inserirNoFim();
void apagar();
void mostrarFila();
void liberarFila();


int main() {
    inicializarFila();

    int opcao;

    do {
        printf("\n--- QUEUE com Lista encadeada ---\n");
        printf("[1] Inserir no fim da fila\n");
        printf("[2] Apagar primeiro da fila\n");
        printf("[3] Mostrar fila\n");
        printf("[4] Mostrar primeiro da fila\n");
        printf("[5] Mostrar ultimo da fila\n");
        printf("[6] Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                inserirNoFim();
                break;

            case 2:
                apagar();
                break;

            case 3:
                mostrarFila();
                break;

            case 4:
                mostrarPrimeiro();
                break;

            case 5:
                mostrarUltimo();
                break;

            case 6:
                printf("Saindo...\n");
                liberarFila();
                printf("Programa Encerrado.\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 6);

    return 0;
}


void inicializarFila() {
    head = NULL;
    tail = NULL;
}

Node* criarNo(const char* valor) {
    Node* novo = (Node*)malloc(sizeof(Node));
    if (novo == NULL) {
        printf("Erro ao alocar memoria.\n");
        return NULL;
    }
    strncpy(novo->data, valor, TAM - 1);
    novo->data[TAM - 1] = '\0';
    novo->next = NULL;
    return novo;
}

void mostrarPrimeiro() {
    if (head == NULL) printf("Queue Vazia\n");
    else printf("Primeiro da Fila:\n\"%s\"\n", head->data);
}
void mostrarUltimo() {
    if (tail == NULL) printf("Queue Vazia\n");
    else printf("Ultimo da Fila:\n\"%s\"\n", tail->data);
}

// inseririr novo nó no fim da fila
void inserirNoFim() {
    char valor[TAM];
    printf("Digite o valor:\n");
    scanf("%s", valor);

    Node* novo = criarNo(valor);
    if (novo == NULL) return; //verifica se o novo nó é válido para então continuar a operação

    if (head == NULL) head = novo; // fila vazia
    else tail->next = novo;
    tail = novo;

    tamanho_fila++;
}


void apagar() {
    if (tamanho_fila == 0) {
        printf("Fila vazia. Nada para apagar.\n");
        return;
    }

    Node* temp = head;
    head = head->next;

    if (head == NULL) tail = NULL; //fila ficou vazia
    
    printf("Noh removido da fila (valor: \"%s\").\n", temp->data);
    free(temp);

    tamanho_fila--;
}

void mostrarFila() {
    if (tamanho_fila == 0) {
        printf("\nFila vazia.\n");
        return;
    }

    Node* temp = head;
    printf("\n - - - Queue: - - -\n");
    printf("[i] | valores\n");
    int i = 0;
    while (temp != NULL) {
        printf("[%d] | \"%s\"\n", i, temp->data);
        temp = temp->next;
        i++;
    }
    printf("- - - fim da queue - - -\n");
}

void liberarFila() {
    while (head != NULL) {
        Node* prox = head->next;
        free(head);
        head = prox;
    }
    head = NULL;
    tail = NULL;
    tamanho_fila = 0;
    printf("Memoria Liberada.\n");
}