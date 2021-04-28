#ifndef COMPILER_H_
/*
   Compiler settings inspired from compiler_defs.h found on the net
   it does not use #elif because uc51 does not support #elif
   Tasking CC51 is untested. Especially its unclear if it is big endian 
     
   for each compiler the following macros should be defined
  
   SFR_()    defines a reg in the SFR area 0x80..0xFF
   SBIT_()   defines a single bit within the SFR 
             Note: only valid for SFRs divideable by 8
   SFR16_()  defines a 16 bit sfr in little endian
             Note: the order of access is not guaranted
   NOP()     greates a nop istruction
*/

#ifdef BIG_ENDIAN_
  #undef BIG_ENDIAN_
#endif

#ifdef __RC51__    // Raisonance seems dead now
  #define DATA   data
  #define IDATA  idata
  #define XDATA  xdata
  #define PDATA  pdata
  #define CODE   code
  #define BDATA  bdata
  #define BIT    bit
  #define BIG_ENDIAN_
  
  #define SFR(name_,adr_)         sfr at adr_ name_
  #define SBIT(name_,adr_, pos_)  at (adr_+pos_) sbit name_
  #define SFR16(name_,adr_)       sfr16 at adr_ name_
  #define NOP() asm { 0x00 }
#endif

#ifdef __C51__       // keil
  #define DATA   data
  #define IDATA  idata
  #define XDATA  xdata
  #define PDATA  pdata
  #define CODE   code
  #define BDATA  bdata
  #define BIT    bit
  #define BIG_ENDIAN_
  
  #define SFR_(name_,adr_)       sfr   name_ = adr_
  #define SFR16_(name_,adr_)     sfr16 name_ = adr_
  #define SBIT_(name_,adr_,pos_) sbit  name_ = adr_^pos_
  #include <intrins.h>
  #define NOP() _nop_()
#endif

#ifdef __SDCC_mcs51  // SDCC
  #define DATA   __data
  #define IDATA  __idata
  #define XDATA  __xdata
  #define PDATA  __pdata
  #define CODE   __code
  #define BDATA  __bdata
  #define BIT    __bit
  #define MAKE16(adr_) (((adr_+1) << 8)+adr_) //helper 
  #define SFR_(name_,adr_)       __sfr  __at (adr_) name_
  #define SBIT_(name_,adr_,pos_) __sbit __at (adr_+pos_) name_
  #define SFR16_(name_,adr_)     __sfr16 __at (MAKE16(adr_)) name_
  #define NOP()  __asm__ ("nop")
#endif

#ifdef __IAR_SYSTEMS_ICC__  // iar
  #define DATA   __data
  #define IDATA  __idata
  #define XDATA  __xdata
  #define PDATA  __pdata
  #define CODE   __code
  #define BDATA  __bdata
  #define BIT    __bit
  
  #include <stdbool.h>
  #define SFR_(name_, adr_)        __sfr   __no_init volatile unsigned char name_ @ adr_
  #define SBIT_(name_, adr_, pos_) __bit   __no_init volatile bool name_ @ (adr_+pos_)
  #define SFR16_(name_, adr_)      __sfr   __no_init volatile unsigned int  name_ @ adr_
  #define NOP()  asm ("nop")
#endif  

#ifdef __UC__        // wickenhaeuser uc51 dead demo at www.batronics.com
  #define BIG_ENDIAN_
  
  #define SFR_(name_,adr_)       near unsigned char name_ @ adr_
  #define SBIT_(name_,adr_,pos_) unsigned char bit  name_ @ adr_+pos_
  #define SFR16_(name_,adr_)     // not supported   
  extern void _nop_(void);
  #define NOP() _nop_() 
#endif

#ifdef _CC51               //tasking not tested at all
  #define DATA   _data
  #define IDATA  _idat
  #define XDATA  _xdat
  #define PDATA  _pdat
  #define CODE   _rom
  #define BDATA  _bdat
  #define BIT    _bit
  #define BIG_ENDIAN_      //not shure but keyword _little inticades it
 
  #define SFR_(name_, adr_)        _sfrbyte name_ _at(adr_)
  #define SBIT_(name_, adr_, pos_) _sfrbit  name_ _at(adr_+pos_)
  #define SFR16_(name_, adr_)      _sfrword _little name_ _at(adr_)
  extern void _nop (void);
  #define NOP() _nop()  
#endif

// do a simple check if we have a unknown compiler
#ifndef SFR_
  #error "Error Compiler unknown"
  stop compiling
#endif

#define COMPILER_H_
#endif
