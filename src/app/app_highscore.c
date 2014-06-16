#include <ez8.h> /* special encore constants, macros and falsh functions */
#include <sio.h> /* special encore serial i/o functions */

#include "app/highscore.h"

struct app_highscore *highscores;

void app_highscore_clr()
{
	int i;
	for(i = 0; i < HIGHSCORE_COUNT; i++) {
		highscores[i].score = 0;
		highscores[i].name = "0000";
	}
}

// Adds a score struct to the highscore at the correct position. If it is
// lower than all other items on the list, it is discarded
void app_add_highscore(struct app_highscore score)
{
	struct app_highscore tmp;
	int i;
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
	int i;
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
char app_highscore_test(int score)
{
	int i;
	for(i = 0; i < HIGHSCORE_COUNT; i++) {
		if(score > highscores[i].score)
			return 1;
	}

	return 0;
}