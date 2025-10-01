#include <stdio.h>
#include <string.h>

#define N 10        // tamanho do tabuleiro 10x10
#define M 7         // tamanho das matrizes de habilidade (7x7)
#define WATER 0
#define SHIP 3
#define AFFECT 5

int main() {
    // Saudação curta no estilo gaucho
    printf("Batalha Naval - Desafio Nível Mestre (áreas de efeito)\n\n");

    // Inicializa tabuleiro 10x10 com água (0)
    int board[N][N];
    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            board[r][c] = WATER;

    // --- Colocação de alguns navios (valor 3) diretamente no código ---
    // Exemplo simples: alguns navios horizontais e verticais
    // Navio 1 (horizontal) linha 2, colunas 2..4
    board[2][2] = SHIP; board[2][3] = SHIP; board[2][4] = SHIP;
    // Navio 2 (vertical) linha 5..7, coluna 7
    board[5][7] = SHIP; board[6][7] = SHIP; board[7][7] = SHIP;
    // Navio 3 (horizontal) linha 8, colunas 1..3
    board[8][1] = SHIP; board[8][2] = SHIP; board[8][3] = SHIP;

    // --- Matrizes de habilidade (7x7) ---
    int cone[M][M];
    int cross[M][M];
    int octa[M][M];

    // Centro da matriz
    int cx = M/2; // col central (3)
    int cy = M/2; // row central (3)

    // Constrói dinamicamente a matriz "cone"
    // Lógica: apex no centro da matriz; a partir da linha central para baixo o cone se expande.
    // Condição: célula (i,j) está no cone se i >= cy e abs(j - cx) <= (i - cy)
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            if (i >= cy && ( (i - cy) >= abs(j - cx) )) {
                cone[i][j] = 1;
            } else {
                cone[i][j] = 0;
            }
        }
    }

    // Constrói dinamicamente a matriz "cross" (cruz)
    // Lógica: linha central e coluna central são afetadas
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            if (i == cy || j == cx) {
                cross[i][j] = 1;
            } else {
                cross[i][j] = 0;
            }
        }
    }

    // Constrói dinamicamente a matriz "octaedro" (losango visto frontalmente)
    // Lógica: pontos cuja soma das distâncias manhattan ao centro <= radius formam o losango
    int radius = 3; // para M=7, radius 3 preenche um losango central
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            int manhattan = abs(i - cy) + abs(j - cx);
            if (manhattan <= radius) {
                octa[i][j] = 1;
            } else {
                octa[i][j] = 0;
            }
        }
    }

    // --- Define pontos de origem no tabuleiro (linha, coluna) ---
    // Observação: índices baseados em 0 (linha 0..9, col 0..9).
    // Posicionamentos escolhidos para demonstrar as três habilidades:
    int origin_cone_r = 1, origin_cone_c = 4;   // cone centrado em (1,4)
    int origin_cross_r = 4, origin_cross_c = 2; // cruz centrada em (4,2)
    int origin_octa_r = 6, origin_octa_c = 6;  // octaedro centrado em (6,6)

    // --- Função inline: sobrepor matriz de habilidade no tabuleiro ---
    // Percorre a matriz de habilidade; para cada célula ==1 calcula coordenada no tabuleiro
    // e marca com valor AFFECT (5) se estiver dentro dos limites do tabuleiro.
    // Usa loops aninhados e condicionais conforme requerido.
    auto overlay = [&](int skill[M][M], int orig_r, int orig_c) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {
                if (skill[i][j] == 1) { // condicional obrigatória
                    int board_r = orig_r + (i - cy); // deslocamento relativo ao centro
                    int board_c = orig_c + (j - cx);
                    // valida limites do tabuleiro (simplificado, mas necessário)
                    if (board_r >= 0 && board_r < N && board_c >= 0 && board_c < N) {
                        board[board_r][board_c] = AFFECT; // marca posição afetada (sobrescreve qualquer valor)
                    }
                }
            }
        }
    };

    // Sobrepõe as três habilidades no tabuleiro
    overlay(cone, origin_cone_r, origin_cone_c);
    overlay(cross, origin_cross_r, origin_cross_c);
    overlay(octa, origin_octa_r, origin_octa_c);

    // --- Exibe as matrizes de habilidade (para debug/visualização) ---
    printf("Matriz Cone (1 = afetado):\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", cone[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Matriz Cruz (1 = afetado):\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", cross[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Matriz Octaedro (1 = afetado):\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", octa[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // --- Exibe o tabuleiro final ---
    // Representação: 0 = água, 3 = navio (antes de sobrepor), 5 = área afetada
    // Como no requisito escolhemos sobrescrever com 5, os navios que estiverem sob efeito serão exibidos como 5.
    printf("Tabuleiro 10x10 (0=água, 3=navio, 5=área afetada):\n\n");
    printf("   "); // cabeçalho de colunas
    for (int c = 0; c < N; c++) printf("%2d ", c);
    printf("\n");
    for (int r = 0; r < N; r++) {
        printf("%2d ", r); // índice de linha
        for (int c = 0; c < N; c++) {
            printf(" %d ", board[r][c]);
        }
        printf("\n");
    }

    // Legenda e observações
    printf("\nLegenda:\n");
    printf("0 = Água\n3 = Navio (padrão)\n5 = Área afetada por habilidade (sobrescreve visualmente outras marcas)\n\n");

    printf("Observações técnicas:\n");
    printf("- Matrizes de habilidade foram construídas dinamicamente com loops aninhados e condicionais.\n");
    printf("- As habilidades foram centralizadas no ponto de origem definido e sobrepostas ao tabuleiro com checagem de limites.\n");
    printf("- O valor usado para representar área afetada é %d.\n", AFFECT);

    return 0;
}
