#include <stdio.h>

#define BOARD_SIZE   10    // Tabuleiro 10×10
#define SHIP_SIZE     3    // Todos os navios têm tamanho 3

#define WATER         0    // Água
#define SHIP          3    // Parte de navio

// Estrutura para coordenada (linha, coluna)
typedef struct {
    int row;
    int col;
} Coord;

// Protótipos das funções
void initBoard(int board[BOARD_SIZE][BOARD_SIZE]);
int  canPlaceHorizontal(int board[][BOARD_SIZE], Coord start);
int  canPlaceVertical  (int board[][BOARD_SIZE], Coord start);
int  canPlaceDiagDR    (int board[][BOARD_SIZE], Coord start);
int  canPlaceDiagUR    (int board[][BOARD_SIZE], Coord start);
void placeHorizontal   (int board[][BOARD_SIZE], Coord start);
void placeVertical     (int board[][BOARD_SIZE], Coord start);
void placeDiagDR       (int board[][BOARD_SIZE], Coord start);
void placeDiagUR       (int board[][BOARD_SIZE], Coord start);
void printBoard        (int board[][BOARD_SIZE]);

int main() {
    int board[BOARD_SIZE][BOARD_SIZE];

    // 1) Inicializa todo o tabuleiro com água (0)
    initBoard(board);

    // 2) Define pontos iniciais para os 4 navios
    Coord horizStart = {1, 1};  // horizontal
    Coord vertStart  = {4, 5};  // vertical
    Coord diagDRStart= {0, 7};  // diagonal ↘ (down‑right)
    Coord diagURStart= {9, 2};  // diagonal ↗ (up‑right)

    // 3) Valida e posiciona cada navio
    if (!canPlaceHorizontal(board, horizStart)) {
        printf("Erro: não foi possível posicionar navio horizontal em (%d,%d)\n",
               horizStart.row, horizStart.col);
        return 1;
    }
    placeHorizontal(board, horizStart);

    if (!canPlaceVertical(board, vertStart)) {
        printf("Erro: não foi possível posicionar navio vertical em (%d,%d)\n",
               vertStart.row, vertStart.col);
        return 1;
    }
    placeVertical(board, vertStart);

    if (!canPlaceDiagDR(board, diagDRStart)) {
        printf("Erro: não foi possível posicionar navio diagonal DR em (%d,%d)\n",
               diagDRStart.row, diagDRStart.col);
        return 1;
    }
    placeDiagDR(board, diagDRStart);

    if (!canPlaceDiagUR(board, diagURStart)) {
        printf("Erro: não foi possível posicionar navio diagonal UR em (%d,%d)\n",
               diagURStart.row, diagURStart.col);
        return 1;
    }
    placeDiagUR(board, diagURStart);

    // 4) Exibe o tabuleiro final
    printBoard(board);
    return 0;
}

// --- Implementações ---

// Zera toda a matriz com WATER
void initBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            board[i][j] = WATER;
}

// Verifica se cabe navio horizontal sem sair dos limites e sem sobrepor
int canPlaceHorizontal(int board[][BOARD_SIZE], Coord s) {
    if (s.row < 0 || s.row >= BOARD_SIZE ||
        s.col < 0 || s.col + SHIP_SIZE > BOARD_SIZE)
        return 0;
    for (int j = 0; j < SHIP_SIZE; j++)
        if (board[s.row][s.col + j] != WATER)
            return 0;
    return 1;
}

// Verifica navio vertical
int canPlaceVertical(int board[][BOARD_SIZE], Coord s) {
    if (s.col < 0 || s.col >= BOARD_SIZE ||
        s.row < 0 || s.row + SHIP_SIZE > BOARD_SIZE)
        return 0;
    for (int i = 0; i < SHIP_SIZE; i++)
        if (board[s.row + i][s.col] != WATER)
            return 0;
    return 1;
}

// Verifica navio diagonal ↘ (linha+1, col+1)
int canPlaceDiagDR(int board[][BOARD_SIZE], Coord s) {
    if (s.row < 0 || s.col < 0 ||
        s.row + SHIP_SIZE > BOARD_SIZE ||
        s.col + SHIP_SIZE > BOARD_SIZE)
        return 0;
    for (int k = 0; k < SHIP_SIZE; k++)
        if (board[s.row + k][s.col + k] != WATER)
            return 0;
    return 1;
}

// Verifica navio diagonal ↗ (linha-1, col+1)
int canPlaceDiagUR(int board[][BOARD_SIZE], Coord s) {
    if (s.row < SHIP_SIZE - 1 || s.col < 0 ||
        s.row >= BOARD_SIZE    || 
        s.col + SHIP_SIZE > BOARD_SIZE)
        return 0;
    for (int k = 0; k < SHIP_SIZE; k++)
        if (board[s.row - k][s.col + k] != WATER)
            return 0;
    return 1;
}

// Marca navio horizontal
void placeHorizontal(int board[][BOARD_SIZE], Coord s) {
    for (int j = 0; j < SHIP_SIZE; j++)
        board[s.row][s.col + j] = SHIP;
}

// Marca navio vertical
void placeVertical(int board[][BOARD_SIZE], Coord s) {
    for (int i = 0; i < SHIP_SIZE; i++)
        board[s.row + i][s.col] = SHIP;
}

// Marca navio diagonal ↘
void placeDiagDR(int board[][BOARD_SIZE], Coord s) {
    for (int k = 0; k < SHIP_SIZE; k++)
        board[s.row + k][s.col + k] = SHIP;
}

// Marca navio diagonal ↗
void placeDiagUR(int board[][BOARD_SIZE], Coord s) {
    for (int k = 0; k < SHIP_SIZE; k++)
        board[s.row - k][s.col + k] = SHIP;
}

// Imprime índices e células do tabuleiro
void printBoard(int board[][BOARD_SIZE]) {
    printf("   ");
    for (int j = 0; j < BOARD_SIZE; j++)
        printf("%2d ", j);
    printf("\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%2d ", i);
        for (int j = 0; j < BOARD_SIZE; j++)
            printf(" %d ", board[i][j]);
        printf("\n");
    }
}
