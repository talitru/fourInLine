
/*
This program implement the game "four in line". the game is between two players:player number one-'X',
player number 2-'O'. one of the players win when he gets sequence of four 'X'/'O' respectively.
the sequence can be in four forms: vertical,horizontal,diagonally- from the two sides.
every turn the program gets from the current player a number of column(between 1-7) and set&print
 the sign of the player on the board.The progrm announce which of the players won or if there's a tie.
*/

//Name:Tali Terngo Truneh 

#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

/*************** Board ***************/
#define ROWS 6
#define COLS 7
char board[ROWS][COLS];

/*********** Declarations ************/

/// This function initializes the game board by assigning each cell
/// with ' ' (resulting with an empty game board).
void initBoard();

/// This function gets a row number and a column number (a cell),
/// and returns the character in that cell (could be 'X', 'O' or ' ').
/// For example:
/// char c = getCell(1, 1);
char getCell(int row, int col);

/// This function gets a row number, a column number and a sign,
/// and assigns the cell with the given sign.
/// For example:
/// setCell(1, 1, 'X');
void setCell(int row, int col, char sign);

/// This function clears the screen.
void clearScreen();

///This function print the board of the game
void PrintBoard();

///This function gets the sign of the player and checks if the current player won
///in one of the four forms of winning.
///The function returns true if the player won in one of the forms else- false.
bool IsThereAVictory(char signOfPlayer);

///This function checks if there is a tie between the players.
/// A tie happens when the board is full and no one won.
///If there is a tie the function returns true else- false.
bool IsThereATie();

///This function gets a number of column and checs if the column is full
/// if the column is full it returns '-1' else- it returns the number of the free row in this column.
int IsFull(int col);

const char player1 = 'X';
const char player2 = 'O';

/*************** Main ****************/
int main()
{
    int col;
    initBoard();
    PrintBoard();
    bool resVictory = false;
    bool resTie = false;

    while((resVictory == false) && (resTie == false))
    {
        printf("\nplayer number 1:\n");
        printf("Please enter column input (a number between 1-7):\n");
        scanf("%d", &col);
        while ((col > 7) || (col < 1))
        {
            printf("The col you entered is not between 1-7.\n");
            printf("Please enter column input(a number between 1 - 7) :\n");
            scanf("%d", &col);
        }

        int resFull = IsFull(col);
        while (resFull == -1)
        {
            printf("The col you entered is full.\n");
            printf("Please enter column input (a number between 1-7):\n");
            scanf("%d", &col);
            resFull = IsFull(col);
        }

        if (resFull != -1)
        {
            clearScreen();
            setCell(resFull, col, player1);
            PrintBoard();


            if(IsThereAVictory(player1))
            {
                printf("\nplayer number 1 won!:)\n");
                resVictory = true;
            }

            else if(IsThereATie())
            {
                printf("\nthere's a tie!\n");
                resTie = true;
            }

            else
            {
                printf("\nplayer number 2:\n");
                printf("Please enter column input (a number between 1-7):\n");
                scanf("%d", &col);
                while ((col > 7) || (col < 1))
                {
                    printf("The col you entered is not between 1-7.\n");
                    printf("Please enter column input(a number between 1 - 7) :\n");
                    scanf("%d", &col);
                }

                int resFull2 = IsFull(col);
                
                while (resFull2 == -1)
                {
                    printf("The col you entered is full.\n");
                    printf("Please enter column input (a number between 1-7):\n");
                    scanf("%d", &col);
                    resFull2 = IsFull(col);
                }
                if(resFull2 != -1)
                {
                    clearScreen();
                    setCell(resFull2, col, player2);
                    PrintBoard();
                    if(IsThereAVictory(player2))
                    {
                        printf("\nplayer number 2 won!:)\n");
                        resVictory = true;
                    }
                    else if(IsThereATie())
                    {
                        printf("\nthere's a tie!\n");
                        resTie = true;
                    }
                }
            }
        }
    }

}

/********** Implementations **********/
char getCell(int row, int col)
{
    return board[row - 1][col - 1];
}

void setCell(int row, int col, char sign)
{
    board[row - 1][col - 1] = sign;
}

void initBoard()
{
    int i, j;
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            setCell(i + 1, j + 1, ' ');
        }
    }
}

void clearScreen()
{
    system("cls");
}

void PrintBoard()
{
    int row,col;
    for (row = 0; row <=6; row++)
    {
        if (row == 0)
        {
            for (col = 0; col <= 7; col++)
            {
                if (col == 0)
                {
                    printf(" ");
                }
                else
                {
                    printf("    %d", col);
                }
            }

            printf("\n%c",'A');
            row = 1;
        }
        for (col = 1; col <= 7; col++)
        {
            printf("    %c",getCell(row,col));
        }

        if (row != 6)
        {
            printf("\n%c", 'A' + row);
        }
    }
}

bool IsThereAVictory(char signOfPlayer)
{

    int col, row,k, count;
    char ch;

    // This part of the function checks if there's a sequence
    //of 4 X or O (acoording to the input) vertically on the bord.
    //for example: X   or    O
    //             X         O
    //             X         O
    //             X         O
    for (col = 1; col <= 7; col++)
    {
        count = 0;
        for (row = 6; row >= 1; row--)
        {
            ch = getCell(row, col);
            if (ch == signOfPlayer)
            {
                count++;
            }
            else
            {
                count = 0;
            }
            if (count == 4)
            {
                return true;

            }
        }
    }

    //This part of the function checks if there's a sequence
    //of 4 X or O (acoording to the input) horizontally on the board.
    //For example:  X X X X
    //                or
    //              O O O O
    for (row = 6; row >= 1; row--)
    {
        count = 0;
        for (col = 1; col <=7; col++)
        {
            ch = getCell(row, col);
            if (ch == signOfPlayer)
            {
                count++;
            }
            else
            {
                count = 0;
            }
            if (count == 4)
            {
                return true;
            }
        }
    }

    //This part of the function checks if there's a
    //sequence of 4 X or O diagonally upward.
    //For example:    
    //            X  or    O
    //          X        O
    //        X        O
    //      X        O
    for (row = 6; row >=4; row--)
    {
        count = 0;
        for (col = 1; col <= 4; col++)
        {

            ch = getCell(row, col);
            if (ch == signOfPlayer)
            {
                for (k = 1; k <= 3; k++)
                {
                    if (getCell(row - k, col + k) == signOfPlayer)
                    {
                        count++;
                    }
                    else
                    {
                        count = 0;
                    }
                    if (count == 3)
                    {
                        return true;
                    }
                }
            }
        }
    }

    //This part of the function checks if there's a
    //sequence of 4 X or O diagonally downward.
    //For example:  
    //    X      or    O
    //      X            O
    //        X            O
    //          X            O
    for (row = 1; row <= 3;row++)
    {
        count = 0;

        for (col = 1; col <= 4; col++)
        {
            ch = getCell(row, col);
            if (ch == signOfPlayer)
            {
                for (k = 1; k <= 3; k++)
                {
                    if (getCell(row + k, col + k) == signOfPlayer)
                    {
                        count++;
                    }
                    else
                    {
                        count = 0;
                    }
                    if (count == 3)
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}


bool IsThereATie()
{
    int col, count = 0;
    for (col = 1; col <= 7; col++)
    {
        if (IsFull(col) == -1)
        {
            count++;

        }
    }
    if (count == 7)
    {
        return true;
    }

    return false;
}

int IsFull(int col)
{
    int row;
    char ch;

    for (row = 6; row >= 1; row--)
    {
        ch = getCell(row, col);
        if (ch == ' ')
        {

            return row;
        }
    }

    return -1;
}
