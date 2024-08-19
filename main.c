#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char board[3][3];

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove(char);
void computerMove(char);
char checkWinner();
void printWinner(char, char, char);

int main() {
    char winner = ' ';
    char response = ' ';
    char PLAYER = ' ';
    char COMPUTER = ' ';
    int win_count = 0;
    int lose_count = 0;

    do {
        winner = ' ';
        response = ' ';
        PLAYER = ' ';
        COMPUTER = ' ';

        resetBoard();

        while(winner == ' ' && checkFreeSpaces() != 0) {
            printBoard();

            if (PLAYER == ' ' && COMPUTER == ' ') {
                printf("Choose a side (X or O):");
                scanf(" %c", &PLAYER);
                PLAYER = toupper(PLAYER);
                if (PLAYER == 'X') {
                    COMPUTER = 'O';
                } else if (PLAYER == 'O') {
                    COMPUTER = 'X';
                } else {
                    printf("Invalid input. Defaulting to X.\n");
                    PLAYER = 'X';
                    COMPUTER = 'O';
                }
            }

                playerMove(PLAYER);
                winner = checkWinner();
                if(winner != ' ' || checkFreeSpaces() == 0) {
                    break;
                }
                computerMove(COMPUTER);
                winner = checkWinner();
                if(winner != ' ' || checkFreeSpaces() == 0) {
                    break;
                }
            }
            printBoard();
            printWinner(winner, PLAYER, COMPUTER);
            if (winner == PLAYER) {
                win_count++;
            }
            else if (winner == COMPUTER) {
                lose_count++;
            }

            printf("\nWould you like to play again? (Y/N):");
            scanf(" %c", &response);
            response = toupper(response);
        } while (response == 'Y');

        printf("Thanks for playing!\n");
        printf("Win Count: %d\n", win_count);
        printf("Lose Count: %d\n", lose_count);

        return 0;
}

void resetBoard() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}
void printBoard() {
    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}
int checkFreeSpaces() {
    int freeSpaces = 9;

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i][j] != ' ') {
                freeSpaces--;
            }
        }
    }
    return freeSpaces;
}
void playerMove(char PLAYER) {
    int x;
    int y;

    do {
        printf("Enter row number(1-3):");
        scanf("%d", &x);
        x--;

        printf("Enter column number(1-3):");
        scanf("%d", &y);
        y--;

        if(board[x][y] != ' ') {
            printf("Invalid move!\n");
        }
        else {
            board[x][y] = PLAYER;
            break;
        }
    }while(board[x][y != ' ']);
}
void computerMove(char COMPUTER) {
    // creates a seed based on current time
    srand(time(0));
    int x;
    int y;

    if(checkFreeSpaces() > 0) {
        do {
            x = rand() % 3;
            y = rand() % 3;
        }while(board[x][y] != ' ');

        board[x][y] = COMPUTER;
    }
    else {
        printWinner(' ', ' ', ' ');
    }
}
char checkWinner() {
    //check rows
    for (int i = 0; i < 3; i++) {
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            return board[i][0];
        }
    }
    //check columns
    for (int i = 0; i < 3; i++) {
        if(board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
            return board[0][i];
        }
    }
    //check diagonal 1
    if(board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        return board[0][0];
    }
    //check diagonal 2
    if(board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        return board[0][2];
    }

    return ' ';
}
void printWinner(char winner, char PLAYER, char COMPUTER) {
    if(winner == PLAYER) {
        printf("YOU WIN!");
    }
    else if(winner == COMPUTER) {
        printf("YOU LOSE!");
    }
    else {
        printf("IT'S A TIE!");
    }
}