#ifndef APP_MAP_H
#define APP_MAP_H

#include "std/fixpt.h"

struct app_map_ball {
	struct std_fixpt_point pos;
	struct std_fixpt_point vel;
	char speed;
};

struct app_map_paddle {
	long x;
	long vel;
};
	

struct app_map_context {
	char difficulty;
	char level;
	char lives;
	int score;
	struct app_map_ball ball;
	struct app_map_paddle paddle;
	long *blocks;
	int blocks_left;
};

extern void app_map_reset(struct app_map_context *ctx);
extern void app_map_refresh(struct app_map_context *ctx);

#endif /* APP_MAP_H */
