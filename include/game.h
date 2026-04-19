#ifndef GAME_H
#define GAME_H

#include <stdint.h>

/* Must perfectly match offset requirements in assembly */
typedef struct {
    int32_t ext_max_x;      // offset 0
    int32_t ext_max_y;      // offset 4
    int32_t field_width;    // offset 8
    int32_t field_height;   // offset 12
    
    int32_t ball_x;         // offset 16
    int32_t ball_y;         // offset 20
    int32_t ball_dx;        // offset 24
    int32_t ball_dy;        // offset 28
    
    int32_t p1_x;           // offset 32
    int32_t p1_y;           // offset 36
    int32_t p1_score;       // offset 40
    
    int32_t p2_x;           // offset 44
    int32_t p2_y;           // offset 48
    int32_t p2_score;       // offset 52
    
    int32_t is_running;     // offset 56
    int32_t mode;           // offset 60
} GameState; // Total size 64 bytes

extern void asm_update_game(GameState* state);
extern void asm_reset_ball(GameState* state);

void init_game(GameState* state, int width, int height);

#endif