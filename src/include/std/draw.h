#ifndef STD_DRAW_H
#define STD_DRAW_H

#define STD_DRAW_RED

//! Point struct
struct std_draw_point {
	int x;
	int y;
};

//! Window style definition struct
struct std_draw_window_style {
	char hori; //!< Char for horizontal element
	char vert; //!< Char for vertical element
	char tr; //!< Char for top right element
	char tl; //!< Char for top left element
	char bl; //!< Char for bottom left element
	char br; //!< Char for bottom right element
	char hstart; //!< Char for header start
	char hend; //!< Char for header end
	char fill; //!< Boolean for fiil. True will fill
};

 //! Window definition struct
struct std_draw_window {
	struct std_draw_point tl; //!< Top left point
	struct std_draw_point br; //!< Bottom right point
	struct std_draw_point cursor; //!< Cursor position
	struct std_draw_window_style style; //!< Window style definition
	char *title; //!< Title
};

 //! Box definition struct
struct std_draw_box {
	struct std_draw_point tl; //!< Top left point
	struct std_draw_point br; //!< Bottom right point
	char color; //!< Color of box
};

/* function prototypes */
extern void std_draw_window(struct std_draw_window *window);
extern void std_draw_box(struct std_draw_box *box);

#endif /* std/draw.h */
