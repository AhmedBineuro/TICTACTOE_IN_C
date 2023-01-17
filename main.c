#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h> //To be able to clear the console
// I will use 0 for empty space 1 for x and 2 for y
int playSpace[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
bool XWin = false, OWin = false, XTurn = false, play = true;
char *logo = "  _______ _____ _____ _______       _____ _______ ____  ______ \n |__   __|_   _/ ____|__   __|/\\   / ____|__   __/ __ \\|  ____|\n    | |    | || |       | |  /  \\ | |       | | | |  | | |__   \n    | |    | || |       | | / /\\ \\| |       | | | |  | |  __|  \n    | |   _| || |____   | |/ ____ \\ |____   | | | |__| | |____ \n    |_|  |_____\\_____|  |_/_/    \\_\\_____|  |_|  \\____/|______|\n\n\n";
int AICHANCE;
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
        for (int j = 0; j < 2; j++)
        {
            winner = playSpace[i][j];
            if (playSpace[i][j] != playSpace[i][j + 1])
            {
                winner = 0;
                break;
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
            for (int j = 0; j < 2; j++)
            {
                winner = playSpace[j][i];
                if (playSpace[j][i] != playSpace[j + 1][i])
                {
                    winner = 0;
                    break;
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
void checkThreat()
{
    bool threat = false;
    bool potential = false;
    int tRow = -1, tCol = -1, pRow = -1, pCol = -1;
    // Check row win condition
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (playSpace[i][j] != 0)
            {

                if (j == 0)
                {
                    if (playSpace[i][j] == playSpace[i][j + 2] && playSpace[i][j + 1] == 0)
                    {
                        if (playSpace[i][j] == 1)
                        {
                            threat = true;
                            tRow = i;
                            tCol = j + 1;
                        }
                        else if (playSpace[i][j] == 2)
                        {
                            potential = true;
                            pRow = i;
                            pCol = j + 1;
                        }
                    }
                }
                if (playSpace[i][j] == playSpace[i][j + 1] && playSpace[i][j + 2] == 0)
                {
                    if (playSpace[i][j] == 1)
                    {
                        threat = true;
                        tRow = i;
                        tCol = j + 2;
                    }
                    else if (playSpace[i][j] == 2)
                    {
                        potential = true;
                        pRow = i;
                        pCol = j + 2;
                    }
                }
            }
        }
    }

    // Check column conditions
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (playSpace[j][i] != 0)
            {

                if (j == 0)
                {
                    if (playSpace[j][i] == playSpace[j + 2][i] && playSpace[j + 1][i] == 0)
                    {
                        if (playSpace[j][i] == 1)
                        {
                            threat = true;
                            tRow = j + 1;
                            tCol = i;
                        }
                        else if (playSpace[j][i] == 2)
                        {
                            potential = true;
                            pRow = j + 1;
                            pCol = i;
                        }
                    }
                }
                if (playSpace[j][i] == playSpace[j + 1][i] && playSpace[j + 2][i] == 0)
                {
                    if (playSpace[j][i] == 1)
                    {
                        threat = true;
                        tRow = j + 2;
                        tCol = i;
                    }
                    else if (playSpace[j][i] == 2)
                    {
                        potential = true;
                        pRow = j + 2;
                        pCol = i;
                    }
                }
            }
        }
    }

    /*
    check
     | |X
     | |
    X| |
    =====
    X| |
     | |
     | |X

    */
    if (playSpace[0][2] == playSpace[2][0] && playSpace[1][1] == 0)
    {
        if (playSpace[0][2] == 1)
        {
            threat = true;
            tRow = 1;
            tCol = 1;
        }
        else if (playSpace[0][2] == 2)
        {
            potential = true;
            pRow = 1;
            pCol = 1;
        }
    }
    if ((playSpace[0][0] == playSpace[2][2] && playSpace[1][1] == 0))
    {
        if (playSpace[0][0] == 1)
        {
            threat = true;
            tRow = 1;
            tCol = 1;
        }
        else if (playSpace[0][0] == 2)
        {
            potential = true;
            pRow = 1;
            pCol = 1;
        }
    }
    /*
check
 | |X
 |X|
 | |
=====
X| |
 |X|
 | |

*/
    if (playSpace[0][2] == playSpace[1][1] && playSpace[2][0] == 0)
    {
        if (playSpace[0][2] == 1)
        {
            threat = true;
            tRow = 2;
            tCol = 0;
        }
        else if (playSpace[0][2] == 2)
        {
            potential = true;
            pRow = 2;
            pCol = 0;
        }
    }
    if ((playSpace[0][0] == playSpace[1][1] && playSpace[2][2] == 0))
    {
        if (playSpace[0][0] == 1)
        {
            threat = true;
            tRow = 2;
            tCol = 2;
        }
        else if (playSpace[0][0] == 2)
        {
            potential = true;
            pRow = 2;
            pCol = 2;
        }
    }
    /*
check
 | |
 |X|
X| |
=====
 | |
 |X|
 | |X

*/
    if (playSpace[2][0] == playSpace[1][1] && playSpace[0][2] == 0)
    {
        if (playSpace[1][1] == 1)
        {
            threat = true;
            tRow = 0;
            tCol = 2;
        }
        else if (playSpace[1][1] == 2)
        {
            potential = true;
            pRow = 0;
            pCol = 2;
        }
    }
    if ((playSpace[2][2] == playSpace[1][1] && playSpace[0][0] == 0))
    {
        if (playSpace[1][1] == 1)
        {
            threat = true;
            tRow = 1;
            tCol = 1;
        }
        else if (playSpace[1][1] == 2)
        {
            potential = true;
            pRow = 0;
            pCol = 0;
        }
    }
    if (potential)
    {
        srand(clock());
        if (rand() % 100 > AICHANCE)
        {
            playSpace[pRow][pCol] = 2;
            XTurn = true;
            return;
        }
    }
    if (threat)
    {
        srand(clock());
        if (rand() % 100 > AICHANCE)
        {
            playSpace[tRow][tCol] = 2;
            XTurn = true;
            return;
        }
    }
    srand(clock());
    int row = rand() % 3;
    srand(clock());
    int col = rand() % 3;
    do
    {
        srand(clock());
        row = rand() % 3;
        srand(clock());
        col = rand() % 3;
    } while (playSpace[row][col] != 0);
    playSpace[row][col] = 2;
    XTurn = true;
    return;
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
        XTurn = !XTurn;
        if (XTurn == true)
        {
            playSpace[row - 1][column - 1] = 1;
        }
        else
        {
            playSpace[row - 1][column - 1] = 2;
        }
        checkState();
        printf("\n===================================\n");
    }
}
void gameLoopAI()
{
    srand(clock());
    XTurn = rand() % 2;
    char input[3];
    while (XWin == false && OWin == false)
    {
        printPlaySpace();
        if (XTurn)
        {
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
            playSpace[row - 1][column - 1] = 1;
        }
        checkState();
        checkThreat();
        checkState();
        printf("\n===================================\n");
    }
}
void setDifficulty(int dif)
{
    AICHANCE = (dif)*10;
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
            printf("\nAI? (y/n)\n");
            gets(input);
            if (input[0] == 'n' || input[0] == 'N')
            {
                system("CLS");
                gameLoop();
            }
            else
            {
                int difficulty = -1;
                while (difficulty > 4 || difficulty < 1)
                {

                    printf("\nDifficulty (1-easy 4-hard)? (y/n)\n");
                    gets(input);
                    difficulty = input[0] - 48;
                }
                setDifficulty(difficulty);
                system("CLS");
                gameLoopAI();
            }
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
    system("CLS");
    return 0;
}