#ifndef APP_MAP_H
#define APP_MAP_H

#include "std/fixpt.h"

#define BLOCK_ROWS 5

//! The ball struct
struct app_map_ball {
	struct std_fixpt_point pos; //!< The position of the ball
	struct std_fixpt_point vel; //!< The velocity of the ball
	char speed; //!< The speed of the ball
};

//! The paddle struct
struct app_map_paddle {
	long x; //!< The position of the paddle
	long vel; //!< The velocity of the paddle
};
	
//! The game context
struct app_map_context {
	char difficulty; //!< The difficulty
	char level; //!< The current level
	char lives; //!< The current number of lives
	int score; //!< The current score
	struct app_map_ball ball; //!< The ball
	struct app_map_paddle paddle; //!< The paddle
	long blocks[BLOCK_ROWS]; //!< The blocks in the map
	int blocks_left; //!< The number of blocks that are left
	char resumed_game; //!< True if the game is resumed
};

extern void app_map_reset(struct app_map_context *ctx);
extern void app_map_refresh(struct app_map_context *ctx);

#endif /* APP_MAP_H */
