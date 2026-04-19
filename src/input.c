#include <ncurses.h>
#include "input.h"
#include "config.h"

void handle_input(GameState* state) {
    int ch = getch();
    
    while (ch != ERR) {

        /* SPLASH */
        if (state->mode == STATE_SPLASH) {
            if (ch == '\n' || ch == KEY_ENTER || ch == ' ')
                state->mode = STATE_MENU;
        }

        /* MENU */
        else if (state->mode == STATE_MENU) {
            switch (ch) {
                case '1':
                    state->mode = STATE_PLAYING;
                    asm_reset_ball(state);
                    break;

                case '2':
                    state->mode = STATE_AI;
                    asm_reset_ball(state);
                    break;

                case 'q':
                case 'Q':
                    state->is_running = 0;
                    break;
            }
        }

        /* GAME MODES */
        else if (state->mode == STATE_PLAYING || state->mode == STATE_AI) {
            switch (ch) {

                case 'q':
                case 'Q':
                    state->is_running = 0;
                    break;

                /* PLAYER 1 = ARROWS (NEW) */
                case KEY_UP:
                    if (state->p1_y - PADDLE_HEIGHT / 2 > 1)
                        state->p1_y--;
                    break;

                case KEY_DOWN:
                    if (state->p1_y + PADDLE_HEIGHT / 2 < state->field_height)
                        state->p1_y++;
                    break;

                /* PLAYER 2 = only in PvP mode */
                case 'w':
                case 'W':
                    if (state->mode == STATE_PLAYING &&
                        state->p2_y - PADDLE_HEIGHT / 2 > 1)
                        state->p2_y--;
                    break;

                case 's':
                case 'S':
                    if (state->mode == STATE_PLAYING &&
                        state->p2_y + PADDLE_HEIGHT / 2 < state->field_height)
                        state->p2_y++;
                    break;
            }
        }

        ch = getch();
    }
}