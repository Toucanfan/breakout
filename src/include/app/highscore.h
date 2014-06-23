#ifndef APP_HIGHSCORE_H
#define APP_HIGHSCORE_H

#define HIGHSCORE_COUNT 5

//! Struct for a single highscore entry
struct app_highscore {
	int score; //!< The score

	//! The name of the player.
	/**
	 * Last char must be `\0	`
	 */
	char name[4];
};

void app_highscore_clr(void);
void app_highscore_init(void);
void app_add_highscore(struct app_highscore score);
void app_render_highscore();
char app_highscore_test(int score);
struct app_highscore *app_get_top_score();
#endif
