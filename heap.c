#include <stdio.h>
#include <stdlib.h>

typedef struct Heap {
    float *array;
    int capacidade;
    int tamanho;
} Heap;

Heap* criarHeap(int capacidade);
void inserir(Heap *heap, float valor);
void liberarHeap(Heap *heap);
int extrairMaximo(Heap *heap);
void imprimirHeap(Heap *heap);
void heapfyUp(Heap *heap, int i);
void heapfyDown(Heap *heap, int i);

int main() {
    int capacidade, opcao, valor;

    printf("Capacidade inicial da Heap: ");
    scanf("%d", &capacidade);

    Heap *heap = criarHeap(capacidade);

    do {
        printf("\n- - - - MENU DA HEAP - - - -\n");
        printf("[1] Inserir elemento\n");
        printf("[2] Extrair mqximo\n");
        printf("[3] Mostrar heap\n");
        printf("[4] Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Valor a inserir: ");
                scanf("%d", &valor);
                inserir(heap, valor);
                printf("Valor inserido!\n");
                break;
            case 2:
                if (heap->tamanho == 0) {
                    printf("Heap vazia!\n");
                } else {
                    int max = extrairMaximo(heap);
                    printf("Mqximo extraído: %d\n", max);
                }
                break;
            case 3:
                imprimirHeap(heap);
                break;
            case 4:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opcao invqlida!\n");
        }
    } while (opcao != 4);
    liberarHeap(heap);
    return 0;
}

Heap* criarHeap(int capacidade) {
    Heap *heap = malloc(sizeof(Heap));
    if (heap == NULL) {
        return NULL;
    }
    heap->capacidade = capacidade;
    heap->tamanho = 0;
    heap->array = malloc(heap->capacidade * sizeof *heap->array);
    if (heap->array == NULL) {
        free(heap);
        return NULL;
    }
    return heap;
}

void inserir(Heap *heap, float valor) {
    if (heap->tamanho == heap->capacidade) {
        return;
    }
    heap->array[heap->tamanho] = valor;
    heap->tamanho++;
    heapfyUp(heap, heap->tamanho - 1); // restaura a propriedade de heap subindo o novo elemento
}

void liberarHeap(Heap *heap) {
    if (heap != NULL) {
        free(heap->array);
        free(heap);
    }
}

int extrairMaximo(Heap *heap) {
    if (heap->tamanho == 0) {
        return -1;
    }
    int maximo = (int)heap->array[0];
    heap->array[0] = heap->array[heap->tamanho - 1];
    heap->tamanho--;
    if (heap->tamanho > 0) {
        heapfyDown(heap, 0); // restaura a propriedade de heap descendo a nova raiz
    }
    return maximo;
}

void imprimirHeap(Heap *heap) {
    for (int i = 0; i < heap->tamanho; i++) {
        printf("%f ", heap->array[i]);
    }
    printf("\n");
}

void heapfyDown(Heap *heap, int i) {
    while (1) {
        int esq = 2 * i + 1;
        int dir = 2 * i + 2;
        int maior = i;

        if (esq < heap->tamanho && heap->array[esq] > heap->array[maior]) {
            maior = esq;
        }
        if (dir < heap->tamanho && heap->array[dir] > heap->array[maior]) {
            maior = dir;
        }
        if (maior != i) {
            float tmp = heap->array[i];
            heap->array[i] = heap->array[maior];
            heap->array[maior] = tmp;
            i = maior;
        } else {
            break;
        }
    }
}

void heapfyUp(Heap *heap, int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;
        if (heap->array[pai] < heap->array[i]) {
            float tmp = heap->array[pai];
            heap->array[pai] = heap->array[i];
            heap->array[i] = tmp;
            i = pai;
        } else {
            break;
        }
    }
}