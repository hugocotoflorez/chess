#include "chess.h"
#include <locale.h>
#include <stdio.h>
#include <wchar.h>

typedef enum
{
    BLACK = 0,
    RED,
    GREEN,
    ORANGE,
    BLUE,
    PURPLE,
    CYAN,
    WHITE
} Color;

// piece color
#define PIECE_COLOR_WHITE WHITE
#define PIECE_COLOR_BLACK BLACK
// board color
#define BOARD_COLOR_WHITE WHITE
#define BOARD_COLOR_BLACK BLACK

// THEME
#define TRANSPARENT_THEME
// #define REALISTIC_THEME

void term_set_bg(Color c)
{
    wprintf(L"\e[%dm", 100 + c);
}

void term_set_fg(Color c)
{
    wprintf(L"\e[%dm", 30 + c);
}

void term_reset_color()
{
    wprintf(L"\e[0m");
}

void term_nl()
{
    putwchar(L'\n');
}

void term_goto(Position position)
{
    wprintf(L"\e[%d;%dH", position.i, position.j);
}

void term_clean()
{
    wprintf(L"\e[0m\e[H\e[J");
}

void term_hide_cursor()
{
    wprintf(L"\e[?25l");
}

void term_show_cursor()
{
    wprintf(L"\e[?25h");
}

void enable_wide_mode()
{
    setlocale(LC_ALL, "");
    fwide(stdout, 1);
}

#ifdef TRANSPARENT_THEME
wchar_t piece_repr[] = {
    [KING]   = L'',
    [QUEEN]  = L'',
    [BISHOP] = L'',
    [KNIGHT] = L'',
    [ROOK]   = L'',
    [PAWN]   = L'',
};
#elifdef REALISTIC_THEME
wchar_t piece_repr[] = {
    [KING]   = L'',
    [QUEEN]  = L'',
    [BISHOP] = L'',
    [KNIGHT] = L'',
    [ROOK]   = L'',
    [PAWN]   = L'',
};
#else
wchar_t piece_repr[] = {
    [KING]   = L'󰡗',
    [QUEEN]  = L'󰡚',
    [BISHOP] = L'󰡜',
    [KNIGHT] = L'󰡘',
    [ROOK]   = L'󰡛',
    [PAWN]   = L'󰡙',
};
#endif /* ifdef TRANSPARENT_THEME */


void init_graphics()
{
    enable_wide_mode();
}

void print_board(Board board, Position offset, enum Options options)
{
    Board temp_board = NULL; // just to reverse it easily
    if (options & REVERSE_BOARD)
        temp_board = reverse_board(board);
    else
        temp_board = board;

    term_clean();
    term_goto(offset);
    if (options & REVERSE_BOARD)
        wprintf(L"  H G F E D C B A");
    else
        wprintf(L"  A B C D E F G H");
    term_nl();
    for (int i = 0; i < 8; i++)
    {
        if (options & REVERSE_BOARD)
            wprintf(L"%d ", 1 + i);
        else
            wprintf(L"%d ", 8 - i);
        for (int j = 0; j < 8; j++)
        {
            term_set_bg(((i + j) % 2) ? BOARD_COLOR_BLACK : BOARD_COLOR_WHITE);
            switch (temp_board[i * 8 + j] % 10)
            {
                case KING:
                case QUEEN:
                case BISHOP:
                case KNIGHT:
                case ROOK:
                case PAWN:
                    term_set_fg((temp_board[i * 8 + j] >= 10) ? PIECE_COLOR_BLACK :
                                                                PIECE_COLOR_WHITE);
                    putwchar(piece_repr[temp_board[i * 8 + j] % 10]);
                    putwchar(' ');
                    term_reset_color();
                    break;
                default:
                    putwchar(' ');
                    putwchar(' ');
            }
            term_reset_color();
        }
        if (options & REVERSE_BOARD)
            wprintf(L" %d", 1 + i);
        else
            wprintf(L" %d", 8 - i);
        term_nl();
    }
    if (options & REVERSE_BOARD)
        wprintf(L"  H G F E D C B A");
    else
        wprintf(L"  A B C D E F G H");
    term_nl();
    fflush(stdout);
    if (options & REVERSE_BOARD)
        free_board(temp_board);
}

void show_possible_movs(Board board, Position position, Position offset, enum Options options, enum Castle castle_status)
{
    Board temp_board = NULL; // just to reverse it easily
    Board possible_movs_board;


    if (options & REVERSE_BOARD)
    {
        temp_board = reverse_board(board);
        position.i = 7 - position.i;
        position.j = 7 - position.j;
    }
    else
    {
        temp_board = board;
    }
    possible_movs_board = possible_movs(temp_board, position, castle_status);

    if (possible_movs_board == NULL) // trying to show no-piece movs
    {
        return;
    }

    term_clean();
    term_goto(offset);
    if (options & REVERSE_BOARD)
        wprintf(L"  H G F E D C B A");
    else
        wprintf(L"  A B C D E F G H");
    term_nl();
    for (int i = 0; i < 8; i++)
    {
        if (options & REVERSE_BOARD)
            wprintf(L"%d ", 1 + i);
        else
            wprintf(L"%d ", 8 - i);
        for (int j = 0; j < 8; j++)
        {
            switch (possible_movs_board[i * 8 + j])
            {
                case CAN_MOVE:
                    term_set_bg(CYAN);
                    break;
                case CAN_PROMOTE:
                    term_set_bg(ORANGE);
                    break;
                case CAN_CAPTURE:
                    term_set_bg(RED);
                    break;
                case SELF: // do nothing (default bg)
                case CANT_MOVE:
                    term_set_bg(((i + j) % 2) ? BOARD_COLOR_BLACK : BOARD_COLOR_WHITE);
                    break;
            }
            switch (temp_board[i * 8 + j] % 10)
            {
                case KING:
                case QUEEN:
                case BISHOP:
                case KNIGHT:
                case ROOK:
                case PAWN:
                    term_set_fg((temp_board[i * 8 + j] >= 10) ? PIECE_COLOR_BLACK :
                                                                PIECE_COLOR_WHITE);
                    putwchar(piece_repr[temp_board[i * 8 + j] % 10]);
                    putwchar(' ');
                    term_reset_color();
                    break;
                default:
                    putwchar(' ');
                    putwchar(' ');
            }
            term_reset_color();
        }
        if (options & REVERSE_BOARD)
            wprintf(L" %d", 1 + i);
        else
            wprintf(L" %d", 8 - i);
        term_nl();
    }
    if (options & REVERSE_BOARD)
        wprintf(L"  H G F E D C B A");
    else
        wprintf(L"  A B C D E F G H");
    term_nl();
    fflush(stdout);
    if (options & REVERSE_BOARD)
    {
        free_board(temp_board);
    }
    free_board(possible_movs_board);
}
