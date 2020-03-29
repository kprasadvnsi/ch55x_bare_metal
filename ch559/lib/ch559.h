#ifndef __CH559_H__
#define __CH559_H__

#include <compiler.h>

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

#endif  // __CH559_H__
