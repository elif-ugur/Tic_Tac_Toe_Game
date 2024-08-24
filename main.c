#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char board[3][3];

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove(char);
void computerMove(char, int, char);
char checkWinner();
void printWinner(char, char, char);
void chooseSymbol(char*, char*);
void firstMode(int, char*, char, char, int);
void secondMode(int, char*, char, char, int);
void thirdMode(int, char*, char, char, int);
void playingSequence(int, char*, char, char, int);
int minimax(char[3][3], int, int, char, char);


int main() {
    char winner = ' ';
    char response = ' ';
    char PLAYER = ' ';
    char COMPUTER = ' ';
    int win_count = 0;
    int lose_count = 0;
    int tie_count = 0;
    int turn = 0;
    int difficulty = 0;

    do {
        winner = ' ';
        response = ' ';
        PLAYER = ' ';
        COMPUTER = ' ';
        turn = 0;

        resetBoard();

        printf("Choose the difficulty (1/2/3):\n");
        scanf(" %d", &difficulty);

        if (difficulty != 1 && difficulty != 2 && difficulty != 3){
            printf("Invalid input\n");
            continue;
        }

        printf("Choose your turn (1 for player first, 2 for computer first):\n");
        scanf(" %d", &turn);

        if (PLAYER == ' ' && COMPUTER == ' ') {
            chooseSymbol(&PLAYER, &COMPUTER);
        }

        if (difficulty == 1) {
            firstMode(turn, &winner, PLAYER, COMPUTER, difficulty);
        }
        else if (difficulty == 2) {
            secondMode(turn, &winner, PLAYER, COMPUTER, difficulty);
        }
        else if (difficulty == 3) {
            thirdMode(turn, &winner, PLAYER, COMPUTER, difficulty);
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
void computerMove(char COMPUTER, int difficulty, char PLAYER) {
    if (difficulty == 1) {
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
    else if (difficulty == 2) {
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
            computerMove(COMPUTER, difficulty, PLAYER);
        }
    }
    else if (difficulty == 3) {
        int bestScore = -1000;
        int move[2] = {-1, -1};

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(board[i][j] == ' ') {
                    board[i][j] = COMPUTER;
                    int score = minimax(board, 0, 0, COMPUTER, PLAYER);
                    board[i][j] = ' ';
                    if(score > bestScore) {
                        bestScore = score;
                        move[0] = i;
                        move[1] = j;
                    }
                }
            }
        }
        board[move[0]][move[1]] = COMPUTER;
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
void firstMode(int turn, char* winner, char PLAYER, char COMPUTER, int difficulty) {
    playingSequence(turn, winner, PLAYER, COMPUTER, difficulty);
}
void secondMode(int turn, char* winner, char PLAYER, char COMPUTER, int difficulty) {
    playingSequence(turn, winner, PLAYER, COMPUTER, difficulty);
}

void thirdMode(int turn, char* winner, char PLAYER, char COMPUTER, int difficulty) {
    playingSequence(turn, winner, PLAYER, COMPUTER, difficulty);
}

void playingSequence(int turn, char* winner, char PLAYER, char COMPUTER, int difficulty) {
    if (turn == 1) {
        while(*winner == ' ' && checkFreeSpaces() != 0) {
            printBoard();

            playerMove(PLAYER);
            *winner = checkWinner();
            if(*winner != ' ' || checkFreeSpaces() == 0) {
                break;
            }
            computerMove(COMPUTER, difficulty, PLAYER);
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

        computerMove(COMPUTER, difficulty, PLAYER);
        *winner = checkWinner();
        if (*winner != ' ' || checkFreeSpaces() == 0) {
            printBoard();
            printWinner(*winner, PLAYER, COMPUTER);
            return;
        }

        while (*winner == ' ' && checkFreeSpaces() != 0) {
            printBoard();

            playerMove(PLAYER);
            *winner = checkWinner();
            if (*winner != ' ' || checkFreeSpaces() == 0) {
                break;
            }

            computerMove(COMPUTER, difficulty, PLAYER);
            *winner = checkWinner();
            if (*winner != ' ' || checkFreeSpaces() == 0) {
                break;
            }
        }
    }
}

int minimax(char board[3][3], int depth, int isMaximizing, char COMPUTER, char PLAYER) {
    int result = checkWinner();
    if (result == COMPUTER) {
        return 10 - depth;
    }
    else if (result == PLAYER) {
        return depth - 10;
    }
    else if (checkFreeSpaces() == 0) {
        return 0;
    }

    if(isMaximizing) {
        int bestScore = -1000;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(board[i][j] == ' ') {
                    board[i][j] = COMPUTER;
                    int score = minimax(board, depth + 1, 0, COMPUTER, PLAYER);
                    board[i][j] = ' ';
                    bestScore = (score > bestScore) ? score : bestScore;
                    }
                }
            }
        return bestScore;
        }
    else {
        int bestScore = 1000;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(board[i][j] == ' ') {
                    board[i][j] = PLAYER;
                    int score = minimax(board, depth + 1, 1, COMPUTER, PLAYER);
                    board[i][j] = ' ';
                    bestScore = (score < bestScore) ? score : bestScore;
                }
            }
        }
        return bestScore;
    }
}