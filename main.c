#include "chess.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

bool should_show_possible_movs(char* s, Position* position1)
{
    int temp;
    if (strlen(s) != 2)
        return false;

    temp = s[0] - 96;
    if (temp < 1 || temp > 8)
        return false;
    position1->j = temp - 1;

    temp = s[1] - 48;
    if (temp < 1 || temp > 8)
        return false;
    position1->i = 8 - temp;

    wprintf(L"Posi: (%d,%d)\n");

    return true;
}

bool transform_input(char* s, Position* position1, Position* position2)
{
    int temp;
    if (strlen(s) != 4)
        return false;

    temp = s[0] - 96;
    if (temp < 1 || temp > 8)
        return false;
    position1->j = temp - 1;

    temp = s[1] - 48;
    if (temp < 1 || temp > 8)
        return false;
    position1->i = 8 - temp;

    temp = s[2] - 96;
    if (temp < 1 || temp > 8)
        return false;
    position2->j = temp - 1;

    temp = s[3] - 48;
    if (temp < 1 || temp > 8)
        return false;
    position2->i = 8 - temp;

    return true;
}

enum TURN
{
    WHITE = 0,
    BLACK = 1,
};

int main()
{
    Board board;
    Position position1, position2;
    char input_buffer[4 + 1];
    Position offset = { 1, 1 };
    int options     = NONE;

    init_graphics();

    create_board(&board);
    if (!is_valid_board(board))
        DIE;

    init_board(board);
    print_board(board, offset, options);

    enum TURN turn = WHITE;
    while (!is_checkmate(board)) // main loop
    {
        wprintf(L"Move (<from><to>) -> ");
        scanf("%4s", input_buffer);
        if (!transform_input(input_buffer, &position1, &position2))
        {
            if (should_show_possible_movs(input_buffer, &position1))
                show_possible_movs(board, position1, offset, options);

            if (strlen(input_buffer) == 1 && input_buffer[0] == 'q')
                DIE;
            continue;
        }

        if (!can_move(position1, position2, board, options))
        {
            wprintf(L"Cant move (I)\n");
            continue;
        }
        if (!color_match(board, position1, turn))
        {
            wprintf(L"Cant move! (C)\n");
            continue;
        }

        board_move(board, position1, position2);

        // swap turn
        turn = (turn == WHITE) ? BLACK : WHITE;
        options = options & REVERSE_BOARD ? options & ~REVERSE_BOARD : options | REVERSE_BOARD;

        print_board(board, offset, options);
    }
    free_board(board);
    return 0;
}
