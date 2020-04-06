
// Blink LEDs connected to port P0

#include <stdint.h>
#include <ch559.h>

#define MASK_P0_OC 0x0F

static inline void delay() {
    uint32_t i;
    for (i = 0; i < (5 * 12000UL); i++){}
        __asm__("nop");
}

void run_led () {
	uint8_t i;
	for(i=0; i<8; i++) {
		P0 = (1 << i);
		delay();
	}
}

void main() {

	PORT_CFG |= bP0_DRV | (MASK_P0_OC & ~bP0_OC); // Set port P0 driving current and output mode.
    P0_DIR = 0xFF; // Set all bits to output mode

	// Turning all bits to high
	P0 = 0xFF;
	delay();
	delay();
	delay();
	delay();


	// Turning all bits to low
	P0 = 0x00;
	delay();
	delay();
	delay();
	delay();

	// Turning alternate bits to high
	P0 = 0xAA;
	delay();
	delay();
	delay();
	delay();

	// Turning upper half bits to high
	P0 = 0xF0;
	delay();
	delay();
	delay();
	delay();

	// Turning lower half bits to high
	P0 = 0x0F;
	delay();
	delay();
	delay();
	delay();

	while (1) {
		run_led();
	}
}
