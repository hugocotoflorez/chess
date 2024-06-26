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
    BLACK = 1
};

int main(void)
{
    Board board;
    Position position1, position2;
    char input_buffer[4 + 1];
    Position offset             = { 1, 1 };
    int options                 = NONE;
    bool checkmate              = false;
    enum TURN turn              = WHITE;
    enum Castle castle_status[] = { BOTH_CASTLE, BOTH_CASTLE };

    init_graphics();
    create_board(&board);
    if (!is_valid_board(board))
        DIE;

    init_board(board);
    print_board(board, offset, options);

    while (!checkmate) // main loop
    {
        wprintf(L"[%s] -> ", turn ? "Black" : "White");
        scanf("%4s", input_buffer);
        if (!transform_input(input_buffer, &position1, &position2))
        {
            if (should_show_possible_movs(input_buffer, &position1))
                show_possible_movs(board, position1, offset, options, castle_status[turn]);

            if (strlen(input_buffer) == 1 && input_buffer[0] == 'q')
            {
                wprintf(L"Do you want to surrender? [y/n] ");
                scanf("%2s", input_buffer);
                if (strlen(input_buffer) == 1 && input_buffer[0] == 'y')
                    DIE;
            }

            continue;
        }

        if (!can_move(position1, position2, board, options, castle_status[turn]))
        {
            wprintf(L"Cant move! Cant move to this position\n");
            continue;
        }

        if (!color_match(board, position1, turn))
        {
            wprintf(L"Cant move! Cant move this piece\n");
            continue;
        }

        board_move(board, position1, position2, &castle_status[turn]);
        check_castling(&castle_status[turn], board, position1, options);

        if (is_check(board, turn, castle_status[turn]))
        {
            if (is_checkmate(board, turn, options, castle_status[turn]))
            {
                checkmate = true;
                // break; // REMOVE
            }
        }

        // is needed to move the piece before and return to its previous position if its check
        if (is_check(board, turn == BLACK ? WHITE : BLACK, castle_status[turn]))
        {
            wprintf(L"Cant move! Its check\n");
            board_move(board, position2, position1, &castle_status[turn]);
            continue;
        }

        // swap turn
        turn = (turn == WHITE) ? BLACK : WHITE;
        options = options & REVERSE_BOARD ? options & ~REVERSE_BOARD : options | REVERSE_BOARD;

        print_board(board, offset, options);
    }
    wprintf(L"Checkmate!\n");

    free_board(board);
    return 0;
}
