#ifndef UI_H
#define UI_H

#include "game.h"

void init_ui(void);
void cleanup_ui(void);
void draw_game(const GameState* state);
void draw_splash(const GameState* state);
void draw_menu(const GameState* state);

#endif