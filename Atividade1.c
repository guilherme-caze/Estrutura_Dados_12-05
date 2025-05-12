#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    typedef struct Paciente{
    char nome[30];
    int CPF;
    char gravidade[10]; // Verde | Amarelo | Vermelho
    } Paciente;


    // Definição do nó da fila
    typedef struct Node {
    Paciente dado;
    struct Node* proximo;
    } Node;

    // Definição da estrutura da fila
    typedef struct Queue {
    Node* frente;
    Node* tras;
    } Queue;

    // Função para criar uma fila vazia
    Queue* criarFila() {
    Queue* fila = (Queue*)malloc(sizeof(Queue));
    fila->frente = fila->tras = NULL;
    return fila;
    }

    // Função para inserir um paciente na fila (enqueue)
    void enqueue(Queue* fila, Paciente paciente) {
    Node* novoNode = (Node*)malloc(sizeof(Node));
    novoNode->dado = paciente;
    novoNode->proximo = NULL;
    
    if (fila->tras == NULL) {
        fila->frente = fila->tras = novoNode;
        return;
    }

    fila->tras->proximo = novoNode;
    fila->tras = novoNode;
    }

    // Função para remover um paciente da fila (dequeue)
    Paciente dequeue(Queue* fila) {
    if (fila->frente == NULL) {
        printf("A fila está vazia!\n");
        Paciente vazio;
        strcpy(vazio.nome, "");
        vazio.CPF = 0;
        strcpy(vazio.gravidade, "");
        return vazio;
    }

    Node* temp = fila->frente;
    Paciente paciente = temp->dado;
    fila->frente = fila->frente->proximo;

    if (fila->frente == NULL) {
        fila->tras = NULL;
    }

    free(temp);
    return paciente;
    }

    // Função para verificar se a fila está vazia
    int isEmpty(Queue* fila) {
    return fila->frente == NULL;
    }

    // Função para imprimir os pacientes de uma fila
    void imprimirFila(Queue* fila, char* nomeFila) {
    printf("\nPacientes na fila %s:\n", nomeFila);

    if (isEmpty(fila)) {
        printf("A fila esta vazia!\n");
        return;
    }

    Node* atual = fila->frente;
    while (atual != NULL) {
        Paciente paciente = atual->dado;
        printf("Nome: %s | CPF: %d | Gravidade: %s\n", paciente.nome, paciente.CPF, paciente.gravidade);
        atual = atual->proximo;
    }
    }

    int main(){

    // Criando as três filas
    Queue* filaVerde = criarFila();
    Queue* filaAmarela = criarFila();
    Queue* filaVermelha = criarFila();

    int opcao;
    
    for(int i = 0; i < 3; i++){
        Paciente paciente;

    printf("Bem vindo ao Hospital, informe seu nome e CPF\n");
    printf("Nome: ");
    scanf(" %[^\n]", paciente.nome);
    printf("CPF: ");
    scanf("%d",&paciente.CPF);

    printf("Escolha a gravidade do paciente:\n1 - Verde\n2 - Amarelo\n3 - Vermelho\nOpcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
            case 1:
                strcpy(paciente.gravidade, "Verde");
                enqueue(filaVerde, paciente);
                break;
            case 2:
                strcpy(paciente.gravidade, "Amarelo");
                enqueue(filaAmarela, paciente);
                break;
            case 3:
                strcpy(paciente.gravidade, "Vermelho");
                enqueue(filaVermelha, paciente);
                break;
            default:
                printf("Opção invalida!\n");
        }

    }

    imprimirFila(filaVerde, "Verde");
    imprimirFila(filaAmarela, "Amarela");
    imprimirFila(filaVermelha, "Vermelha");

        return 0;
    }
