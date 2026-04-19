#ifndef CONFIG_H
#define CONFIG_H

#define FPS 30
#define FRAME_DELAY_MS (1000 / FPS)

#define PADDLE_HEIGHT 5
#define PADDLE_CHAR '|'
#define BALL_CHAR 'O'

#define COLOR_PAIR_DEFAULT 1
#define COLOR_PAIR_BALL 2
#define COLOR_PAIR_PADDLE 3

#define STATE_SPLASH 0
#define STATE_MENU 1
#define STATE_PLAYING 2
#define STATE_AI 3

#endif