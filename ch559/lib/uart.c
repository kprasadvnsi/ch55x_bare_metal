#include "ch559.h"
#include "uart.h"

/*
 * P3.0 -> RX
 * P3.1 -> TX
 */

// Initlize UART0 using T1 timer for baud generation.
void uart0_init() {

	// SM0 & SM1: UART0 mode
	// 00 - mode 0, shift Register, baud rate fixed at: Fsys/12
	// 01 - mode 1, 8-bit UART,     baud rate = variable by timer1 or timer2 overflow rate
	// 10 - mode 2, 9-bit UART,     baud rate fixed at: Fsys/128@SMOD=0, Fsys/32@SMOD=1
	// 11 - mode 3, 9-bit UART,     baud rate = variable by timer1 or timer2 overflow rate
	SM0 = 0;
	SM1 = 1;
   
	// RCLK select UART0 receiving clock: 0=timer1 overflow pulse, 1=timer2 overflow pulse
	// TCLK select UART0 transmittal clock: 0=timer1 overflow pulse, 1=timer2 overflow pulse
	RCLK = 0;
	TCLK = 0;
    
    // bT1_M1 & bT1_M0: timer1 mode
	// 00: mode 0, 13-bit timer or counter by cascaded TH1 and lower 5 bits of TL1, the upper 3 bits of TL1 are ignored
	// 01: mode 1, 16-bit timer or counter by cascaded TH1 and TL1
	// 10: mode 2, TL1 operates as 8-bit timer or counter, and TH1 provide initial value for TL1 auto-reload
	// 11: mode 3, stop timer1
	TMOD = MASK_T1_MOD & (bT1_M1 | ~bT1_M0);

    PCON |= SMOD;
	T2MOD = T2MOD | bTMR_CLK | bT1_CLK;
	TH1 = 256 - FREQ_SYS/16/UART0_BAUD;

    TR1 = 1;
    TI = 1;
    REN = 1;
}

// Map UART0 to alternative pins P0.2/P0.3
void uart0_alter() {

}

// Receive one byte data from UART0
uint8_t uart0_read() {
	while(!RI);
    RI = 0;
    return SBUF;
}

// Send one byte data to UART0
void uart0_write(uint8_t data) {
	while (!TI);
    TI = 0;
    SBUF = data & 0xFF;
}
