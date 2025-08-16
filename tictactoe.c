#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void drawBoard(char board[3][3]);
int checkWinner(char board[3][3]);
int isFull(char board[3][3]);

int main() {
    char board[3][3] = { {'1','2','3'},
                         {'4','5','6'},
                         {'7','8','9'} };

    int choice, row, col, player = 1;
    char mark;
    int gameStatus = 0; // 0 = ongoing, 1 = win

    do {
        drawBoard(board);
        player = (player % 2) ? 1 : 2;
        printf("Player %d, enter your choice (1-9): ", player);
        scanf("%d", &choice);

        mark = (player == 1) ? 'X' : 'O';

        // Convert choice into board coordinates
        row = (choice - 1) / 3;
        col = (choice - 1) % 3;

        // Validate move
        if (choice >= 1 && choice <= 9 && board[row][col] != 'X' && board[row][col] != 'O') {
            board[row][col] = mark;
            if (checkWinner(board)) {
                gameStatus = 1;
            } else if (isFull(board)) {
                break; // board full ? draw
            }
            player++;
        } else {
            printf("Invalid move! Try again.\n");
            getchar(); // consume newline
            getchar(); // wait for keypress
        }

    } while (gameStatus == 0);

    drawBoard(board);

    if (gameStatus == 1) {
        printf("==> Player %d wins!\n", player);
    } else {
        printf("==> Game draw!\n");
    }

    return 0;
}

// Function to draw the board
void drawBoard(char board[3][3]) { int i;
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printf("\nTIC TAC TOE\n");
    printf("Player 1 (X)  -  Player 2 (O)\n\n");

    for (i = 0; i < 3; i++) {
        printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        if (i < 2) printf("---|---|---\n");
    }
    printf("\n");
}

// Function to check winner
int checkWinner(char board[3][3]) { int i;
    // Check rows & columns
    for ( i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return 1;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return 1;
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return 1;

    return 0;
}

// Function to check if board is full
int isFull(char board[3][3]) { int i,j;
    for ( i = 0; i < 3; i++)
        for ( j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return 0;
    return 1;
}
