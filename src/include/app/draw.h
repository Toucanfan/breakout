#ifndef APP_DRAW_H
#define APP_DRAW_H

#define EASY 0
#define MEDIUM 1
#define HARD 2
#define VERY_HARD 3


#include "std/draw.h"
#include "std/tty.h"
#include "app/draw.h"

extern void app_draw_splash(void);
extern void app_draw_highscores(void);
extern void app_draw_resume();
extern void app_draw_endgame(void);
extern void app_draw_difficulties(char init, char selection);
extern void app_draw_save(void);
extern void app_draw_menu(char init, char selection);

#endif /* app/draw.h */
