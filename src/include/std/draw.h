#ifndef STD_DRAW_H
#define STD_DRAW_H

/* data structures */
struct std_draw_point {
	int x;
	int y;
};

struct std_draw_window_style {
	char hori;
	char vert;
	char tr;
	char tl;
	char bl;
	char br;
	char hstart;
	char hend;
	char fill;
};

struct std_draw_window {
	struct std_draw_point tl;
	struct std_draw_point br;
	struct std_draw_point cursor;
	struct std_draw_window_style style;
	char title[16];
};



/* function prototypes */
extern void std_draw_window(struct std_draw_window *window);


#endif /* std/draw.h */
