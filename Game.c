#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>


char player1, player2;
char computer;
char board[3][3];
int y, x;

void PrintBoard();
char CheckWinner();
int PlayerMove(char player, int x, int y);
void Reset();
int checkFreeSpaces();
void ComputerMove(char computer);
int Start();
void PlayerInput();

int main(void)
{
    srand(time(NULL));
    char response;

    while (true)
    {
        int option = 0;

        Reset();

        printf("Select Option:\n");
        printf("1. Player1 vs Computer\n2. Player1 vs Player2\n\n");

        scanf("%d", &option);

        if (option != 1 && option != 2)
        {
            printf("\nInvalid Option :(\n");
            return 1;
        }

        if (option == 1)
        {
            if (Start()) return 1;

            do
            {
                PlayerInput();

                if (PlayerMove(player1, y, x))
                {
                    printf("Invalid Move\n");
                }
                else
                {
                    ComputerMove(computer);
                    PrintBoard();
                }
            } while (CheckWinner() == ' ' && checkFreeSpaces());

            if (CheckWinner() == player1)
            {
                printf("You Won!\n");
            }
            else if (CheckWinner() == computer)
            {
                printf("You Lose!\n");
            }
            else
            {
                printf("Tie!\n");
            }
        }
        else
        {
            if (Start()) return 1;

            do
            {
                printf("Player1\n");
                PlayerInput();

                if (PlayerMove(player1, y, x))
                {
                    printf("Invalid Move\n");
                }
                else
                {
                    if (CheckWinner() != ' ' || !checkFreeSpaces())
                    {
                        PrintBoard();
                        break;
                    }

                    PrintBoard();
                    printf("Player2\n");

                    while (true)
                    {
                        PlayerInput();

                        if (PlayerMove(player2, y, x))
                        {
                            printf("Invalid Move\n");
                        }
                        else
                        {
                            break;
                        }
                    }

                    PrintBoard();
                }
            } while (CheckWinner() == ' ' && checkFreeSpaces());

            if (CheckWinner() == player1)
            {
                printf("Player1 Wins!\n");
            }
            else if (CheckWinner() == player2)
            {
                printf("Player2 Wins!\n");
            }
            else
            {
                printf("Tie!\n");
            }
        }

        printf("Do you want to play again? (Y, N)\n");
        scanf("%c");

        if (scanf("%c", &response) == 0 || (toupper(response) != 'N' && toupper(response) != 'Y'))
        {
            printf("Invalid Input\n");
            break;
        }
        else if (toupper(response) == 'N')
        {
            printf("\nThanks for Playing!\n");
            break;
        }
        else
        {
            continue;
        }
    }

    return 0;
} 


void PrintBoard()
{
    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n\n");
}


void Reset()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}


int PlayerMove(char player, int y, int x)
{
    if (board[y][x] == ' ')
    {
        board[y][x] = player;
        return 0;
    }

    return 1;
}


int checkFreeSpaces()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                return 1;
            }
        }
    }

    return 0;
}


void ComputerMove(char computer)
{
    int y, x;

    if (checkFreeSpaces())
    {
        do
        {
            y = rand() % 3;
            x = rand() % 3;
        } while (board[y][x] != ' ');

        board[y][x] = computer;
    }
}


char CheckWinner()
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
        {
            return board[i][0];
        }

        if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
        {
            return board[0][i];
        }
    }

    if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
    {
        return board[0][0];
    }
    else if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
    {
        return board[0][2];
    }

    return ' ';
}


int Start()
{
    char tmp;

    printf("Player1 choose your team (X, O)\n");
    scanf("%c");
    scanf("%c", &tmp);

    player1 = toupper(tmp);

    if (player1 != 'X' && player1 != 'O')
    {
        printf("Invalid team\n");
        return 1;
    }
    else if (player1 == 'X')
    {
        computer = player2 = 'O';
    }
    else
    {
        computer = player2 = 'X';
    }

    PrintBoard();
    printf("Make a move!\n");

    return 0;
}


void PlayerInput()
{
    while (true)
    {
        printf("row: ");
        scanf("%c");

        if (scanf("%d", &y) == 0 || y < 1 || y > 3)
        {
            printf("Invalid Move\n");
            continue;
        }
        else
        {
            while (true)
            {
                scanf("%c");
                printf("column: ");

                if (scanf("%d", &x) == 0 || x < 1 || x > 3)
                {
                    printf("Invalid Move\n");
                    continue;
                }
                else
                {
                    y--;
                    x--;
                    break;
                }
            }

            break;
        }
    }
}
