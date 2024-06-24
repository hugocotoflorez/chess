/**
 * Console chess implementation
 *
 * by Hugo Coto Florez
 * (https://github.com/hugocotoflorez/clchess)
 *
 */

#ifndef _CHESS_H
#define _CHESS_H

#include <stdbool.h>
#include <stdlib.h>

typedef int* Board;


typedef struct
{
    int i, j;
} Position;


typedef enum Piece
{
    KING = 1,
    QUEEN,
    BISHOP,
    KNIGHT,
    ROOK,
    PAWN
} Piece;

enum Options
{
    NONE          = 0x0,
    REVERSE_BOARD = 0x1 << 1,
};

enum Movs
{
    CANT_MOVE = 0,
    CAN_MOVE,
    CAN_CAPTURE,
    CAN_PROMOTE,
    SELF,
};

void init_graphics();
void print_board(Board board, Position offset, enum Options options);
void create_board(Board* board);
bool is_valid_board(Board board);
void init_board(Board board);
void free_board(Board board);

Board reverse_board(Board board);

Board possible_movs(Board board, Position position);
void show_possible_movs(Board board, Position position, Position offset, enum Options options);
int can_move(Position from, Position to, Board board, enum Options options);
void board_move(Board board, Position from, Position to);

bool is_checkmate(Board board);

bool color_match(Board board, Position position, int turn);

#define DIE exit(1);

#endif //_CHESS_H
