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

extern void app_highscore_clr(void);
extern void app_highscore_init(void);
extern void app_highscore_add(struct app_highscore score);
extern void app_highscore_render();
extern char app_highscore_test(int score);
extern struct app_highscore *app_highscore_get_topscore(void);
#endif
