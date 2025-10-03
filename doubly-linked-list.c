#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 50 // tamanho da string "data"

typedef struct Node {
    char data[TAM];
    struct Node* prev;
    struct Node* next;
} Node;

Node* head = NULL;
Node* tail = NULL;
int tamanho_lista = 0;

// prototipos das funções
void inicializarLista();
Node* criarNo(const char* valor);
Node* buscarNo(int posicao);
void inserirEntre(Node* anterior, Node* proximo, Node* novo);
void inserirNaPosicao(const char* valor, int posicao);
void inserirValorNaPosicao(int posicao);
void inserirInicio();
void inserirFim();
void inserirMeio();
void apagar();
void mostrarLista();
void liberarLista();


int main() {
    inicializarLista();

    int opcao;

    do {
        printf("\n--- Lista Duplamente Encadeada ---\n");
        printf("[1] Inserir no inicio\n");
        printf("[2] Inserir no fim\n");
        printf("[3] Inserir em uma posicao\n");
        printf("[4] Apagar noh em uma posicao\n");
        printf("[5] Mostrar lista\n");
        printf("[6] Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                inserirInicio();
                break;

            case 2:
                inserirFim();
                break;

            case 3:
                inserirMeio();
                break;

            case 4:
                apagar();
                break;

            case 5:
                mostrarLista();
                break;

            case 6:
                printf("Saindo...\n");
                liberarLista();
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 6);

    return 0;
}


void inicializarLista() {
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
    novo->prev = NULL;
    novo->next = NULL;
    return novo;
}

// Otimização: retorna head ou tail (qual for mais próximo da posição) | reduz de O(n) para O(n/2)
Node* buscarNo(int posicao) {
    if (posicao < 0 || posicao >= tamanho_lista) return NULL;
    if (head == NULL) return NULL;
    
    Node* temp;
    if (posicao <= tamanho_lista / 2) { 
        // percorre do início
        temp = head;
        for (int i = 0; i < posicao; i++)
            temp = temp->next;
    } else { 
        // percorre do fim
        temp = tail;
        for (int i = tamanho_lista - 1; i > posicao; i--)
            temp = temp->prev;
    }
    return temp;
}

// Função genérica de inserção entre dois nós
void inserirEntre(Node* anterior, Node* proximo, Node* novo) {

    if (anterior != NULL) anterior->next = novo;
    if (proximo != NULL) proximo->prev = novo;

    novo->prev = anterior;
    novo->next = proximo;

    if (anterior == NULL) head = novo; // se for início
    if (proximo == NULL) tail = novo; // se for fim

    tamanho_lista++;
}

// a lógica de inserção separada em casos
void inserirNaPosicao(const char* valor, int posicao) {

    if (posicao < 0 || posicao > tamanho_lista) return;

    Node* novo = criarNo(valor);
    if (novo == NULL) return;

    if (posicao == 0) {
        // inserir no início
        inserirEntre(NULL, head, novo);
    } else if (posicao == tamanho_lista) {
        // inserir no fim
        inserirEntre(tail, NULL, novo);
    } else {
        // inserir no meio
        Node* temp = buscarNo(posicao);
        inserirEntre(temp->prev, temp, novo);
    }
}

void inserirValorNaPosicao(int posicao) {
    if (posicao < 0 || posicao > tamanho_lista) {
        printf("Posicao invalida!\n");
        return;
    }
    char valor[TAM];
    printf("Digite o valor:\n");
    scanf("%s", valor); 
    getchar(); // limpa o '\n' do buffer
    inserirNaPosicao(valor, posicao);

}

void inserirInicio() {
    inserirValorNaPosicao(0);
}

void inserirFim() {
    inserirValorNaPosicao(tamanho_lista);
}

void inserirMeio() {
    int posicao;
    do {
        printf("Digite a posicao para inserir (0 a %d):\n", tamanho_lista);
        scanf("%d", &posicao);
        if (posicao < 0 || posicao > tamanho_lista)
            printf("Posicao invalida! Tente novamente.\n");
    } while (posicao < 0 || posicao > tamanho_lista);

    inserirValorNaPosicao(posicao);
}

void apagar() {
    if (tamanho_lista == 0) {
        printf("Lista vazia. Nada para apagar.\n");
        return;
    }

    int posicao;
    do {
        printf("Digite a posicao do no a apagar (0 a %d):\n", tamanho_lista - 1);
        scanf("%d", &posicao);
        if (posicao < 0 || posicao >= tamanho_lista)
            printf("Posicao invalida! Tente novamente.\n");
    } while (posicao < 0 || posicao >= tamanho_lista);

    Node* temp = buscarNo(posicao);
    if (temp == NULL) {
        printf("Posicao invalida!\n");
        return;
    }  
    
    // Ajusta ponteiros dos nós vizinhos
    if (temp->prev != NULL) temp->prev->next = temp->next;
    else head = temp->next; // se era o primeiro nó
    if (temp->next != NULL) temp->next->prev = temp->prev;
    else tail = temp->prev; // se era o último nó

    printf("Noh na posicao %d removido (valor: %s).\n", posicao, temp->data);
    free(temp);

    tamanho_lista--;
}

void mostrarLista() {
    if (tamanho_lista == 0) {
        printf("\nLista vazia.\n");
        return;
    }

    Node* temp = head;
    printf("\n - - - Lista: - - -\n");
    printf("[i] | valores\n");
    int i = 0;
    while (temp != NULL) {
        printf("[%d] | %s\n", i, temp->data);
        temp = temp->next;
        i++;
    }
    printf("- - - fim da lista - - -\n");
}

void liberarLista() {
    while (head != NULL) {
        Node* prox = head->next;
        free(head);
        head = prox;
    }
    head = NULL;
    tail = NULL;
    tamanho_lista = 0;
}