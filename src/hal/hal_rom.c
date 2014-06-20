#include <ez8.h>
#include "hal/rom.h"
#include "std/tty.h"

#define FLASH_STATE_LOCKED 0x00

void hal_rom_read(unsigned char page, void *buf, int n)
{
	char *dst = buf;
	rom const *src = (rom const*)((unsigned int)page << 9);
	DI();

	/* setup timing */
	INIT_FLASH(FREQ18432);

	/* write n bytes of page to buf */
	while(n--) {
		*dst = READ_FLASH(src);
		src++;
		dst++;
	}
	EI();
}

void hal_rom_write(unsigned char page, void *buf, int n)
{
	char *src = buf;
	rom const *dst = (rom const*)((unsigned int)page << 9);
	DI();
	/* setup timing */
	INIT_FLASH(FREQ18432);
	/* select page */
	FPS = (page & 0x7F);


	/* do a page erase */
	FCTL = 0x73; /* unlock code 1 */
	FCTL = 0x8C; /* unlock code 2 */
	FCTL = 0x95; /* now unlocked, begin page erase */

	/* busy wait until page erase is completed */
	while (FSTAT != FLASH_STATE_LOCKED);


	/* write n bytes of buf to page */
	while(n--) {
		WRITE_FLASH(dst, *src);
		
		src++;
		dst++;
	}
	EI();
}
