#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <stdlib.h>
#include "ui.h"
#include "input.h"
#include "game.h"
#include "config.h"

static void update_ai(GameState* state) {
    static int ai_tick = 0;
    ai_tick++;

    if (ai_tick % 2 != 0)
        return;

    int diff = state->ball_y - state->p2_y;

    if (diff > 1) {
        if (state->p2_y + PADDLE_HEIGHT / 2 < state->field_height)
            state->p2_y++;
    } else if (diff < -1) {
        if (state->p2_y - PADDLE_HEIGHT / 2 > 1)
            state->p2_y--;
    }
}

int main(void) {
    init_ui();

    GameState state;
    
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
    
    init_game(&state, max_x, max_y);

    while (state.is_running) {
        handle_input(&state);
        
        if (state.mode == STATE_SPLASH) {
            draw_splash(&state);
        } else if (state.mode == STATE_MENU) {
            draw_menu(&state);
        } else if (state.mode == STATE_PLAYING) {
            asm_update_game(&state);
            draw_game(&state);
        } else if (state.mode == STATE_AI) {
            update_ai(&state);
            asm_update_game(&state);
            draw_game(&state);
        }
        
        usleep(FRAME_DELAY_MS * 1000);
    }

    cleanup_ui();
    return 0;
}