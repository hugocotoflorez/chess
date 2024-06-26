#include "chess.h"
#include <stdbool.h>
#include <stdio.h>
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

int board_move(Board board, Position from, Position to, enum Castle* castle_status)
{

    int temp;
    if (castle_status)
        if (*castle_status != CANT_CASTLE)
        {
            if (board[from.i * 8 + from.j] % 10 == KING)
            {
                *castle_status = CANT_CASTLE;
                if (board[to.i * 8 + to.j] % 10 == ROOK)
                {
                    if (from.j > to.j)
                    {
                        board_move(board, from, (Position){ from.i, from.j - 2 }, 0);
                        board_move(board, to, (Position){ from.i, from.j - 1 }, 0);
                    }
                    else
                    {
                        board_move(board, from, (Position){ from.i, from.j + 2 }, 0);
                        board_move(board, to, (Position){ from.i, from.j + 1 }, 0);
                    }
                    return 0;
                }
            }
            if (board[from.i * 8 + from.j] % 10 == ROOK)
            {
                if (from.i == 7 && from.j == 7)
                    *castle_status &= ~RIGHT_CASTLE;
                if (from.i == 0 && from.j == 0)
                    *castle_status &= ~RIGHT_CASTLE;
                if (from.i == 7 && from.j == 0)
                    *castle_status &= ~LEFT_CASTLE;
                if (from.i == 0 && from.j == 7)
                    *castle_status &= ~LEFT_CASTLE;
            }
        }
    temp                       = board[to.i * 8 + to.j];
    board[to.i * 8 + to.j]     = board[from.i * 8 + from.j];
    board[from.i * 8 + from.j] = 0;
    return temp;
}

void board_restore(Board board, Position prev_from, Position prev_to, int temp)
{
    board[prev_from.i * 8 + prev_from.j] = board[prev_to.i * 8 + prev_to.j];
    board[prev_to.i * 8 + prev_to.j]     = temp;
}

int is_check(Board board, int attack_color, enum Castle castle_status)
{
    int king_pos;
    Board ret_board, temp;
    create_board(&ret_board);

    for (king_pos = 0; king_pos < 64; king_pos++)
    {
        if (board[king_pos] % 10 == KING)
            if (board[king_pos] / 10 != attack_color)
                break;
    }

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            if (i * 8 + j == king_pos)
                continue;
            if (board[i * 8 + j] != 0 && board[i * 8 + j] / 10 == attack_color)
            {
                temp = possible_movs(board, (Position){ i, j }, CANT_CASTLE);
                for (int k = 0; k < 64; k++)
                {
                    ret_board[k] += temp[k] != 0 ? 1 : 0;
                }
                free_board(temp);
            }
        }
    int p = ret_board[king_pos];
    free_board(ret_board);
    return p;
}


int is_square_attacked(Board board, int attack_color, Position square)
{
    Board ret_board, temp;
    create_board(&ret_board);

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            if (board[i * 8 + j] != 0 && board[i * 8 + j] / 10 == attack_color)
            {
                temp = possible_movs(board, (Position){ i, j }, CANT_CASTLE);
                for (int k = 0; k < 64; k++)
                {
                    ret_board[k] += temp[k] != 0 ? 1 : 0;
                }
                free_board(temp);
            }
        }
    int p = ret_board[square.i * 8 + square.j];
    free_board(ret_board);
    return p;
}

// have to be on check
bool is_checkmate(Board board, int turn, enum Options options, enum Castle castle_status)
{
    int temp;
    Board movs;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (board[i * 8 + j] != 0)
                if (board[i * 8 + j] / 10 != turn)
                {
                    movs = possible_movs(board, (Position){ i, j }, castle_status);
                    for (int ii = 0; ii < 8; ii++)
                        for (int jj = 0; jj < 8; jj++)
                            if (i == ii && j == jj)
                                continue;
                            else if (movs[ii * 8 + jj] != 0)
                            {
                                temp = board_move(board, (Position){ i, j },
                                (Position){ ii, jj }, &castle_status);
                                if (!is_check(board, turn, castle_status))
                                {
                                    board_restore(board, (Position){ i, j },
                                    (Position){ ii, jj }, temp);
                                    free_board(movs);
                                    return false;
                                }
                                board_restore(board, (Position){ i, j },
                                (Position){ ii, jj }, temp);
                            }
                    free_board(movs);
                }
    return true;
}

void check_castling(enum Castle* castle_status, Board board, Position position1, enum Options options)
{
    if (*castle_status == CANT_CASTLE)
        return;

    if (options & REVERSE_BOARD)
        position1 = (Position){ 7 - position1.i, 7 - position1.j };

    if (position1.i == 0 && position1.j == 0)
        *castle_status &= ~LEFT_CASTLE;

    if (position1.i == 0 && position1.j == 7)
        *castle_status &= ~RIGHT_CASTLE;

    if (board[position1.i * 8 + position1.j] % 10 == KING)
        *castle_status &= ~BOTH_CASTLE;
}
