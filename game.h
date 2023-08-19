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


void print_board();

char check_winner(char board[3][3]);

int move_player(char player, int x, int y);

void reset_board();

int check_free_spaces(char board[3][3]);

void computer_move(char computer);

team get_player_team();

coordinate get_player_move();

char* input(char* prompt);

char** create_board();

char** move_result(char board[3][3], coordinate move, char computer);

void delete_board(char** board);

int minimax(char board[3][3], char computer);
