#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


extern char board[3][3];

typedef struct Team {
    char player1;
    char player2;
} team;

typedef struct Coordinate {
    int x;
    int y;
} coordinate;


// Prints the game board.
void print_board();

// Checks for a winner.
char check_winner(char board[3][3]);

// Moves player.
int move_player(char player, coordinate move);

// Resets game board.
void reset_board();

// Checks for free spaces on the game board.
int check_free_spaces(char board[3][3]);

// Computer makes move using minimax algorithm.
void computer_move(char computer);

// Prompts the player to select a team.
team get_player_team();

// Prompts the player for a move based on x, y coordinates.
coordinate get_player_move();

// Gets input from player, simillar to the input function in python.
char* input(char* prompt);

// Creates a new board.
char** create_board();

// Returns a new game board resulting from a move.
char** move_result(char board[3][3], coordinate move, char computer);

// Deletes a board created using the create_board() function.
void delete_board(char** board);

// The minimax algorithm.
int minimax(char board[3][3], char computer);
