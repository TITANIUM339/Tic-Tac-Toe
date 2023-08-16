#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
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

char check_winner();

int move_player(char player, int x, int y);

void reset_board();

int check_free_spaces();

void computer_move(char computer);

team get_player_team();

coordinate get_player_move();

char* input(char* prompt);
