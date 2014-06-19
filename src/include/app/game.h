#ifndef APP_GAME_H
#define APP_GAME_H

#include "app/map.h"

extern char game_state;

void game_tick (struct app_map_context *ctx);
void init_game(struct app_map_context *ctx);
extern void init_endgame(struct app_map_context *ctx);

#endif /* app/game.h */
