#include <ncurses.h>
#include "ui.h"
#include "config.h"

void init_ui(void) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    
    if (has_colors()) {
        start_color();
        init_pair(COLOR_PAIR_DEFAULT, COLOR_WHITE, COLOR_BLACK);
        init_pair(COLOR_PAIR_BALL, COLOR_YELLOW, COLOR_BLACK);
        init_pair(COLOR_PAIR_PADDLE, COLOR_CYAN, COLOR_BLACK);
    }
}

void cleanup_ui(void) {
    endwin();
}

void draw_splash(const GameState* state) {
    erase();
    attron(COLOR_PAIR(COLOR_PAIR_DEFAULT));

    int x = state->ext_max_x / 2;
    int y = state->ext_max_y / 2;

    mvprintw(y - 4, x - 7, "TERMINAL PONG");
    mvprintw(y - 2, x - 6, "BIOWESS 2026");
    mvprintw(y,     x - 14, "C + NASM x86-64 ENGINE");
    mvprintw(y + 2, x - 15, "Press ENTER to continue");

    attroff(COLOR_PAIR(COLOR_PAIR_DEFAULT));
    refresh();
}

void draw_menu(const GameState* state) {
    erase();
    attron(COLOR_PAIR(COLOR_PAIR_DEFAULT));

    int x = state->ext_max_x / 2;
    int y = state->ext_max_y / 2;

    mvprintw(y - 3, x - 5, "MAIN MENU");
    mvprintw(y - 1, x - 10, "1. Two Player");
    mvprintw(y,     x - 10, "2. Play vs AI");
    mvprintw(y + 2, x - 10, "Q. Quit");
    mvprintw(y + 4, x - 14, "Use keys 1 / 2 / Q");

    attroff(COLOR_PAIR(COLOR_PAIR_DEFAULT));
    refresh();
}

void draw_game(const GameState* state) {
    erase();
    
    attron(COLOR_PAIR(COLOR_PAIR_DEFAULT));
    box(stdscr, 0, 0);
    
    for (int i = 1; i < state->ext_max_y - 1; i += 2) {
        mvaddch(i, state->ext_max_x / 2, '|');
    }
    
    mvprintw(0, state->ext_max_x / 2 - 10,
             " %d - %d ", state->p1_score, state->p2_score);

    attroff(COLOR_PAIR(COLOR_PAIR_DEFAULT));
    
    attron(COLOR_PAIR(COLOR_PAIR_PADDLE));

    int half_pad = PADDLE_HEIGHT / 2;

    for (int i = -half_pad; i <= half_pad; i++) {
        if (state->p1_y + i > 0 && state->p1_y + i < state->ext_max_y - 1)
            mvaddch(state->p1_y + i, state->p1_x, PADDLE_CHAR);
            
        if (state->p2_y + i > 0 && state->p2_y + i < state->ext_max_y - 1)
            mvaddch(state->p2_y + i, state->p2_x, PADDLE_CHAR);
    }

    attroff(COLOR_PAIR(COLOR_PAIR_PADDLE));
    
    attron(COLOR_PAIR(COLOR_PAIR_BALL));
    mvaddch(state->ball_y, state->ball_x, BALL_CHAR);
    attroff(COLOR_PAIR(COLOR_PAIR_BALL));
    
    refresh();
}