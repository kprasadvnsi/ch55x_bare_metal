
// Blink a LED connected to pin 1.6

#include <stdint.h>
#include <ch559.h>

static inline void delay() {
    uint32_t i;
    for (i = 0; i < (120000UL); i++){}
        __asm__("nop");
}

void main() {
	PORT_CFG = 0b00101101;
    P1_DIR = 0b11110000;
	P1 = 0x00;

	while (1) {
		delay();
		P1_6 = !P1_6;
	}
}
