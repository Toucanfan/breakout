#ifndef HAL_ROM_H
#define HAL_ROM_H

#define HAL_ROM_PAGE0 0x7D /* 3rd last high-sector page */
#define HAL_ROM_PAGE1 0x7E
#define HAL_ROM_PAGE2 0x7F

extern void hal_rom_read(unsigned char page, void *buf, int n);
extern void hal_rom_write(unsigned char page, void *buf, int n);

#endif /* HAL_ROM_H */
