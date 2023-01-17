#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> //To be able to clear the console
// I will use 0 for empty space 1 for x and 2 for y
int playSpace[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
bool XWin = false, OWin = false, XTurn = false, play = true;
char *logo = "  _______ _____ _____ _______       _____ _______ ____  ______ \n |__   __|_   _/ ____|__   __|/\\   / ____|__   __/ __ \\|  ____|\n    | |    | || |       | |  /  \\ | |       | | | |  | | |__   \n    | |    | || |       | | / /\\ \\| |       | | | |  | |  __|  \n    | |   _| || |____   | |/ ____ \\ |____   | | | |__| | |____ \n    |_|  |_____\\_____|  |_/_/    \\_\\_____|  |_|  \\____/|______|\n\n\n";
void printPlaySpace()
{
    printf("\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (playSpace[i][j] == 0)
                printf("  ");
            else if (playSpace[i][j] == 1)
                printf(" X ");
            else
                printf(" O ");

            if (j != 2)
                printf("|");
            else
                printf("\n");
        }
        if (i != 2)
            printf("-----------\n");
        else
            printf("\n");
    }
}
void resetPlaySpace()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            playSpace[i][j] = 0;
    XWin = false;
    OWin = false;
}
void checkState()
{
    // Check row win condition
    int winner = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (j != 2)
            {
                winner = playSpace[i][j];
                if (playSpace[i][j] != playSpace[i][j + 1])
                {
                    winner = 0;
                    break;
                }
            }
        }
        if (winner > 0)
            break;
    }
    // Check column condition
    if (winner == 0)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (j != 2)
                    winner = playSpace[j][i];
                {
                    if (playSpace[j][i] != playSpace[j + 1][i])
                    {
                        winner = 0;
                        break;
                    }
                }
            }
            if (winner > 0)
                break;
        }
        // Check diagonal condition
        if (winner == 0)
        {
            if ((playSpace[0][0] == playSpace[1][1] && playSpace[1][1] == playSpace[2][2]) || (playSpace[0][2] == playSpace[1][1] && playSpace[1][1] == playSpace[2][0]))
                winner = playSpace[1][1];
        }
        if (winner == 0)
        {
            winner = -1;
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    if (playSpace[i][j] == 0)
                        winner = 0;
        }
    }
    if (winner == 0)
        return;
    if (winner == -1)
    {
        XWin = true;
        OWin = true;
    }
    else if (winner == 1)
        XWin = true;
    else
        OWin = true;
}
void gameLoop()
{
    char input[3];
    while (XWin == false && OWin == false)
    {
        printPlaySpace();
        printf("Where would you like to play next? (format is row,column NO SPACE)\n");
        gets(input);
        int row = input[0] - 48, column = input[2] - 48;
        while (row < 1 || row > 3 || column < 1 || column > 3 || playSpace[row - 1][column - 1] != 0)
        {
            if (playSpace[row - 1][column - 1] != 0)
            {
                printf("Location taken please choose another location\n");
                gets(input);
            }
            else
            {
                printf("Please put valid location (format is row,column NO SPACE)\n");
                gets(input);
            }
            row = input[0] - 48;
            column = input[2] - 48;
        }
        if (XTurn == true)
        {
            playSpace[row - 1][column - 1] = 1;
        }
        else
        {
            playSpace[row - 1][column - 1] = 2;
        }
        XTurn = !XTurn;
        checkState();
        printf("\n===================================\n");
    }
}

int main()
{
    char input[1];
    while (play)
    {
        system("CLS");
        // printf("\nWelcome To TICTACTOE!\n");
        printf(logo);
        printf("\nWould you like to play? (y/n)\n");
        gets(input);
        if (input[0] == 'n' || input[0] == 'N')
        {
            play = false;
        }
        else
        {
            system("CLS");
            gameLoop();
            if (XWin && OWin)
            {
                printf("\nDRAW\n");
            }
            else if (XWin)
            {
                printf("\nX WINS!!\n");
            }
            else if (OWin)
            {
                printf("\nO WINS!!\n");
            }
            system("pause");
            resetPlaySpace();
        }
    }
    return 0;
}