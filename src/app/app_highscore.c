#include <ez8.h> /* special encore constants, macros and falsh functions */
#include <sio.h> /* special encore serial i/o functions */

#include "app/highscore.h"

struct app_highscore *highscores;

// Resets/clears the entire highscore list. Since the score is set to 0, the
// rendering will no display it.
void app_highscore_clr()
{
	char i;
	for(i = 0; i < HIGHSCORE_COUNT; i++) {
		highscores[i].score = 0;
		highscores[i].name = "000";
	}
}

// Adds a score struct to the highscore at the correct position. If it is
// lower than all other items on the list, it is discarded
void app_add_highscore(struct app_highscore score)
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
}

// Renders highscore list
void app_render_highscore()
{
	char i;
	for(i = 0; i < HIGHSCORE_COUNT; i++) {
		if(highscores[i].score > 0) {
			printf("%s", highscores[i].name);
			printf(" : %5d\n", highscores[i].score);
		} else {
			printf(" -- : --\n");
		}
	}
}

// Tests if a score is a new highscore
char app_highscore_test(char score)
{
	char i;
	for(i = 0; i < HIGHSCORE_COUNT; i++) {
		if(score > highscores[i].score)
			return 1;
	}

	return 0;
}

// Returns the top score
struct app_highscore *app_get_top_score()
{
	return &highscores[0];
}