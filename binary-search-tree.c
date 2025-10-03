#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int dado;
    struct Node *esquerda, *direita;
} Node;

// Protótipos das funções
Node* novoNo(int dado);
Node* inserir(Node* raiz, int dado);
Node* buscar(Node* raiz, int dado);
void emOrdem(Node* raiz);
Node* remover(Node* raiz, int dado);
void destruir(Node* raiz);
int altura(Node* raiz);
int minimo(Node* raiz);
int maximo(Node* raiz);
int contarNos(Node* raiz);
void imprimirRelatorio(Node* raiz);

// Principal
int main() {
    Node* raiz = NULL;
    int opcao, valor;
    while (opcao != 7) {
        printf("\n--- Menu ABB ---\n");
        printf("[1] Inserir\n");
        printf("[2] Buscar\n");
        printf("[3] Imprimir em ordem\n");
        printf("[4] Remover valor da ABB\n");
        printf("[5] Destruir arvore e comecar nova\n");
        printf("[6] Relatorio com informacoes da arvore\n");
        printf("[7] Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nDigite o valor para inserir: ");
                scanf("%d", &valor);
                raiz = inserir(raiz, valor);
                printf("Valor %d inserido.\n", valor);
                break;
            case 2:
                printf("\nDigite o valor para buscar: ");
                scanf("%d", &valor);
                if (buscar(raiz, valor))
                    printf("\nValor %d encontrado!\n", valor);
                else
                    printf("\nValor %d nao encontrado.\n", valor);
                break;
            case 3:
                printf("\nEm ordem: \n");
                emOrdem(raiz);
                printf("\n");
                break;
            case 4:
                printf("\nDigite o valor para remover: ");
                scanf("%d", &valor);
                raiz = remover(raiz, valor);
                printf("Valor %d removido, se existia.\n", valor);
                break;
            case 5:
                printf("\nDestruindo arvore...\n");
                destruir(raiz);
                raiz = NULL;
                printf("Arvore destruida. Nova arvore criada.\n");
                break;
            case 6:
                imprimirRelatorio(raiz);
                break;
            case 7:
                printf("\nSaindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    }
    destruir(raiz); // Liberar memória antes de sair
    return 0;
}

// Função para criar um novo nó
Node* novoNo(int dado) {
    Node* no = (Node*)malloc(sizeof(Node));
    no->dado = dado;
    no->esquerda = no->direita = NULL;
    return no;
}

// Função para inserir um dado na ABB
Node* inserir(Node* raiz, int dado) {
    if (raiz == NULL) return novoNo(dado);
    if (dado < raiz->dado)
        raiz->esquerda = inserir(raiz->esquerda, dado);
    else if (dado > raiz->dado)
        raiz->direita = inserir(raiz->direita, dado);
    return raiz;
}

// Função para buscar um dado na ABB
Node* buscar(Node* raiz, int dado) {
    if (raiz == NULL || raiz->dado == dado) return raiz;
    if (dado < raiz->dado)
        return buscar(raiz->esquerda, dado);
    else
        return buscar(raiz->direita, dado);
}

// Função para imprimir em ordem
void emOrdem(Node* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("%d ", raiz->dado);
        emOrdem(raiz->direita);
    }
}

// Função para remover um dado da ABB
Node* remover(Node* raiz, int dado) {
    if (raiz == NULL) return NULL;
    if (dado < raiz->dado) {
        raiz->esquerda = remover(raiz->esquerda, dado);
    } else if (dado > raiz->dado) {
        raiz->direita = remover(raiz->direita, dado);
    } else {
        // Nó encontrado
        if (raiz->esquerda == NULL) {
            Node* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            Node* temp = raiz->esquerda;
            free(raiz);
            return temp;
        } else {
            // Caso com dois filhos
            Node* temp = raiz->direita;
            while (temp->esquerda != NULL)
                temp = temp->esquerda;
            raiz->dado = temp->dado;
            raiz->direita = remover(raiz->direita, temp->dado);
        }
    }
    return raiz;
}

// Função para destruir a árvore e liberar memória
void destruir(Node* raiz) {
    if (raiz != NULL) {
        destruir(raiz->esquerda);
        destruir(raiz->direita);
        free(raiz);
    }
}

// Função para calcular a altura da árvore
int altura(Node* raiz) {
    if (raiz == NULL) return 0; // altura de árvore vazia é 0
    int alt_esq = altura(raiz->esquerda);
    int alt_dir = altura(raiz->direita);
    return 1 + (alt_esq > alt_dir ? alt_esq : alt_dir);
}

// Função para encontrar o valor mínimo na árvore
int minimo(Node* raiz) {
    if (raiz == NULL) {
        printf("Arvore vazia.\n");
        return -1; // Retorna -1 se a árvore estiver vazia
    }
    Node* atual = raiz;
    while (atual->esquerda != NULL)
        atual = atual->esquerda;
    return atual->dado;
}

// Função para encontrar o valor máximo na árvore
int maximo(Node* raiz) {
    if (raiz == NULL) {
        printf("Arvore vazia.\n");
        return -1; // Retorna -1 se a árvore estiver vazia
    }
    Node* atual = raiz;
    while (atual->direita != NULL)
        atual = atual->direita;
    return atual->dado;
}

// Função para contar o número de nós na árvore
int contarNos(Node* raiz) {
    if (raiz == NULL) return 0;
    return 1 + contarNos(raiz->esquerda) + contarNos(raiz->direita);
}

// Função para imprimir o relatório da árvore
void imprimirRelatorio(Node* raiz) {
    printf("\nRelatorio da arvore:\n");
    int alt = altura(raiz);
    if (alt == 0) {
        printf("Arvore vazia\n(Nada para mostrar no relatorio)\n");
        return;
    }
    printf("Altura: %d\n", alt);
    int min = minimo(raiz);
    int max = maximo(raiz);
    if (raiz != NULL) {
        printf("Minimo: %d\n", min);
        printf("Maximo: %d\n", max);
    } else {
        printf("Minimo: (arvore vazia)\n");
        printf("Maximo: (arvore vazia)\n");
    }
    printf("Total de nos: %d\n", contarNos(raiz));
}