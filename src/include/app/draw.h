#ifndef APP_DRAW_H
#define APP_DRAW_H

#define EASY 0
#define MEDIUM 1
#define HARD 2
#define VERY_HARD 3

#define GAME 0
#define HIGHSCORES 1
#define RESUME 2
#define EXIT 3

#include "std/draw.h"
#include "std/tty.h"
#include "app/draw.h"

void app_draw_splash(void);
void app_draw_highscores(void);
void app_draw_menu(char init, char selection);
void app_draw_endgame(void);
void app_draw_difficulties(char init, char selection);

#endif /* app/draw.h */
