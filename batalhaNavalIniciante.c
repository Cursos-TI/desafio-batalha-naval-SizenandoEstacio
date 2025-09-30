#include <stdio.h>

int main() {
    // --- Inicialização do tabuleiro 10x10 ---
    int tabuleiro[10][10];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0; // 0 representa água
        }
    }

    // --- Definição dos navios ---
    int tamanhoNavio = 3; // todos os navios têm tamanho 3

    // Coordenadas iniciais definidas diretamente
    int linhaNavioH = 2; // navio horizontal começa na linha 2
    int colunaNavioH = 1; // coluna inicial do navio horizontal

    int linhaNavioV = 5; // navio vertical começa na linha 5
    int colunaNavioV = 7; // coluna inicial do navio vertical

    // --- Posicionamento do navio horizontal ---
    for (int i = 0; i < tamanhoNavio; i++) {
        tabuleiro[linhaNavioH][colunaNavioH + i] = 3; // 3 representa navio
    }

    // --- Posicionamento do navio vertical ---
    for (int i = 0; i < tamanhoNavio; i++) {
        tabuleiro[linhaNavioV + i][colunaNavioV] = 3; // 3 representa navio
    }

    // --- Exibição do tabuleiro ---
    printf("Tabuleiro 10x10 com navios posicionados:\n\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
