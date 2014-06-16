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