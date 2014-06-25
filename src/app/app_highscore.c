/**
 * @file
 * @author Henrik Enggaard Hansen <henrik.enggaard@gmail.com>
 * @version 1.1
 * @section app_highscore-description Description
 * 
 * This file implements the functions needed for handling the highscore list.
 */

#include <ez8.h>
#include <sio.h>

#include "app/highscore.h"
#include "std/tty.h"
#include "std/rom.h"

static struct app_highscore highscores[5];

/*
 * Clears the highscore list.
 *
 * All scores are replaced by zero.
 */
void app_highscore_clr()
{
	char i;
	for(i = 0; i < HIGHSCORE_COUNT; i++) {
		highscores[i].score = 0;
		highscores[i].name[0] = '0';
		highscores[i].name[1] = '0';
		highscores[i].name[2] = '0';
		highscores[i].name[3] = '\0';
	}
	std_rom_write(STD_ROM_PAGE0, highscores, sizeof(highscores));
}

/**
 * Adds a score struct to the highscore at the correct position. If it is
 * lower than all items on the list, it is discarded.
 *
 * @param score The highscore to be inserted
 */
void app_highscore_add(struct app_highscore score)
{
	struct app_highscore tmp;
	char i;
	/* Note that sorting is not needed, since the list is always kept in
	 * a sorted state. If a score in the list is lower than the new score
	 * the new score takes its place and the old score takes place of the
	 * new.
	 *   So when a score is inserted all other scores ripple down.
	 * O(n) where n is number of scores in all scenarios.
	 */
	for(i = 0; i < HIGHSCORE_COUNT; i++) {
		if(highscores[i].score < score.score) {
			tmp = highscores[i];
			highscores[i] = score;
			score = tmp;
		}
	}
	std_rom_write(STD_ROM_PAGE0, highscores, sizeof(highscores));
}

/**
 * Prints the highscore list
 */
void app_highscore_render()
{
	char i;
	for(i = 0; i < HIGHSCORE_COUNT; i++) {
		if(highscores[i].score > 0) {
			std_tty_printf(" %s", highscores[i].name);
			std_tty_printf(" : %3d\n", highscores[i].score);
		} else {
			std_tty_printf(" --- : ---\n");
		}
	}
}

/**
 * Tests if a score is a new highscore
 *
 * @param score The score to test
 * 
 * @return Boolean char: 0 it if is not a new highscore, 1 if it is
 */
char app_highscore_test(int score)
{
	char i;
	for(i = 0; i < HIGHSCORE_COUNT; i++) {
		if(score > highscores[i].score)
			return 1;
	}

	return 0;
}

/**
 * Returns the top score
 * 
 * @return The top score
 */
struct app_highscore *app_highscore_get_topscore()
{
	return &highscores[0];
}

/**
 * Initializes the highscore list. If there is a
 * well formed highscore list in the ROM, it is read
 * and used.
 *
 * Otherwise the highscore list is cleared.
 */
void app_highscore_init(void)
{
	std_rom_read(STD_ROM_PAGE0, highscores, sizeof(highscores));
	if (highscores[0].name[3] != '\0')
		app_highscore_clr();
}
