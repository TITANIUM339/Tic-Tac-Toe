#include "game.h"

int main()
{
    // Initializing the random number generator.
    srand(time(NULL));

    while (true)
    {
        // Player's selected option.
        int option;

        char* tmp;

        // Resetting game board.
        reset_board();

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

        team players;

        // Player vs computer.
        if (option == 1)
        {
            // Prompting player to select team.
            players = get_player_team();

            do
            {
                // Prompting player for a move.
                coordinate position = get_player_move();

                // Making sure the player provided a valid move.
                if (move_player(players.player1, position.x, position.y))
                {
                    printf("Invalid Move.\n");
                }
                // Computer making a move.
                else
                {
                    computer_move(players.player2);
                    print_board();
                }
            }
            // Keep looping over until there is no more spaces left or a winner has been determined. 
            while (check_winner() == ' ' && check_free_spaces());
        }
        // Player1 vs Player2.
        else
        {
            // Prompting player to select team.
            players = get_player_team();

            do
            {
                // Prompting Player1 for a move.
                printf("[Player1]\n");
                coordinate position = get_player_move();

                // Making sure Player1 provided a valid move.
                if (move_player(players.player1, position.x, position.y))
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
                        
                        coordinate position = get_player_move();

                        // Making sure Player2 provided a valid move.
                        if (move_player(players.player2, position.x, position.y))
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
        }

        // Determining who the winner is.
        if (check_winner() == players.player1)
        {
            printf("Player1 Wins!\n");
        }
        else if (check_winner() == players.player2)
        {
            printf("Player2 Wins!\n");
        }
        else
        {
            printf("Tie!\n");
        }

        // Player's response.
        char response;

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
