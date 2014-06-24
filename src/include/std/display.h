#ifndef STD_DISPLAY_H
#define STD_DISPLAY_H

#define STD_DISPLAY_ROWS 10
#define STD_DISPLAY_COLS 10

//! The display buffer struct
struct std_display_buffer {
	unsigned char buf[STD_DISPLAY_ROWS][STD_DISPLAY_COLS]; //!< The buffer
	unsigned char flags[STD_DISPLAY_ROWS];
	unsigned char dirty_rows;
};

//! Set pixels on the display
/**
 * @param buffer The display buffer
 * @param row The current row
 * @param col The current column
 * @param ch The character to insert
 */
#define std_display_set_pixel(buffer, row, col, ch) \
{\
	buffer.buf[row][col] = ch; \
	buffer.flags[row] |= 0x1; \
}

/* function prototypes */
extern void std_display_refresh(struct std_display_buffer *buf);


#endif /* std/display.h */
