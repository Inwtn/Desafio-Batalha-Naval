#include <stdio.h>

#define BOARD_SIZE   10    // Dimensão do tabuleiro (10×10)
#define SHIP_SIZE     3    // Tamanho fixo de cada navio

#define WATER         0    // Representa água
#define SHIP          3    // Representa navio
#define EFFECT        5    // Representa área afetada por habilidade

// Estrutura para coordenadas (linha, coluna)
typedef struct {
    int row;
    int col;
} Coord;

// Protótipos das funções
void initBoard(int board[BOARD_SIZE][BOARD_SIZE]);
void initEffectMatrix(int mat[][BOARD_SIZE], int size, char type);
void overlayEffect(int board[][BOARD_SIZE], int effMat[][BOARD_SIZE], int size, Coord origin);
void printBoard(int board[BOARD_SIZE][BOARD_SIZE]);

int main() {
    int board[BOARD_SIZE][BOARD_SIZE];

    // 1) Inicializa tabuleiro com água
    initBoard(board);

    // (Aqui você pode posicionar navios como nos níveis anteriores)
    // Exemplo mínimo: um navio horizontal e um vertical
    // ... (omitted for brevidade) ...

    // 2) Define matrizes de efeito (todas serão 5x5)
    const int EFF_SIZE = 5;
    static int cone[EFF_SIZE][EFF_SIZE];
    static int cross[EFF_SIZE][EFF_SIZE];
    static int octa[EFF_SIZE][EFF_SIZE];

    // 3) Inicializa cada matriz dinamicamente
    initEffectMatrix(cone, EFF_SIZE, 'C');   // Cone para baixo
    initEffectMatrix(cross, EFF_SIZE, 'X');  // Cruz
    initEffectMatrix(octa, EFF_SIZE, 'O');   // Octaedro (losango)

    // 4) Define origens das habilidades no tabuleiro
    Coord originCone  = {2, 2};  // ponto de topo do cone
    Coord originCross = {5, 5};  // centro da cruz
    Coord originOcta  = {7, 2};  // centro do losango

    // 5) Sobrepõe efeitos ao tabuleiro
    overlayEffect(board, cone,  EFF_SIZE, originCone);
    overlayEffect(board, cross, EFF_SIZE, originCross);
    overlayEffect(board, octa,  EFF_SIZE, originOcta);

    // 6) Exibe tabuleiro final
    printBoard(board);
    return 0;
}

// Preenche tabuleiro com WATER (0)
void initBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = WATER;
        }
    }
}

// Constrói matriz de efeito de tamanho size x size
// 'C' = cone (para baixo), 'X' = cruz, 'O' = octaedro (losango)
void initEffectMatrix(int mat[][BOARD_SIZE], int size, char type) {
    int center = size / 2;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mat[i][j] = 0; // padrão não afetado
            switch (type) {
                case 'C':
                    // Cone: linha i representa distância do topo
                    // Largura cresce a cada linha: j deve estar dentro de um triângulo
                    if (j >= center - i && j <= center + i) {
                        mat[i][j] = 1;
                    }
                    break;
                case 'X':
                    // Cruz: afeta centro de linhas e colunas
                    if (i == center || j == center) {
                        mat[i][j] = 1;
                    }
                    break;
                case 'O':
                    // Octaedro (losango): soma das distâncias ao centro <= center
                    if (abs(i - center) + abs(j - center) <= center) {
                        mat[i][j] = 1;
                    }
                    break;
            }
        }
    }
}

// Sobrepõe a matriz de efeito ao tabuleiro, marcando EFFECT (5)
void overlayEffect(int board[][BOARD_SIZE], int effMat[][BOARD_SIZE], int size, Coord origin) {
    int center = size / 2;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (effMat[i][j] == 1) {
                int bi = origin.row + (i - center);
                int bj = origin.col + (j - center);
                // Verifica limites do tabuleiro
                if (bi >= 0 && bi < BOARD_SIZE && bj >= 0 && bj < BOARD_SIZE) {
                    // Não sobrescreve navio (3)
                    if (board[bi][bj] == WATER) {
                        board[bi][bj] = EFFECT;
                    }
                }
            }
        }
    }
}

// Exibe o tabuleiro no console
void printBoard(int board[][BOARD_SIZE]) {
    // Cabeçalhos de coluna
    printf("   ");
    for (int j = 0; j < BOARD_SIZE; j++) {
        printf(" %d ", j);
    }
    printf("\n");

    for (int i = 0; i < BOARD_SIZE; i++) {
        printf(" %d ", i); // índice da linha
        for (int j = 0; j < BOARD_SIZE; j++) {
            int v = board[i][j];
            char c = (v == WATER ? '.' : v == SHIP ? 'S' : 'A');
            // . = água, S = navio, A = área de efeito
            printf(" %c ", c);
        }
        printf("\n");
    }
}