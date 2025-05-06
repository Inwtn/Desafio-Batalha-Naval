#include <stdio.h>

#define BOARD_SIZE 10    // Dimensão do tabuleiro (10×10)
#define SHIP_SIZE   3    // Tamanho fixo dos navios

// Valor usado para água e para navio
#define WATER 0
#define SHIP  3

// Tipo para coordenada
typedef struct {
    int row;
    int col;
} Coord;

// Prototipos
void initBoard(int board[BOARD_SIZE][BOARD_SIZE]);
int  canPlaceHorizontal(int board[][BOARD_SIZE], Coord start);
int  canPlaceVertical(int board[][BOARD_SIZE], Coord start);
void placeHorizontal(int board[][BOARD_SIZE], Coord start);
void placeVertical(int board[][BOARD_SIZE], Coord start);
void printBoard(int board[][BOARD_SIZE]);

int main() {
    int board[BOARD_SIZE][BOARD_SIZE];
    
    // Inicializa tabuleiro com água
    initBoard(board);

    // Coordenadas iniciais definidas diretamente
    Coord horizStart = {2, 4};  // navio horizontal começa em linha 2, coluna 4
    Coord vertStart  = {5, 7};  // navio vertical começa em linha 5, coluna 7

    // Valida e posiciona navio horizontal
    if (!canPlaceHorizontal(board, horizStart)) {
        printf("Erro: não é possível posicionar o navio horizontal em (%d, %d)\n",
               horizStart.row, horizStart.col);
        return 1;
    }
    placeHorizontal(board, horizStart);

    // Valida e posiciona navio vertical
    if (!canPlaceVertical(board, vertStart)) {
        printf("Erro: não é possível posicionar o navio vertical em (%d, %d)\n",
               vertStart.row, vertStart.col);
        return 1;
    }
    placeVertical(board, vertStart);

    // Exibe tabuleiro final
    printBoard(board);

    return 0;
}

// Preenche todo o tabuleiro com WATER (0)
void initBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = WATER;
        }
    }
}

// Verifica se cabe um navio horizontal de tamanho SHIP_SIZE em start
// dentro dos limites e sem sobrepor outro navio
int canPlaceHorizontal(int board[][BOARD_SIZE], Coord start) {
    // Checa limites à direita
    if (start.col < 0 || start.col + SHIP_SIZE > BOARD_SIZE ||
        start.row < 0 || start.row >= BOARD_SIZE) {
        return 0;
    }
    // Checa sobreposição
    for (int j = 0; j < SHIP_SIZE; j++) {
        if (board[start.row][start.col + j] != WATER) {
            return 0;
        }
    }
    return 1;
}

// Verifica se cabe um navio vertical de tamanho SHIP_SIZE em start
// dentro dos limites e sem sobrepor outro navio
int canPlaceVertical(int board[][BOARD_SIZE], Coord start) {
    // Checa limites para baixo
    if (start.row < 0 || start.row + SHIP_SIZE > BOARD_SIZE ||
        start.col < 0 || start.col >= BOARD_SIZE) {
        return 0;
    }
    // Checa sobreposição
    for (int i = 0; i < SHIP_SIZE; i++) {
        if (board[start.row + i][start.col] != WATER) {
            return 0;
        }
    }
    return 1;
}

// Marca SHIP nas SHIP_SIZE posições horizontalmente
void placeHorizontal(int board[][BOARD_SIZE], Coord start) {
    for (int j = 0; j < SHIP_SIZE; j++) {
        board[start.row][start.col + j] = SHIP;
    }
}

// Marca SHIP nas SHIP_SIZE posições verticalmente
void placeVertical(int board[][BOARD_SIZE], Coord start) {
    for (int i = 0; i < SHIP_SIZE; i++) {
        board[start.row + i][start.col] = SHIP;
    }
}

// Imprime o tabuleiro no console
void printBoard(int board[][BOARD_SIZE]) {
    printf("   ");
    // Cabeçalho de colunas
    for (int j = 0; j < BOARD_SIZE; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        // Cabeçalho de linha
        printf("%2d ", i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf(" %d ", board[i][j]);
        }
        printf("\n");
    }
}
