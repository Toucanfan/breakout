#define HIGHSCORE_COUNT 5

struct app_highscore {
	int score;
	char *name;
};

void app_highscore_clr(void);
void app_render_highscore();
char app_highscore_test(int score);