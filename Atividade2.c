#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    float num1;
    float num2;
    char operacao; // '+', '-', '*', '/'
} Operacao;

typedef struct {
    Operacao itens[MAX];
    int topo;
} Pilha;

void inicializar(Pilha *p) {
    p->topo = -1;
}

int estaVazia(Pilha *p) {
    return p->topo == -1;
}

int estaCheia(Pilha *p) {
    return p->topo == MAX - 1;
}

int empilhar(Pilha *p, Operacao op) {
    if (estaCheia(p)) return 0;
    p->itens[++p->topo] = op;
    return 1;
}

int desempilhar(Pilha *p, Operacao *op) {
    if (estaVazia(p)) return 0;
    *op = p->itens[p->topo--];
    return 1;
}

float calcular(Operacao op) {
    switch (op.operacao) {
        case '+': return op.num1 + op.num2;
        case '-': return op.num1 - op.num2;
        case '*': return op.num1 * op.num2;
        case '/': return (op.num2 != 0) ? op.num1 / op.num2 : 0;
        default: return 0;
    }
}

void exibirResultado(Pilha *p) {
    float resultadoTotal = 0;
    for (int i = 0; i <= p->topo; i++) {
        float resultado = calcular(p->itens[i]);
        printf("Operacao %d: %.2f %c %.2f = %.2f\n",
               i + 1,
               p->itens[i].num1,
               p->itens[i].operacao,
               p->itens[i].num2,
               resultado);
        resultadoTotal += resultado;
    }
    printf("\nResultado acumulado das operacoes: %.2f\n", resultadoTotal);
}

int main() {
    Pilha pilha;
    inicializar(&pilha);
    int opcao;

    do {
        printf("\nCalculadora com Pilha\n");
        printf("1. Adicionar operacao\n");
        printf("2. Desfazer ultima operacao\n");
        printf("3. Exibir resultado final\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            Operacao nova;
            printf("Digite o primeiro numero: ");
            scanf("%f", &nova.num1);
            printf("Digite o segundo numero: ");
            scanf("%f", &nova.num2);
            printf("Digite a operacao (+ - * /): ");
            scanf(" %c", &nova.operacao);
            if (empilhar(&pilha, nova)) {
                printf("Operacao adicionada com sucesso.\n");
            } else {
                printf("Pilha cheia! Nao foi possivel adicionar.\n");
            }
        } else if (opcao == 2) {
            Operacao removida;
            if (desempilhar(&pilha, &removida)) {
                printf("ultima operacao desfeita: %.2f %c %.2f\n",
                       removida.num1, removida.operacao, removida.num2);
            } else {
                printf("Pilha vazia! Nenhuma operacao para desfazer.\n");
            }
        } else if (opcao == 3) {
            if (estaVazia(&pilha)) {
                printf("Nenhuma operacao para exibir.\n");
            } else {
                exibirResultado(&pilha);
            }
        }
    } while (opcao != 0);

    printf("Programa encerrado.\n");
    return 0;
}
