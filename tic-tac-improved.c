#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>

void board();
int range(int choice);
int cellChoice(int choice, char mark);
int checkMark(int choice);
int check_winner();
void recap();

char cell[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'}; 
char reset[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
char mark; 
int choice;
int turn = 0;
char playerOne[17];
char playerTwo[17];
char startGame;
char selectPlayer;

int main() {
    srand(time(NULL));

    do {
        printf("\n\t\t\t\t\t [ TIC TAC TOE ] \n");
        printf("\t\t\t Input the number corresponding to the box that you want to mark.");

        board(); 

        printf("\n\t\t\t|||||||||||||||||||||||||||||||||||||||||||||||||||||||");
        printf("\n\t\t\t\t           Start the game? ");
        printf("\n\t\t\t\t  Single Player Mode:   Type \"S\"");
        printf("\n\t\t\t\t    Two Player Mode:   Type \"M\"");
        printf("\n\t\t\t\t               Exit:   Type \"N\"");
        printf("\n\t\t\t|||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
        printf("\n\t\t\t\t\t      Enter: ");
        scanf(" %c", &startGame);
        fflush(stdin); 
        system("cls");
    } while (startGame != 'M' && startGame != 'm' && startGame != 'n' && startGame != 'N' && startGame != 'S' && startGame != 's');

    
    if (startGame == 'M' || startGame == 'm') {
        printf("\n\n\t\t\t\t\t     [ Two Player Mode ] ");
        printf("\n\n\t [ Player names can be up to 16 characters. ] \n");
        printf("\a\n\n\t Enter Name for Player 1 (X) : ");
        scanf("%s", playerOne);

        printf("\t Enter Name for Player 2 (O) : ");
        scanf("%s", playerTwo);

        system("cls"); 
        printf("\a");

        while (check_winner() == 0 && turn < 9) 
        {
            board();
            turn++; 

            if (turn % 2 == 0) 
            {
                mark = 'O';
                do 
                {
                    printf("\t (O) %s's turn : ", playerTwo);
                    scanf("%d", &choice);
                    fflush(stdin); 
                } while (range(choice) != 0 || checkMark(choice) != 0);

                if (checkMark(choice) == 0) 
                {
                    cellChoice(choice, mark); 
                }
            } else 
            {
                mark = 'X';
                do {
                    printf("\t (X) %s's turn : ", playerOne);
                    scanf("%d", &choice);
                    fflush(stdin); 
                } while (range(choice) != 0 || checkMark(choice) != 0);

                if (checkMark(choice) == 0) {
                    cellChoice(choice, mark);
                }
            }
            system("cls");
        }

        if (turn == 9 && check_winner() == 0) 
        {
            printf("\n\t It's a TIE, what an intense game! \a\n\n");
        }
        recap();
    } else if (startGame == 'N' || startGame == 'n') {
        printf("\n\n\t No one to play with? \a");
        printf("\n\t It's fine, we'll see you again next time! \n\n");
    }
    
    else if (startGame == 'S' || startGame == 's') {
        do {
            printf("\n\n\t\t\t\t\t     [ Single Player Mode ] ");
            printf("\n\n\t [Select Player Number (1 or 2)] \n");
            printf("\a\n\n\t Select player number: ");
            scanf(" %c", &selectPlayer);
            fflush(stdin); 
            system("cls");
            printf("\a");
        } while (selectPlayer != '1' && selectPlayer != '2');
        printf("\n\n\t\t\t\t\t     [ Single Player Mode ] ");
        if (selectPlayer == '1') {
            printf("\a\n\n\t You are player (X)");
            printf("\a\n\n\t Press any key to proceed...");
            getchar(); 
            system("cls");
        } else {
            printf("\a\n\n\t You are player (O)");
            printf("\a\n\n\t Press any key to proceed...");
            getchar(); 
            system("cls");
        }
        while (check_winner() == 0 && turn < 9) {
            board();
            turn++;
            if (selectPlayer == '2') {
                if (turn % 2 == 0) {
                    mark = 'O';
                    do {
                        printf("\t (O) %s's turn : ", playerTwo);
                        scanf("%d", &choice);
                        fflush(stdin); 
                    } while (range(choice) != 0 || checkMark(choice) != 0);
                    if (checkMark(choice) == 0) {
                        cellChoice(choice, mark);
                    }
                } else {
                    mark = 'X';
                    do {
                        int nRandom = (rand() % 9) + 1;
                        choice = nRandom;
                    } while (range(choice) != 0 || checkMark(choice) != 0);
                    if (checkMark(choice) == 0) {
                        printf("\t (X) Computer played number %d", choice);
                        cellChoice(choice, mark);
                    }
                }
                system("cls");
            } else {
                if (turn % 2 == 0) {
                    mark = 'O';
                    do {
                        int nRandom = (rand() % 9) + 1;
                        choice = nRandom;
                    } while (range(choice) != 0 || checkMark(choice) != 0);
                    if (checkMark(choice) == 0) {
                        printf("\t (O) Computer played number %d", choice);
                        cellChoice(choice, mark);
                    }
                } else {
                    mark = 'X';
                    do {
                        printf("\t (X) %s's turn : ", playerTwo);
                        scanf("%d", &choice);
                        fflush(stdin); 
                    } while (range(choice) != 0 || checkMark(choice) != 0);
                    if (checkMark(choice) == 0) {
                        cellChoice(choice, mark);
                    }
                }
            }
            system("cls");
        }
        if (turn == 9 && check_winner() == 0) {
            printf("\n\t It's a TIE, what an intense game! \a\n\n");
        }
        recap();
    }
    return 0;
}

void board() {
    printf("\n \n");
    printf("\t    NOTE: Choosing a box that has already been marked and numbers not within the 1-9 range \n");
    printf("\t          are considered invalid inputs. Player will be prompted to enter an input again. \n \n");
    printf("\n\n\t\t\t\t\t |-----------------| \n");
    printf("\t\t\t\t\t |  %c  |  %c  |  %c  | \n", cell[0], cell[1], cell[2]);
    printf("\t\t\t\t\t |-----+-----+-----| \n");
    printf("\t\t\t\t\t |  %c  |  %c  |  %c  | \n", cell[3], cell[4], cell[5]);
    printf("\t\t\t\t\t |-----+-----+-----| \n");//github.com/ean28//signature
    printf("\t\t\t\t\t |  %c  |  %c  |  %c  | \n", cell[6], cell[7], cell[8]);
    printf("\t\t\t\t\t |-----------------| \n\n");
}

int range(int choice) {
    if (choice < 1 || choice > 9) {
        return 1;
    } else {
        return 0;
    }
}

int cellChoice(int choice, char mark) {
    choice--;
    cell[choice] = mark;
    return 0;
}

int checkMark(int choice) {
    choice--;
    if (cell[choice] == 'X' || cell[choice] == 'O') {
        return 1;
    } else {
        return 0;
    }
}

int check_winner() {
    int winningCombinations[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
        {0, 4, 8}, {2, 4, 6}             // Diagonals
    };

    for (int i = 0; i < 8; i++) {
        int a = winningCombinations[i][0];
        int b = winningCombinations[i][1];
        int c = winningCombinations[i][2];

        if (cell[a] == cell[b] && cell[b] == cell[c]) {
            printf("\n\t Player %c has won the game. Well-played! \a\n\n", cell[a]);
            return 1;
        }
    }

    return 0;
}

void recap() {
    printf("\n\t Recap: \n");
    printf("\n\t |-----------------| \n");
    printf("\t |  %c  |  %c  |  %c  | \n", cell[0], cell[1], cell[2]);
    printf("\t |-----+-----+-----| \n");
    printf("\t |  %c  |  %c  |  %c  | \n", cell[3], cell[4], cell[5]);
    printf("\t |-----+-----+-----| \n");
    printf("\t |  %c  |  %c  |  %c  | \n", cell[6], cell[7], cell[8]);
    printf("\t |-----------------| \n\n\n");

    printf("\n\t Do you want to play again? \n\n\t Press 'Y' to continue. ");
    printf("\n\t Press any key to exit. \n\n ");
    printf("Enter: ");

    char input;
    scanf(" %c", &input);

    if (input == 'y' || input == 'Y') {
        system("cls");
        strncpy(cell, reset, 9);
        main();
    } else {
        system("cls");
        printf("\n\t Thank you for playing. Goodbye for now. \a\n\n");
    }
}

