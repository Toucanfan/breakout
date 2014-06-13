#ifndef HAL_UART_H
#define HAL_UART_H

#include <sio.h>

#define BAUD 115200

/* macro functions */
#define hal_uart_init() init_uart(_UART0, _DEFFREQ, BAUD)

#endif /* hal/uart.h */
