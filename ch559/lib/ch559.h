#ifndef __CH559_H__
#define __CH559_H__

#include <compiler.h>

/* Clock and Sleep and Power Registers */
SFR(PCON,	0x87);	// power control and reset flag
#define SMOD              0x80      // baud rate selection for UART0 mode 1/2/3: 0=slow(Fsys/128 @mode2, TF1/32 @mode1/3, no effect for TF2),
                                    //   1=fast(Fsys/32 @mode2, TF1/16 @mode1/3, no effect for TF2)
#define bRST_FLAG1        0x20      // ReadOnly: recent reset flag high bit
#define bRST_FLAG0        0x10      // ReadOnly: recent reset flag low bit
#define MASK_RST_FLAG     0x30      // ReadOnly: bit mask of recent reset flag
#define RST_FLAG_SW       0x00
#define RST_FLAG_POR      0x10
#define RST_FLAG_WDOG     0x20
#define RST_FLAG_PIN      0x30
// bPC_RST_FLAG1 & bPC_RST_FLAG0: recent reset flag
//    00 - software reset, by bSW_RESET=1 @(bBOOT_LOAD=0 or bWDOG_EN=1)
//    01 - power on reset
//    10 - watch-dog timer overflow reset
//    11 - external input manual reset by RST pin
#define GF1               0x08      // general purpose flag bit 1
#define GF0               0x04      // general purpose flag bit 0
#define PD                0x02      // power-down enable bit, auto clear by wake-up hardware
SFR(PLL_CFG,	0xB2);	// PLL clock config: lower 5 bits for PLL clock Fpll, upper 3 bits for USB 4x clock Fusb4x, Write@SafeMode
#define MASK_PLL_MULT     0x1F      // bit mask of PLL clock Fpll multiple
#define MASK_USB_4X_DIV   0xE0      // bit mask of USB 4x clock Fusb4x divisor, value 000b means 1000b
SFR(CLOCK_CFG,	0xB3);	// system clock config: lower 5 bits for system clock Fsys, Write@SafeMode
#define bOSC_EN_INT       0x80      // internal oscillator enable and original clock selection: 1=enable & select internal clock, 0=disable & select external clock
#define bOSC_EN_XT        0x40      // external oscillator enable, need quartz crystal or ceramic resonator between X1 and X2 pins
#define bWDOG_IF_TO       0x20      // ReadOnly: watch-dog timer overflow interrupt flag, cleared by reload watch-dog count or auto cleared when MCU enter interrupt routine
#define MASK_SYS_CK_DIV   0x1F      // bit mask of system clock Fsys divisor, value 00000b means 100000b
/*
   Fxt = 4MHz~20MHz, from external oscillator @XI&XO
   Fosc = bOSC_EN_INT ? 12MHz : Fxt
   Fpll = Fosc * ( PLL_CFG & MASK_PLL_MULT ) => 288MHz (24MHz~350MHz)
   Kusb = ( PLL_CFG & MASK_USB_4X_DIV ) >> 5
   Fusb4x = Fpll / ( Kusb ? Kusb : 8 ) => 48MHz (Fixed)
   Ksys = CLOCK_CFG & MASK_SYS_CK_DIV
   Fsys = Fpll / ( Ksys ? Ksys : 32 ) => 12MHz (1MHz~56MHz)
*/
SFR(SLEEP_CTRL,	0xEA);	// sleep control, Write@SafeMode
#define bSLP_OFF_USB      0x80      // clock off for USB
#define bSLP_OFF_ADC      0x40      // clock off for ADC
#define bSLP_OFF_UART1    0x20      // clock off for UART1
#define bSLP_OFF_P1S1     0x10      // clock off for PWM1 / SPI1
#define bSLP_OFF_SPI0     0x08      // clock off for SPI0
#define bSLP_OFF_TMR3     0x04      // clock off for timer3
#define bSLP_OFF_LED      0x02      // clock off for LED
#define bSLP_OFF_XRAM     0x01      // clock off for xRAM
SFR(WAKE_CTRL,	0xEB);	// wake-up control, Write@SafeMode
#define bWAK_BY_USB       0x80      // enable wake-up by USB event
#define bWAK_RXD1_LO      0x40      // enable wake-up by RXD1 low level
#define bWAK_P1_5_LO      0x20      // enable wake-up by pin P1.5 low level
#define bWAK_P1_4_LO      0x10      // enable wake-up by pin P1.4 low level
#define bWAK_P0_3_LO      0x08      // enable wake-up by pin P0.3 low level
#define bWAK_CAP3_LO      0x04      // enable wake-up by CAP3 low level
#define bWAK_P3_2E_3L     0x02      // enable wake-up by pin P3.2 (INT0) edge or pin P3.3 (INT1) low level
#define bWAK_RXD0_LO      0x01      // enable wake-up by RXD0 low level
SFR(RESET_KEEP,	0xFE);	// value keeper during reset
SFR(WDOG_COUNT,	0xFF);	// watch-dog count, count by clock frequency Fsys/262144

/*  Port Registers  */
SFR(P1,	0x90);	// port 1 input & output
   SBIT(P1_7,	0x90, 7);
   SBIT(P1_6,	0x90, 6);
   SBIT(P1_5,	0x90, 5);
   SBIT(P1_4,	0x90, 4);
   SBIT(P1_3,	0x90, 3);
   SBIT(P1_2,	0x90, 2);
   SBIT(P1_1,	0x90, 1);
   SBIT(P1_0,	0x90, 0);

SFR(P1_DIR,	0xBA);	// port 1 direction
SFR(PORT_CFG,	0xC6);	// port 0/1/2/3 config

/*  Timer0/1 Registers  */
SFR(TCON,	0x88);	// timer 0/1 control and external interrupt control
   SBIT(TF1,	0x88, 7);	// timer1 overflow & interrupt flag, auto cleared when MCU enter interrupt routine
   SBIT(TR1,	0x88, 6);	// timer1 run enable
   SBIT(TF0,	0x88, 5);	// timer0 overflow & interrupt flag, auto cleared when MCU enter interrupt routine
   SBIT(TR0,	0x88, 4);	// timer0 run enable
   SBIT(IE1,	0x88, 3);	// INT1 interrupt flag, auto cleared when MCU enter interrupt routine
   SBIT(IT1,	0x88, 2);	// INT1 interrupt type: 0=low level action, 1=falling edge action
   SBIT(IE0,	0x88, 1);	// INT0 interrupt flag, auto cleared when MCU enter interrupt routine
   SBIT(IT0,	0x88, 0);	// INT0 interrupt type: 0=low level action, 1=falling edge action
SFR(TMOD,	0x89);	// timer 0/1 mode
#define bT1_GATE          0x80      // gate control of timer1: 0=timer1 run enable while TR1=1, 1=timer1 run enable while P3.3 (INT1) pin is high and TR1=1
#define bT1_CT            0x40      // counter or timer mode selection for timer1: 0=timer, use internal clock, 1=counter, use P3.5 (T1) pin falling edge as clock
#define bT1_M1            0x20      // timer1 mode high bit
#define bT1_M0            0x10      // timer1 mode low bit
#define MASK_T1_MOD       0x30      // bit mask of timer1 mode
// bT1_M1 & bT1_M0: timer1 mode
//   00: mode 0, 13-bit timer or counter by cascaded TH1 and lower 5 bits of TL1, the upper 3 bits of TL1 are ignored
//   01: mode 1, 16-bit timer or counter by cascaded TH1 and TL1
//   10: mode 2, TL1 operates as 8-bit timer or counter, and TH1 provide initial value for TL1 auto-reload
//   11: mode 3, stop timer1
#define bT0_GATE          0x08      // gate control of timer0: 0=timer0 run enable while TR0=1, 1=timer0 run enable while P3.2 (INT0) pin is high and TR0=1
#define bT0_CT            0x04      // counter or timer mode selection for timer0: 0=timer, use internal clock, 1=counter, use P3.4 (T0) pin falling edge as clock
#define bT0_M1            0x02      // timer0 mode high bit
#define bT0_M0            0x01      // timer0 mode low bit
#define MASK_T0_MOD       0x03      // bit mask of timer0 mode
// bT0_M1 & bT0_M0: timer0 mode
//   00: mode 0, 13-bit timer or counter by cascaded TH0 and lower 5 bits of TL0, the upper 3 bits of TL0 are ignored
//   01: mode 1, 16-bit timer or counter by cascaded TH0 and TL0
//   10: mode 2, TL0 operates as 8-bit timer or counter, and TH0 provide initial value for TL0 auto-reload
//   11: mode 3, TL0 is 8-bit timer or counter controlled by standard timer0 bits, TH0 is 8-bit timer using TF1 and controlled by TR1, timer1 run enable if it is not mode 3
SFR(TL0,	0x8A);	// low byte of timer 0 count
SFR(TL1,	0x8B);	// low byte of timer 1 count
SFR(TH0,	0x8C);	// high byte of timer 0 count
SFR(TH1,	0x8D);	// high byte of timer 1 count

/*  UART0 Registers  */
SFR(SCON,	0x98);	// UART0 control (serial port control)
   SBIT(SM0,	0x98, 7);	// UART0 mode bit0, selection data bit: 0=8 bits data, 1=9 bits data
   SBIT(SM1,	0x98, 6);	// UART0 mode bit1, selection baud rate: 0=fixed, 1=variable
// SM0 & SM1: UART0 mode
//    00 - mode 0, shift Register, baud rate fixed at: Fsys/12
//    01 - mode 1, 8-bit UART,     baud rate = variable by timer1 or timer2 overflow rate
//    10 - mode 2, 9-bit UART,     baud rate fixed at: Fsys/128@SMOD=0, Fsys/32@SMOD=1
//    11 - mode 3, 9-bit UART,     baud rate = variable by timer1 or timer2 overflow rate
   SBIT(SM2,	0x98, 5);	// enable multi-device communication in mode 2/3
#define MASK_UART0_MOD    0xE0      // bit mask of UART0 mode
   SBIT(REN,	0x98, 4);	// enable UART0 receiving
   SBIT(TB8,	0x98, 3);	// the 9th transmitted data bit in mode 2/3
   SBIT(RB8,	0x98, 2);	// 9th data bit received in mode 2/3, or stop bit received for mode 1
   SBIT(TI,	0x98, 1);	// transmit interrupt flag, set by hardware after completion of a serial transmittal, need software clear
   SBIT(RI,	0x98, 0);	// receive interrupt flag, set by hardware after completion of a serial receiving, need software clear
SFR(SBUF,	0x99);	// UART0 data buffer: reading for receiving, writing for transmittal

/*  Timer2/Capture2 Registers  */
SFR(T2CON,	0xC8);	// timer 2 control
   SBIT(TF2,	0xC8, 7);	// timer2 overflow & interrupt flag, need software clear, the flag will not be set when either RCLK=1 or TCLK=1
   SBIT(CAP1F,	0xC8, 7);	// timer2 capture 1 interrupt flag, set by T2 edge trigger if bT2_CAP1_EN=1, need software clear
   SBIT(EXF2,	0xC8, 6);	// timer2 external flag, set by T2EX edge trigger if EXEN2=1, need software clear
   SBIT(RCLK,	0xC8, 5);	// selection UART0 receiving clock: 0=timer1 overflow pulse, 1=timer2 overflow pulse
   SBIT(TCLK,	0xC8, 4);	// selection UART0 transmittal clock: 0=timer1 overflow pulse, 1=timer2 overflow pulse
   SBIT(EXEN2,	0xC8, 3);	// enable T2EX trigger function: 0=ignore T2EX, 1=trigger reload or capture by T2EX edge
   SBIT(TR2,	0xC8, 2);	// timer2 run enable
   SBIT(C_T2,	0xC8, 1);	// timer2 clock source selection: 0=timer base internal clock, 1=external edge counter base T2 falling edge
   SBIT(CP_RL2,	0xC8, 0);	// timer2 function selection (force 0 if RCLK=1 or TCLK=1): 0=timer and auto reload if count overflow or T2EX edge, 1=capture by T2EX edge
SFR(T2MOD,	0xC9);	// timer 2 mode and timer 0/1/2 clock mode
#define bTMR_CLK          0x80      // fastest internal clock mode for timer 0/1/2 under faster clock mode: 0=use divided clock, 1=use original Fsys as clock without dividing
#define bT2_CLK           0x40      // timer2 internal clock frequency selection: 0=standard clock, Fsys/12 for timer mode, Fsys/4 for UART0 clock mode,
                                    //   1=faster clock, Fsys/4 @bTMR_CLK=0 or Fsys @bTMR_CLK=1 for timer mode, Fsys/2 @bTMR_CLK=0 or Fsys @bTMR_CLK=1 for UART0 clock mode
#define bT1_CLK           0x20      // timer1 internal clock frequency selection: 0=standard clock, Fsys/12, 1=faster clock, Fsys/4 if bTMR_CLK=0 or Fsys if bTMR_CLK=1
#define bT0_CLK           0x10      // timer0 internal clock frequency selection: 0=standard clock, Fsys/12, 1=faster clock, Fsys/4 if bTMR_CLK=0 or Fsys if bTMR_CLK=1
#define bT2_CAP_M1        0x08      // timer2 capture mode high bit
#define bT2_CAP_M0        0x04      // timer2 capture mode low bit
// bT2_CAP_M1 & bT2_CAP_M0: timer2 capture point selection
//   x0: from falling edge to falling edge
//   01: from any edge to any edge (level changing)
//   11: from rising edge to rising edge
#define T2OE              0x02      // enable timer2 generated clock output: 0=disable output, 1=enable clock output at T2 pin, frequency = TF2/2
#define bT2_CAP1_EN       0x01      // enable T2 trigger function for capture 1 of timer2 if RCLK=0 & TCLK=0 & CP_RL2=1 & C_T2=0 & T2OE=0
SFR16(RCAP2,	0xCA);	// reload & capture value, little-endian
SFR(RCAP2L,	0xCA);	// low byte of reload & capture value
SFR(RCAP2H,	0xCB);	// high byte of reload & capture value
SFR16(T2COUNT,	0xCC);	// counter, little-endian
//sfr16 T2CAP1        = 0xCC;        // ReadOnly: capture 1 value for timer2
#define T2CAP1            T2COUNT
SFR(TL2,	0xCC);	// low byte of timer 2 count
//sfr T2CAP1L         = 0xCC;         // ReadOnly: capture 1 value low byte for timer2
#define T2CAP1L           TL2
SFR(TH2,	0xCD);	// high byte of timer 2 count
//sfr T2CAP1H         = 0xCD;         // ReadOnly: capture 1 value high byte for timer2
#define T2CAP1H           TH2

#endif  // __CH559_H__
