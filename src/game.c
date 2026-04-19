#include "game.h"
#include "config.h"

void init_game(GameState* state, int width, int height) {
    state->ext_max_x = width;
    state->ext_max_y = height;
    
    state->field_width = width - 2;
    state->field_height = height - 2;
    
    state->p1_x = 2;
    state->p1_y = height / 2;
    state->p1_score = 0;
    
    state->p2_x = width - 3;
    state->p2_y = height / 2;
    state->p2_score = 0;
    
    state->is_running = 1;
    state->mode = STATE_SPLASH;
    
    asm_reset_ball(state);
}