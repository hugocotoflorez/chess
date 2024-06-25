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

int board_move(Board board, Position from, Position to)
{
    int temp                   = board[to.i * 8 + to.j];
    board[to.i * 8 + to.j]     = board[from.i * 8 + from.j];
    board[from.i * 8 + from.j] = 0;
    return temp;
}

void board_restore(Board board, Position prev_from, Position prev_to, int temp)
{
    board[prev_from.i * 8 + prev_from.j] = board[prev_to.i * 8 + prev_to.j];
    board[prev_to.i * 8 + prev_to.j]     = temp;
}

int is_check(Board board, int turn)
{
    int king_pos;
    Board ret_board, temp;
    create_board(&ret_board);

    for (king_pos = 0; king_pos < 64; king_pos++)
    {
        if (board[king_pos] % 10 == KING)
            if (board[king_pos] / 10 != turn)
                break;
    }

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            if (i * 8 + j == king_pos)
                continue;
            if (board[i * 8 + j] != 0 && board[i * 8 + j] / 10 == turn)
            {
                temp = possible_movs(board, (Position){ i, j });
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

// have to be on check
bool is_checkmate(Board board, int turn, enum Options options)
{
    Board movs;
    int temp;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (board[i * 8 + j] != 0)
                if (board[i * 8 + j] / 10 != turn)
                {
                    movs = possible_movs(board, (Position){ i, j });
                    for (int ii = 0; ii < 8; ii++)
                        for (int jj = 0; jj < 8; jj++)
                            if (i == ii && j == jj)
                                continue;
                            else if (movs[ii * 8 + jj] != 0)
                            {
                                temp = board_move(
                                board, (Position){ i, j }, (Position){ ii, jj });
                                if (!is_check(board, turn))
                                {
                                    board_restore(board, (Position){ i, j },
                                    (Position){ ii, jj }, temp);
                                    free_board(movs);
                                    return false;
                                }
                                board_restore(board, (Position){ i, j },
                                (Position){ ii, jj }, temp);
                            }
                }
    free_board(movs);
    return true;
}

