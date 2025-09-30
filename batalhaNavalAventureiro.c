#include <stdio.h>

int main() {
    // --- Inicialização do tabuleiro 10x10 ---
    int tabuleiro[10][10];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0; // 0 representa água
        }
    }

    int tamanhoNavio = 3; // Todos os navios têm tamanho 3

    // --- Coordenadas dos navios ---
    // Navio horizontal
    int linhaNavH = 1;
    int colunaNavH = 2;

    // Navio vertical
    int linhaNavV = 5;
    int colunaNavV = 7;

    // Navio diagonal descendente (linha e coluna aumentam)
    int linhaNavDiag1 = 0;
    int colunaNavDiag1 = 0;

    // Navio diagonal ascendente (linha diminui, coluna aumenta)
    int linhaNavDiag2 = 9;
    int colunaNavDiag2 = 0;

    // --- Posicionamento do navio horizontal ---
    for (int i = 0; i < tamanhoNavio; i++) {
        tabuleiro[linhaNavH][colunaNavH + i] = 3;
    }

    // --- Posicionamento do navio vertical ---
    for (int i = 0; i < tamanhoNavio; i++) {
        tabuleiro[linhaNavV + i][colunaNavV] = 3;
    }

    // --- Posicionamento do navio diagonal descendente ---
    for (int i = 0; i < tamanhoNavio; i++) {
        tabuleiro[linhaNavDiag1 + i][colunaNavDiag1 + i] = 3;
    }

    // --- Posicionamento do navio diagonal ascendente ---
    for (int i = 0; i < tamanhoNavio; i++) {
        tabuleiro[linhaNavDiag2 - i][colunaNavDiag2 + i] = 3;
    }

    // --- Exibição do tabuleiro ---
    printf("Tabuleiro 10x10 com 4 navios posicionados:\n\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
