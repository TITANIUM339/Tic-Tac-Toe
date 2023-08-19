#include "game.h"


char board[3][3];


void print_board()
{
    // Clears the screen.
    printf("\e[1;1H\e[2J");
    
    printf("\n");
    printf(" %c | %c | %c ", board[0][0], board[1][0], board[2][0]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[0][1], board[1][1], board[2][1]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[0][2], board[1][2], board[2][2]);
    printf("\n\n");
}


void reset_board()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}


int move_player(char player, int x, int y)
{
    // Checking if there is an empty space.
    if (board[x][y] == ' ')
    {
        board[x][y] = player;
        return 0;
    }

    return 1;
}


int check_free_spaces(char board[3][3])
{
    int count = 0;

    // Looping over rows.
    for (int i = 0; i < 3; i++)
    {
        // Looping over columns.
        for (int j = 0; j < 3; j++)
        {
            // Checking for a free space.
            if (board[i][j] == ' ')
            {
                count++;
            }
        }
    }

    return count;
}


void computer_move(char computer)
{
    
    int spaceCount = check_free_spaces(board);

    if (spaceCount == 0) return;

    // Array of all possible actions.
    coordinate actions[spaceCount];

    int count = 0;

    // Filling array with actions.
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                actions[count].x = i;
                actions[count].y = j;
                count++;
            }
        }
    }

    // X is the MAX and O is thi MIN player.
    int value = computer == 'X'? -9999:9999;

    coordinate bestMove;

    // Loop over all actions.
    for (int i = 0; i < spaceCount; i++)
    {
        // Result of made action.
        char** tmp = move_result(board, actions[i], computer);

        if (tmp == NULL) exit(1);

        char actionResult[3][3];

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                actionResult[i][j] = tmp[i][j];
            }
        }

        delete_board(tmp);

        // Game board value resulted from made action.
        int actionValue = minimax(actionResult, computer == 'X'? 'O':'X');

        // Max player will try to maximize value.
        if (computer == 'X')
        {
            if (actionValue > value)
            {
                value = actionValue;
                bestMove = actions[i];
            }
        }
        // Min player will try to minimize value.
        else
        {
            if (actionValue < value)
            {
                value = actionValue;
                bestMove = actions[i];
            }
        }
        
    }

    // Making move.
    board[bestMove.x][bestMove.y] = computer;
}


char check_winner(char board[3][3])
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


team get_player_team()
{
    team players;

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

        players.player1 = toupper(*tmp);
        free(tmp);

        if (players.player1 != 'X' && players.player1 != 'O')
        {
            printf("Invalid team.\n");
            continue;
        }
        // Assigning player2 their team.
        else if (players.player1 == 'X')
        {
            players.player2 = 'O';
        }
        else
        {
            players.player2 = 'X';
        }

        print_board();
        printf("Make a move!\n");

        break;
    }

    return players;
}


coordinate get_player_move()
{
    coordinate position;

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

        position.y = atoi(tmp);

        free(tmp);

        // Making sure player provided a valid move.
        if (position.y < 1 || position.y > 3)
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

        position.x = atoi(tmp);

        free(tmp);

        // Making sure player provided a valid move.
        if (position.x < 1 || position.x > 3)
        {
            printf("Invalid Move.\n");
            continue;
        }

        position.x--;
        position.y--;

        break;
    }

    return position;
}


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

        tmp = realloc(string, counter * sizeof (char));

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

char** create_board()
{
    char* values = calloc(9, sizeof (char));
    char** rows = malloc(3 * sizeof (char*));

    if (values == NULL || rows == NULL) exit(1);

    for (int i = 0; i < 3; i++)
    {
        // Assigning the memory address of the beginning of every 3 block chunks.
        rows[i] = values + i * 3;
    }

    return rows;
}

void delete_board(char** board)
{
    free(*board);
    free(board);
}

char** move_result(char board[3][3], coordinate move, char computer)
{
    char** boardCopy = create_board();

    // Copy board values.
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            boardCopy[i][j] = board[i][j];
        }
        
    }

    // Apply move to board copy.
    boardCopy[move.x][move.y] = computer;

    return boardCopy;
}

int minimax(char board[3][3], char computer)
{
    char winner = check_winner(board);
    int spaceCount = check_free_spaces(board);
    coordinate actions[spaceCount];
    int count = 0;

    // Returning the board value if the game has reached a terminal state.
    if (spaceCount == 0 || winner != ' ')
    {
        if (winner == 'X') return 1;
        if (winner == ' ') return 0;
        if (winner == 'O') return -1;   
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                actions[count].x = i;
                actions[count].y = j;
                count++;
            }
        }
    }
    
    // Max player.
    if (computer == 'X')
    {
        int value = -9999;

        for (int i = 0; i < spaceCount; i++)
        {
            char** tmp = move_result(board, actions[i], computer);
            
            if (tmp == NULL) exit(1);
            
            char actionResult[3][3];

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    actionResult[i][j] = tmp[i][j];
                }
                
            }
            
            delete_board(tmp);

            int actionValue = minimax(actionResult, 'O');
            
            if (actionValue > value) value = actionValue;
        }
        
        // Returns highest found value.
        return value;
    }
    // Min player.
    else
    {
        int value = 9999;

        for (int i = 0; i < spaceCount; i++)
        {
            char** tmp = move_result(board, actions[i], computer);

            if (tmp == NULL) exit(1);
            
            char actionResult[3][3];

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    actionResult[i][j] = tmp[i][j];
                }
                
            }
            
            delete_board(tmp);

            int actionValue = minimax(actionResult, 'X');

            if (actionValue < value) value = actionValue;
        }
        
        // Returns lowest found value.
        return value;
    }
}
