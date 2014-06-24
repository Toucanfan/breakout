/**
 * @file
 * @author Troels Mæhl Folke
 * @version 1.0
 * @section std_rom-description Description
 * 
 * ROM data saving and retreiving. Refer to hal_rom
 *
 * @section std_rom-usage Usage
 *
 * @subsection std_rom-writing Writing
 *
 *     char data = 'a';
 *     std_rom_write(STD_ROM_PAGE0, &data, sizeof(data));
 *
 * @subsection std_rom-reading Reading
 *
 *     char data;
 *     std_rom_read(STD_ROM_PAGE0, &data, sizeof(data));
 *
 */

#ifndef STD_ROM_H
#define STD_ROM_H

#include "hal/rom.h"

#define STD_ROM_PAGE0 HAL_ROM_PAGE0
#define STD_ROM_PAGE1 HAL_ROM_PAGE1
#define STD_ROM_PAGE2 HAL_ROM_PAGE2

//! Read data from ROM
#define std_rom_read hal_rom_read
//! Write data to ROM
#define std_rom_write hal_rom_write

#endif /* STD_ROM_H */
