#ifndef APP_DRAW_H
#define APP_DRAW_H

#define EASY 0
#define MEDIUM 1
#define HARD 2
#define VERY HARD 3

#define GAME 0
#define HIGHSCORES 1
#define HELP 2
#define EXIT 3

#include "std/draw.h"
#include "std/tty.h"
#include "app/draw.h"

void app_draw_splash(void);
void app_draw_highscores(void);
void app_draw_menu(char selection);
void app_draw_help(void);
void app_draw_difficulties(char selection);
void app_draw_endgame(void);

#endif /* app/draw.h */
