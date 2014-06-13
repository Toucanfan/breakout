#ifndef STD_DRAW_H
#define STD_DRAW_H

#define STD_DRAW_RED

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
	char *title;
};

struct std_draw_box {
	struct std_draw_point tl;
	struct std_draw_point br;
	char color;
}



/* function prototypes */
extern void std_draw_window(struct std_draw_window *window);
extern void std_draw_box(struct std_draw_box *box);


#endif /* std/draw.h */
