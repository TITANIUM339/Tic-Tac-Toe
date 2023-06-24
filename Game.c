#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


char player1, player2;
char computer;
char board[3][3];
int y, x;

void print_board();
char check_winner();
int move_player(char player, int x, int y);
void reset();
int check_free_spaces();
void get_computer_move(char computer);
void team_select();
void get_player_move();
char* input(char* prompt);


int main()
{
    // Initializing the random number generator.
    srand(time(NULL));

    // Player's response.
    char response;

    while (true)
    {
        // Player's selected option.
        int option;

        char* tmp;

        // Resetting game board.
        reset();

        // Printing out the options available to the player. 
        printf("\n1. Player1 vs Computer\n2. Player1 vs Player2\n\n");

        while (true)
        {
            // Prompting the player for an option.
            tmp = input("Select option (1, 2): ");

            if (tmp == NULL) return 1;

            if (strlen(tmp) > 1)
            {
                printf("Invalid Option.\n");
                free(tmp);
                continue;
            }

            option = atoi(tmp);

            free(tmp);

            // Making sure the player provided a valid option.
            if (option != 1 && option != 2)
            {
                printf("Invalid Option.\n");
                continue;
            }

            break;
        }

        // Player vs computer.
        if (option == 1)
        {
            // Prompting player to select team.
            team_select();

            do
            {
                // Prompting player for a move.
                get_player_move();


                // Making sure the player provided a valid move.
                if (move_player(player1, y, x))
                {
                    printf("Invalid Move.\n");
                }
                // Computer making a move.
                else
                {
                    get_computer_move(computer);
                    print_board();
                }
            }
            // Keep looping over until there is no more spaces left or a winner has been determined. 
            while (check_winner() == ' ' && check_free_spaces());

            // Determining who the winner is.
            if (check_winner() == player1)
            {
                printf("You Win!\n");
            }
            else if (check_winner() == computer)
            {
                printf("You Lose!\n");
            }
            else
            {
                printf("Tie!\n");
            }
        }
        // Player1 vs Player2.
        else
        {
            // Prompting player to select team.
            team_select();

            do
            {
                // Prompting Player1 for a move.
                printf("[Player1]\n");
                get_player_move();

                // Making sure Player1 provided a valid move.
                if (move_player(player1, y, x))
                {
                    printf("Invalid Move.\n");
                }
                else
                {
                    // Checking if no more spaces are left or a winner has been determined.
                    if (check_winner() != ' ' || !check_free_spaces())
                    {
                        print_board();
                        break;
                    }

                    print_board();

                    while (true)
                    {
                        // Prompting Player2 for a move.
                        printf("[Player2]\n");
                        get_player_move();

                        // Making sure Player2 provided a valid move.
                        if (move_player(player2, y, x))
                        {
                            printf("Invalid Move.\n");
                        }
                        else
                        {
                            break;
                        }
                    }

                    print_board();
                }
            }
            // Keep looping over until there is no more spaces left or a winner has been determined.
            while (check_winner() == ' ' && check_free_spaces());

            // Determining who the winner is.
            if (check_winner() == player1)
            {
                printf("Player1 Wins!\n");
            }
            else if (check_winner() == player2)
            {
                printf("Player2 Wins!\n");
            }
            else
            {
                printf("Tie!\n");
            }
        }

        while (true)
        {
            // Asking the Player if he wants to play again.
            tmp = input("Do you want to play again? (Y, N): ");

            if (tmp == NULL) return 1;

            // Making sure the Player provided a valid answer.
            if (strlen(tmp) > 1)
            {
                printf("Invalid Input.\n");
                free(tmp);
                continue;
            }

            response = toupper(*tmp);
            free(tmp);

            if (response != 'N' && response != 'Y')
            {
                printf("Invalid Input.\n");
                continue;
            }

            break;
        }

        // Stopping the game if the Player answered no (N).
        if (response == 'N')
        {
            printf("\nThanks for Playing!\n");
            break;
        }
    }

    return 0;
}


// Prints the game board.
void print_board()
{
    printf("\n");
    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n\n");
}


// Resets game board.
void reset()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}


// Moves player.
int move_player(char player, int y, int x)
{
    // Checking if there is an empty space.
    if (board[y][x] == ' ')
    {
        board[y][x] = player;
        return 0;
    }

    return 1;
}


// Checks for free spaces on the game board.
int check_free_spaces()
{
    // Looping over rows.
    for (int i = 0; i < 3; i++)
    {
        // Looping over columns.
        for (int j = 0; j < 3; j++)
        {
            // Checking for a free space.
            if (board[i][j] == ' ')
            {
                return 1;
            }
        }
    }

    return 0;
}


// Pseudo randomly generated computer move.
void get_computer_move(char computer)
{
    int y, x;

    if (check_free_spaces())
    {
        do
        {
            y = rand() % 3;
            x = rand() % 3;
        }
        while (board[y][x] != ' ');

        board[y][x] = computer;
    }
}


// Checking for a winner.
char check_winner()
{
    // Looping 3 times over rows and columns.
    for (int i = 0; i < 3; i++)
    {
        // Looking for a winner in rows.
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
        {
            return board[i][0];
        }

        // Looking for a winner in columns.
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
        {
            return board[0][i];
        }
    }

    // Looking diagonally (\) for a winner.
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
    {
        return board[0][0];
    }
    // Looking diagonally (/) for a winner.
    else if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
    {
        return board[0][2];
    }

    // Returning an empty space if there are no winners.
    return ' ';
}


// Prompts the player to select a team.
void team_select()
{
    while (true)
    {
        // Prompting player to select a team.
        char* tmp = input("Player1 choose your team (X, O): ");

        if (tmp == NULL) exit(1);

        // Making sure player provided a valid team.
        if (strlen(tmp) > 1)
        {
            printf("Invalid team.\n");
            free(tmp);
            continue;
        }

        player1 = toupper(*tmp);
        free(tmp);

        // Assigning other player's their team.
        if (player1 != 'X' && player1 != 'O')
        {
            printf("Invalid team.\n");
            continue;
        }
        else if (player1 == 'X')
        {
            computer = player2 = 'O';
        }
        else
        {
            computer = player2 = 'X';
        }

        print_board();
        printf("Make a move!\n");

        break;
    }
}

// Prompts the player for a move based on x, y coordinates.
void get_player_move()
{
    while (true)
    {
        // Prompting player for y coordinate.
        char* tmp = input("Row (1-3): ");

        if (tmp == NULL) exit(1);

        if (strlen(tmp) > 1)
        {
            printf("Invalid Move.\n");
            free(tmp);
            continue;
        }

        y = atoi(tmp);

        free(tmp);

        // Making sure player provided a valid move.
        if (y < 1 || y > 3)
        {
            printf("Invalid Move.\n");
            continue;
        }

        // // Prompting player for x coordinate.
        tmp = input("Column (1-3): ");

        if (tmp == NULL) exit(1);

        if (strlen(tmp) > 1)
        {
            printf("Invalid Move.\n");
            free(tmp);
            continue;
        }

        x = atoi(tmp);

        free(tmp);

        // Making sure player provided a valid move.
        if (x < 1 || x > 3)
        {
            printf("Invalid Move.\n");
            continue;
        }

        y--;
        x--;

        break;
    }
}

// Gets input from player, simillar to the input function in python.
char* input(char* prompt)
{
    char* string = NULL;
    char* tmp = NULL;
    char c = ' ';
    int counter;

    printf("%s", prompt);

    // Looping over player's input and resizing (string) accordingly. 
    for (counter = 1; c != '\n' && c != EOF; counter++)
    {
        c = getc(stdin);

        tmp = realloc(string, counter * sizeof *string);

        if (tmp == NULL)
        {
            free(string);
            return NULL;
        }

        string = tmp;

        string[counter - 1] = c;
    }

    // Assigning null to the end of the string;
    string[counter - 2] = '\0';

    return string;
}
