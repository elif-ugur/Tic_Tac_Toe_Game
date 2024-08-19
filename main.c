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
void chooseSymbol(char*, char*);
void easyMode(int, char*, char, char);
void hardMode(int, char*, char, char);
void computerMoveHard(char);


int main() {
    char winner = ' ';
    char response = ' ';
    char PLAYER = ' ';
    char COMPUTER = ' ';
    int win_count = 0;
    int lose_count = 0;
    int tie_count = 0;
    int turn = 0;
    char difficulty = ' ';

    do {
        winner = ' ';
        response = ' ';
        PLAYER = ' ';
        COMPUTER = ' ';
        turn = 0;

        resetBoard();

        printf("Choose the difficulty (e for easy / h for hard):\n");
        scanf(" %c", &difficulty);
        difficulty = tolower(difficulty);

        if (difficulty != 'e' && difficulty != 'h') {
            printf("Invalid input\n");
            continue;
        }

        printf("Choose your turn (1 for player first, 2 for computer first):\n");
        scanf(" %d", &turn);

        if (PLAYER == ' ' && COMPUTER == ' ') {
            chooseSymbol(&PLAYER, &COMPUTER);
        }

        if (difficulty == 'e') {
            easyMode(turn, &winner, PLAYER, COMPUTER);
        }
        else if (difficulty == 'h') {
            hardMode(turn, &winner, PLAYER, COMPUTER);
        }

        printBoard();
        printWinner(winner, PLAYER, COMPUTER);
        if (winner == PLAYER) {
            win_count++;
        }
        else if (winner == COMPUTER) {
            lose_count++;
        }
        else {
            tie_count++;
        }

        printf("\nWould you like to play again? (Y/N):");
        scanf(" %c", &response);
        response = toupper(response);
    } while (response == 'Y');

    printf("Thanks for playing!\n");
    printf("Win Count: %d\n", win_count);
    printf("Tie Count: %d\n", tie_count);
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
    }while(board[x][y] != ' ');
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
void chooseSymbol(char* PLAYER, char* COMPUTER) {
    char symbol;
    printf("Choose a side (X or O):");
    scanf(" %c", &symbol);
    symbol = toupper(symbol);

    if (symbol == 'X') {
        *PLAYER = 'X';
        *COMPUTER = 'O';
    } else if (symbol == 'O') {
        *PLAYER = 'O';
        *COMPUTER = 'X';
    } else {
        printf("Invalid input. Defaulting to X.\n");
        *PLAYER = 'X';
        *COMPUTER = 'O';
    }
}
void easyMode(int turn, char* winner, char PLAYER, char COMPUTER) {
    if (turn == 1) {
        while(*winner == ' ' && checkFreeSpaces() != 0) {
            printBoard();

            playerMove(PLAYER);
            *winner = checkWinner();
            if(*winner != ' ' || checkFreeSpaces() == 0) {
                break;
            }
            computerMove(COMPUTER);
            *winner = checkWinner();
            if(*winner != ' ' || checkFreeSpaces() == 0) {
                break;
            }
        }
    }
    else if (turn == 2) {
        if (PLAYER == ' ' && COMPUTER == ' ') {
            chooseSymbol(&PLAYER, &COMPUTER);
        }

        computerMove(COMPUTER);
        while(*winner == ' ' && checkFreeSpaces() != 0) {
            printBoard();

            playerMove(PLAYER);
            *winner = checkWinner();
            if(*winner != ' ' || checkFreeSpaces() == 0) {
                break;
            }
            computerMove(COMPUTER);
            *winner = checkWinner();
            if(*winner != ' ' || checkFreeSpaces() == 0) {
                break;
            }
        }
    }
}
void hardMode(int turn, char* winner, char PLAYER, char COMPUTER) {
    if (turn == 1) {
        while(*winner == ' ' && checkFreeSpaces() > 0) {
            printBoard();

            playerMove(PLAYER);
            *winner = checkWinner();
            if(*winner != ' ' || checkFreeSpaces() == 0) {
                break;
            }
            computerMoveHard(COMPUTER);
            *winner = checkWinner();
            if(*winner != ' ' || checkFreeSpaces() == 0) {
                break;
            }
        }
    }
    else if (turn == 2) {
        if (PLAYER == ' ' && COMPUTER == ' ') {
            chooseSymbol(&PLAYER, &COMPUTER);
        }
        computerMoveHard(COMPUTER);
        while(*winner == ' ' && checkFreeSpaces() != 0) {
            printBoard();

            playerMove(PLAYER);
            *winner = checkWinner();
            if(*winner != ' ' || checkFreeSpaces() == 0) {
                break;
            }
            computerMoveHard(COMPUTER);
            *winner = checkWinner();
            if(*winner != ' ' || checkFreeSpaces() == 0) {
                break;
            }
        }
    }
}
void computerMoveHard(char COMPUTER) {
    int x;
    int y;
    int alternative_moves[][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
    int size1 = sizeof(alternative_moves)/sizeof(alternative_moves[0]);
    int empty_alternative_moves[size1][2];
    int size2 = 0;


    if(board[1][1] == ' ') {
        board[1][1] = COMPUTER;
        return;
    }

    for(int i = 0; i < size1; i++) {
        x = alternative_moves[i][0];
        y = alternative_moves[i][1];
        if(board[x][y] == ' ') {
            empty_alternative_moves[size2][0] = x;
            empty_alternative_moves[size2][1] = y;
            size2++;
        }
    }

    if (size2 > 0) {
        int random = rand() %size2;
        x  = empty_alternative_moves[random][0];
        y  = empty_alternative_moves[random][1];
        board[x][y] = COMPUTER;
    }
    else {
        computerMove(COMPUTER);
    }
}