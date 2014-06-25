#ifndef APP_GAME_H
#define APP_GAME_H

#include "app/map.h"

extern void app_game_tick (struct app_map_context *ctx, char *next_screen);
extern void app_game_end(struct app_map_context *ctx, char *next_screen);

#endif /* app/game.h */
