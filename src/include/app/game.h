#ifndef APP_GAME_H
#define APP_GAME_H

#include "app/map.h"

extern char app_game_state;

extern void app_game_tick (struct app_map_context *ctx);
extern void app_game_init(struct app_map_context *ctx);
extern void app_game_end(struct app_map_context *ctx);

#endif /* app/game.h */
