#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BOARD_SIZE 9
#define PLAYER_X 'x'
#define PLAYER_O 'o'
#define EMPTY '*'

// Declaração de funções
static void singleMode();
static void doubleMode();
static void placePlayer(char player, int pos);
static int checkWin();
static int getValidInput();
static void displayBoard();

// Tabuleiro do jogo
static char gameTable[BOARD_SIZE];

// Função principal
int main() {
    srand((unsigned int)time(NULL));
    int playAgain;

    do {
        int choice;
        // Preenche o tabuleiro com asteriscos
        for (int i = 0; i < BOARD_SIZE; i++) gameTable[i] = EMPTY;

        // Menu principal
        printf("***************************************\n");
        printf("************* TIC TAC TOE *************\n");
        printf("***************************************\n");
        printf("*********** 1. YOU vs COMPUTER ********\n");
        printf("*********** 2. YOU vs PLAYER **********\n");
        printf("*********** 3. EXIT *******************\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                singleMode();
                break;
            case 2:
                doubleMode();
                break;
            default:
                printf("THANK YOU and EXIT!\n");
                return 0;
        }

        printf("Next game? Enter 1 - YES and 0 - NO: ");
        scanf("%d", &playAgain);

    } while (playAgain == 1);

    return 0;
}

// Exibe o tabuleiro
void displayBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%c ", gameTable[i]);
        if ((i + 1) % 3 == 0) printf("\n");
    }
}

// Função para obter uma posição válida do jogador
int getValidInput() {
    int pos;
    while (1) {
        printf("Enter position (1-9): ");
        scanf("%d", &pos);
        if (pos >= 1 && pos <= BOARD_SIZE && gameTable[pos - 1] == EMPTY) {
            return pos;
        }
        printf("Invalid or occupied position. Try again.\n");
    }
}

// Coloca o jogador (X ou O) no tabuleiro
void placePlayer(char player, int pos) {
    gameTable[pos - 1] = player;
}

// Função do modo single player (vs computador)
void singleMode() {
    int moves = 0;
    displayBoard();

    while (moves < BOARD_SIZE) {
        printf("Your turn. ");
        int pos = getValidInput();
        placePlayer(PLAYER_X, pos);
        moves++;
        displayBoard();

        if (checkWin() == 1) {
            printf("YOU WIN!\n");
            return;
        }

        if (moves < BOARD_SIZE) {
            int compPos;
            do {
                compPos = rand() % BOARD_SIZE + 1;
            } while (gameTable[compPos - 1] != EMPTY);

            printf("Computer's turn.\n");
            placePlayer(PLAYER_O, compPos);
            moves++;
            displayBoard();

            if (checkWin() == -1) {
                printf("YOU LOSE!\n");
                return;
            }
        }

        if (moves == BOARD_SIZE) {
            printf("It's a DRAW!\n");
            return;
        }
    }
}

// Função do modo de dois jogadores
void doubleMode() {
    int moves = 0;
    displayBoard();

    while (moves < BOARD_SIZE) {
        printf("PLAYER 1's turn. ");
        int pos1 = getValidInput();
        placePlayer(PLAYER_X, pos1);
        moves++;
        displayBoard();

        if (checkWin() == 1) {
            printf("PLAYER 1 WINS!\n");
            return;
        }

        if (moves < BOARD_SIZE) {
            printf("PLAYER 2's turn. ");
            int pos2 = getValidInput();
            placePlayer(PLAYER_O, pos2);
            moves++;
            displayBoard();

            if (checkWin() == -1) {
                printf("PLAYER 2 WINS!\n");
                return;
            }
        }

        if (moves == BOARD_SIZE) {
            printf("It's a DRAW!\n");
            return;
        }
    }
}

// Verifica as condições de vitória
int checkWin() {
    const int winPatterns[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Linhas
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Colunas
        {0, 4, 8}, {2, 4, 6}              // Diagonais
    };

    for (int i = 0; i < 8; i++) {
        if (gameTable[winPatterns[i][0]] == gameTable[winPatterns[i][1]] &&
            gameTable[winPatterns[i][1]] == gameTable[winPatterns[i][2]]) {
            if (gameTable[winPatterns[i][0]] == PLAYER_X) return 1;
            if (gameTable[winPatterns[i][0]] == PLAYER_O) return -1;
        }
    }
    return 0;
}
