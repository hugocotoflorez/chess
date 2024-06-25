#include "chess.h"
#include <stdbool.h>

/*
 * Este archivo se deberia rescribir esta un poco hardcodeado
 * (no lo voy a hacer, funciona)
 */

Board possible_movs_king(Board board, Position position)
{
    Board ret_board;
    create_board(&ret_board);
    ret_board[position.i * 8 + position.j] = SELF;
    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++)
        {
            if (i == 0 && j == 0)
                continue;
            if ((position.i + i) * 8 + position.j + j < 0 ||
            (position.i + i) * 8 + position.j + j > 63)
                continue;
            ret_board[(position.i + i) * 8 + position.j + j] =
            (board[(position.i + i) * 8 + position.j + j] == 0) ? CAN_MOVE : CAN_CAPTURE;
        }
    return ret_board;
}

Board possible_movs_queen(Board board, Position position)
{
    Board ret_board;
    int pos;
    create_board(&ret_board);
    ret_board[position.i * 8 + position.j] = SELF;
    for (int i = position.i + 1; i < 8; i++)
    {
        if (board[i * 8 + position.j] != 0)
        {
            ret_board[i * 8 + position.j] = CAN_CAPTURE;
            break;
        }
        else
            ret_board[i * 8 + position.j] = CAN_MOVE;
    }
    for (int i = position.i - 1; i >= 0; i--)
    {
        if (board[i * 8 + position.j] != 0)
        {
            ret_board[i * 8 + position.j] = CAN_CAPTURE;
            break;
        }
        else
            ret_board[i * 8 + position.j] = CAN_MOVE;
    }
    for (int j = position.j + 1; j < 8; j++)
    {
        if (board[(position.i) * 8 + j] != 0)
        {
            ret_board[(position.i) * 8 + j] = CAN_CAPTURE;
            break;
        }
        else
            ret_board[(position.i) * 8 + j] = CAN_MOVE;
    }
    for (int j = position.j - 1; j >= 0; j--)
    {
        if (board[(position.i) * 8 + j] != 0)
        {
            ret_board[(position.i) * 8 + j] = CAN_CAPTURE;
            break;
        }
        else
            ret_board[(position.i) * 8 + j] = CAN_MOVE;
    }
    for (int k = 1; k < 8; k++)
    {
        pos = (position.i - k) * 8 + position.j - k;
        if (position.i - k < 0 || position.j - k < 0)
            break;
        if (board[pos] == 0)
            ret_board[pos] = CAN_MOVE;
        else
        {
            ret_board[pos] = CAN_CAPTURE;
            break;
        }
    }

    for (int k = 1; k < 8; k++)
    {
        pos = (position.i + k) * 8 + position.j + k;
        if (position.i + k > 7 || position.j + k > 7)
            break;
        if (board[pos] == 0)
            ret_board[pos] = CAN_MOVE;
        else
        {
            ret_board[pos] = CAN_CAPTURE;
            break;
        }
    }
    for (int k = 1; k < 8; k++)
    {
        pos = (position.i - k) * 8 + position.j + k;
        if (position.i - k < 0 || position.j + k > 7)
            break;
        if (board[pos] == 0)
            ret_board[pos] = CAN_MOVE;
        else
        {
            ret_board[pos] = CAN_CAPTURE;
            break;
        }
    }
    for (int k = 1; k < 8; k++)
    {
        pos = (position.i + k) * 8 + position.j - k;
        if (position.i + k > 7 || position.j - k < 0)
            break;
        if (board[pos] == 0)
            ret_board[pos] = CAN_MOVE;
        else
        {
            ret_board[pos] = CAN_CAPTURE;
            break;
        }
    }
    return ret_board;
}

Board possible_movs_bishop(Board board, Position position)
{
    Board ret_board;
    int pos;
    create_board(&ret_board);
    ret_board[position.i * 8 + position.j] = SELF;

    for (int k = 1; k < 8; k++)
    {
        pos = (position.i - k) * 8 + position.j - k;
        if (position.i - k < 0 || position.j - k < 0)
            break;
        if (board[pos] == 0)
            ret_board[pos] = CAN_MOVE;
        else
        {
            ret_board[pos] = CAN_CAPTURE;
            break;
        }
    }

    for (int k = 1; k < 8; k++)
    {
        pos = (position.i + k) * 8 + position.j + k;
        if (position.i + k > 7 || position.j + k > 7)
            break;
        if (board[pos] == 0)
            ret_board[pos] = CAN_MOVE;
        else
        {
            ret_board[pos] = CAN_CAPTURE;
            break;
        }
    }
    for (int k = 1; k < 8; k++)
    {
        pos = (position.i - k) * 8 + position.j + k;
        if (position.i - k < 0 || position.j + k > 7)
            break;
        if (board[pos] == 0)
            ret_board[pos] = CAN_MOVE;
        else
        {
            ret_board[pos] = CAN_CAPTURE;
            break;
        }
    }
    for (int k = 1; k < 8; k++)
    {
        pos = (position.i + k) * 8 + position.j - k;
        if (position.i + k > 7 || position.j - k < 0)
            break;
        if (board[pos] == 0)
            ret_board[pos] = CAN_MOVE;
        else
        {
            ret_board[pos] = CAN_CAPTURE;
            break;
        }
    }
    return ret_board;
}

Board possible_movs_knight(Board board, Position position)
{
    Board ret_board;
    int pos;
    create_board(&ret_board);
    ret_board[position.i * 8 + position.j] = SELF;

    for (int i = -2; i <= 2; i++)
        for (int j = -2; j <= 2; j++)
        {
            if (i == j)
                continue;
            if (i == -j)
                continue;
            if (i == 0 || j == 0)
                continue;
            if (position.i + i < 0)
                continue;
            if (position.i + i > 7)
                continue;
            if (position.j + j < 0)
                continue;
            if (position.j + j > 7)
                continue;

            pos            = (position.i + i) * 8 + position.j + j;
            ret_board[pos] = board[pos] == 0 ? CAN_MOVE : CAN_CAPTURE;
        }
    return ret_board;
}

Board possible_movs_rook(Board board, Position position)
{
    Board ret_board;
    create_board(&ret_board);
    ret_board[position.i * 8 + position.j] = SELF;
    for (int i = position.i + 1; i < 8; i++)
    {
        if (board[i * 8 + position.j] != 0)
        {
            ret_board[i * 8 + position.j] = CAN_CAPTURE;
            break;
        }
        else
            ret_board[i * 8 + position.j] = CAN_MOVE;
    }
    for (int i = position.i - 1; i >= 0; i--)
    {
        if (board[i * 8 + position.j] != 0)
        {
            ret_board[i * 8 + position.j] = CAN_CAPTURE;
            break;
        }
        else
            ret_board[i * 8 + position.j] = CAN_MOVE;
    }
    for (int j = position.j + 1; j < 8; j++)
    {
        if (board[(position.i) * 8 + j] != 0)
        {
            ret_board[(position.i) * 8 + j] = CAN_CAPTURE;
            break;
        }
        else
            ret_board[(position.i) * 8 + j] = CAN_MOVE;
    }
    for (int j = position.j - 1; j >= 0; j--)
    {
        if (board[(position.i) * 8 + j] != 0)
        {
            ret_board[(position.i) * 8 + j] = CAN_CAPTURE;
            break;
        }
        else
            ret_board[(position.i) * 8 + j] = CAN_MOVE;
    }

    return ret_board;
}

Board possible_movs_pawn(Board board, Position position)
{
    Board ret_board;
    create_board(&ret_board);
    ret_board[position.i * 8 + position.j] = SELF;
    // move up
    ret_board[(position.i - 1) * 8 + position.j] =
    (board[(position.i - 1) * 8 + position.j] != 0) ? CANT_MOVE : CAN_MOVE;
    // move up-right
    ret_board[(position.i - 1) * 8 + position.j + 1] =
    (board[(position.i - 1) * 8 + position.j + 1] != 0) ? CAN_CAPTURE : CANT_MOVE;
    // move up-left
    ret_board[(position.i - 1) * 8 + position.j - 1] =
    (board[(position.i - 1) * 8 + position.j - 1] != 0) ? CAN_CAPTURE : CANT_MOVE;
    if (position.i == 6)
        ret_board[(position.i - 2) * 8 + position.j] =
        (board[(position.i - 2) * 8 + position.j] != 0) ? CANT_MOVE : CAN_MOVE;

    return ret_board;
}

void fix_self_capture(Board board, Board possible_movs_board, Position position)
{
    int self_color = board[position.i * 8 + position.j] / 10;
    for (int i = 0; i < 64; i++)
        if (possible_movs_board[i] == CAN_CAPTURE)
            if (board[i] / 10 == self_color)
                possible_movs_board[i] = 0;
}

Board possible_movs(Board board, Position position)
{
    Board possible_movs_board;
    switch (board[position.i * 8 + position.j] % 10)
    {
        case PAWN:
            possible_movs_board = possible_movs_pawn(board, position);
            break;
        case KING:
            // TODO: cant move to check possition
            possible_movs_board = possible_movs_king(board, position);
            break;
        case QUEEN:
            possible_movs_board = possible_movs_queen(board, position);
            break;
        case BISHOP:
            possible_movs_board = possible_movs_bishop(board, position);
            break;
        case KNIGHT:
            possible_movs_board = possible_movs_knight(board, position);
            break;
        case ROOK:
            possible_movs_board = possible_movs_rook(board, position);
            break;
        default:
            create_board(&possible_movs_board);
    }
    fix_self_capture(board, possible_movs_board, position);
    return possible_movs_board;
}

int can_move(Position from, Position to, Board board, enum Options options)
{
    Board b;
    Position posi_from;
    Position posi_to;
    if (options & REVERSE_BOARD)
    {
        b         = reverse_board(board);
        posi_from = (Position){ 7 - from.i, 7 - from.j };
        posi_to   = (Position){ 7 - to.i, 7 - to.j };
    }
    else
    {
        b         = board;
        posi_from = from;
        posi_to   = to;
    }
    int p = possible_movs(b, posi_from)[posi_to.i * 8 + posi_to.j];
    if (options & REVERSE_BOARD)
        free_board(b);
    return p;
}

bool color_match(Board board, Position position, int turn)
{
    return turn == board[position.i * 8 + position.j] / 10;
}
