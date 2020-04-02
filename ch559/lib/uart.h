#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>

#ifndef  FREQ_SYS
#define FREQ_SYS 12000000 // System frequency is 12MHz
#endif


#ifndef  UART0_BAUD
#define  UART0_BAUD    9600
#endif

void uart0_init(); // Initlize UART0 using T1 timer for baud generation.
void uart0_alter(); // Map UART0 to alternative pins P0.2/P0.3
uint8_t uart0_read(); // Receive one byte data from UART0
void uart0_write(uint8_t data); // Send one byte data to UART0


#endif  // __UART_H__
