#ifndef APP_GAME_H
#define APP_GAME_H

#include "app/map.h"

extern char game_state;

void game_tick (struct app_map_context *ctx);
void init_level(struct app_map_context *ctx);
void init_game(struct app_map_context *ctx);
void draw_blocks(struct app_map_context *ctx);
char test_block_collision(struct app_map_context *ctx);
int count_blocks(long *blocks);

#endif /* app/game.h */
