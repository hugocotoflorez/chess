#include "chess.h"
#include <stdbool.h>
#include <stdlib.h>
#include <wchar.h>

void create_board(Board* board)
{
    *board = malloc(sizeof(int) * 64);
    for (int i = 0; i < 64; i++)
        (*board)[i] = 0;
}

bool is_valid_board(Board board)
{
    return board != NULL;
}


void free_board(Board board)
{
    free(board);
}

// place pieces in initial position
void init_board(Board board)
{
    board[0]  = 10 + ROOK;
    board[1]  = 10 + KNIGHT;
    board[2]  = 10 + BISHOP;
    board[3]  = 10 + QUEEN;
    board[4]  = 10 + KING;
    board[5]  = 10 + BISHOP;
    board[6]  = 10 + KNIGHT;
    board[7]  = 10 + ROOK;
    board[8]  = 10 + PAWN;
    board[9]  = 10 + PAWN;
    board[10] = 10 + PAWN;
    board[11] = 10 + PAWN;
    board[12] = 10 + PAWN;
    board[13] = 10 + PAWN;
    board[14] = 10 + PAWN;
    board[15] = 10 + PAWN;
    board[48] = PAWN;
    board[49] = PAWN;
    board[50] = PAWN;
    board[51] = PAWN;
    board[52] = PAWN;
    board[53] = PAWN;
    board[54] = PAWN;
    board[55] = PAWN;
    board[56] = ROOK;
    board[57] = KNIGHT;
    board[58] = BISHOP;
    board[59] = QUEEN;
    board[60] = KING;
    board[61] = BISHOP;
    board[62] = KNIGHT;
    board[63] = ROOK;
}


Board reverse_board(Board board)
{
    Board ret;
    create_board(&ret);
    for (int i = 0; i < 64; i++)
    {
        ret[63 - i] = board[i];
    }
    return ret;
}


void board_move(Board board, Position from, Position to)
{
    board[to.i * 8 + to.j]     = board[from.i * 8 + from.j];
    board[from.i * 8 + from.j] = 0;
}


bool is_checkmate(Board board)
{
    for (int i = 0; i < 64; i++)
    {
        if (board[i] % 10 == KING)
            ;
    }
    return false;
}
