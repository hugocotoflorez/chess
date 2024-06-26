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

enum Castle
{
    CANT_CASTLE,
    RIGHT_CASTLE,
    LEFT_CASTLE,
    BOTH_CASTLE,
};

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

Board possible_movs(Board board, Position position, enum Castle castle_status);
void show_possible_movs(Board board,
Position position,
Position offset,
enum Options options,
enum Castle castle_status);
int can_move(Position from, Position to, Board board, enum Options options, enum Castle castle_status);
int board_move(Board board, Position from, Position to, enum Castle* castle_status);

int is_check(Board board, int turn, enum Castle castle_status);
bool is_checkmate(Board board, int turn, enum Options options, enum Castle castle_status);
int is_square_attacked(Board board, int turn, Position square);

bool color_match(Board board, Position position, int turn);

void check_castling(enum Castle* castle_status, Board board, Position position1, enum Options options);

#define DIE exit(1);

#endif //_CHESS_H
