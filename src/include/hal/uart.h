#ifndef HAL_UART_H
#define HAL_UART_H

#include <sio.h>

/* macro functions */
#define hal_uart_init() init_uart(_UART0, _DEFFREQ, _DEFBAUD)

/* function prototypes */
extern void hal_uart_init(void);


#endif /* hal/uart.h */
