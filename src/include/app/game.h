#ifndef APP_GAME_H
#define APP_GAME_H

extern char game_state;

struct ball {
	struct std_fixpt_point pos;
	struct std_fixpt_point vel;
};

struct app_map_ball {    // SKAL FJERNES SENERE
	struct std_fixpt_point pos;
	struct std_fixpt_point vel;
};

struct app_map_paddle {    // SKAL FJERNES SENERE
	long x;
	long vel;
};


struct game_condition {
	char difficulty;
	char level;
	char lives;
	int score;
	struct app_map_ball ball;
	struct app_map_paddle paddle;
	long *blocks;
	int blocks_left;
};


void game_tick (struct game_condition *game_condition);
void init_level(struct game_condition *game_condition);
void init_game(struct game_condition *game_condition);
void draw_blocks(struct game_condition *game_condition);
char test_block_collision(struct game_condition *game_condition);
int count_blocks(long *blocks);

#endif /* app/game.h */
