#include <stdint.h>
#include <stdio.h>
#include <ch559.h>
#include <uart.h>

/*
 * Redirect stdout to UART0
 */
int putchar(int c) {
    uart0_write(c);
    return 0;
}

/*
 * Redirect stdin to UART0
 */
int getchar() {
    return uart0_read();
}

void main() {
	uart0_init();
	printf("Hello World!\n");
	while (1) {}
}
