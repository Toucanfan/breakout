#ifndef APP_MAP_H
#define APP_MAP_H

struct app_map_ball {
	struct std_fixpt_point pos;
	struct std_fixpt_point vel;
};

struct app_map_paddle {
	long x;
	long vel;
};

#endif