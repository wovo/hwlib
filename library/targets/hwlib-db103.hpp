// ==========================================================================
//
// File      : hwlib-db103.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017-2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// this file contains Doxygen lines
/// @file

#ifndef HWLIB_DB103_H
#define HWLIB_DB103_H

#define _HWLIB_TARGET_WAIT_NS_BUSY
#define _HWLIB_TARGET_WAIT_US_BUSY
#include HWLIB_INCLUDE( ../hwlib-all.hpp )

// the LPC header file use 'register' in the pre-C++17 sense
#define register
#include "LPC11xx.h"
#undef register

/// \brief
/// hwlib HAL for the DB103 board
/// 
/// \image html db103-pcb.jpg
//
/// This namespace contains the hwlib implementation of the pins, timing
/// and (sotware) UART output for the DB103 board (LPC1114FN28/102 chip).
/// The chip runs at its default speed of 12 MHz, 
/// from its internal RC oscillator.
///
/// The port and pin parameters to the constructors of the pin classes
/// refer to the LPC1114 ports and pins, as shown on the DB103 PCB.
///
/// The chip runs at 3.3 Volt and that is the level on its IO pins.
///
/// This implementation doesn't (yet) offer:
///    - hardware UART
///    - full CPU speed (48 MHz)
///    - hardware SPI
///
/// References:
///    - <A HREF="http://www.nxp.com/documents/user_manual/UM10398.pdf">
///       LPC1114 user manual</A> (pdf)
///
namespace db103 {
   
   /// \cond INTERNAL    

   // return the pointer to an IO port related register
   volatile __attribute__((weak)) uint32_t *gpioreg( uint32_t port, uint32_t offset ){
      return (volatile uint32_t *)( 0x50000000 + port * 0x10000 + offset );
   }
   
   // configure a pin that has no AD capability
   void __attribute__((weak)) pin_gp_conf( volatile uint32_t *p, uint32_t value ){
      *p = value | ( *p & ~0x07 );
   }   

   // configure a pin with AD capability  
   void __attribute__((weak)) pin_ad_conf( volatile uint32_t *p, uint32_t value ){
      *p = 
         ( value << 0 ) 
         | ( *p & ~ ( ( 0x07 << 0 ) | ( 0x01 << 7 )));
   }   
   
   // configure a pin as GPIO
   void HWLIB_WEAK configure_as_gpio( uint32_t port, uint32_t pin ){
      LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);     // enable IOCON
      switch( ( port << 8 ) | pin ){
         case 0x0000: pin_gp_conf( &LPC_IOCON->RESET_PIO0_0,  0x01 ); break;
         case 0x0001: pin_gp_conf( &LPC_IOCON->PIO0_1,        0x00 ); break;
         case 0x0002: pin_gp_conf( &LPC_IOCON->PIO0_2,        0x00 ); break;
         case 0x0003: pin_gp_conf( &LPC_IOCON->PIO0_3,        0x00 ); break;
         case 0x0004: pin_gp_conf( &LPC_IOCON->PIO0_4,        0x00 ); break;
         case 0x0005: pin_gp_conf( &LPC_IOCON->PIO0_5,        0x00 ); break;
         case 0x0006: pin_gp_conf( &LPC_IOCON->PIO0_6,        0x00 ); break;
         case 0x0007: pin_gp_conf( &LPC_IOCON->PIO0_7,        0x00 ); break;
         case 0x0008: pin_gp_conf( &LPC_IOCON->PIO0_8,        0x00 ); break;
         case 0x0009: pin_gp_conf( &LPC_IOCON->PIO0_9,        0x00 ); break;
         case 0x000A: pin_gp_conf( &LPC_IOCON->SWCLK_PIO0_10, 0x01 ); break;
         case 0x000B: pin_ad_conf( &LPC_IOCON->R_PIO0_11,     0x01 ); break;
         
         case 0x0100: pin_ad_conf( &LPC_IOCON->R_PIO1_0,      0x01 ); break;
         case 0x0101: pin_ad_conf( &LPC_IOCON->R_PIO1_1,      0x01 ); break;
         case 0x0102: pin_ad_conf( &LPC_IOCON->R_PIO1_2,      0x01 ); break;
         case 0x0103: pin_ad_conf( &LPC_IOCON->SWDIO_PIO1_3,  0x01 ); break;
         case 0x0104: pin_ad_conf( &LPC_IOCON->PIO1_4,        0x00 ); break;
         case 0x0105: pin_gp_conf( &LPC_IOCON->PIO1_5,        0x00 ); break;
         case 0x0106: pin_gp_conf( &LPC_IOCON->PIO1_6,        0x00 ); break;
         case 0x0107: pin_gp_conf( &LPC_IOCON->PIO1_7,        0x00 ); break;
         case 0x0108: pin_gp_conf( &LPC_IOCON->PIO1_8,        0x00 ); break;
         case 0x0109: pin_gp_conf( &LPC_IOCON->PIO1_9,        0x00 ); break;
         case 0x010A: pin_gp_conf( &LPC_IOCON->PIO1_10,       0x00 ); break; 
         case 0x010B: pin_gp_conf( &LPC_IOCON->PIO1_11,       0x00 ); break; 
         
         case 0x0200: pin_gp_conf( &LPC_IOCON->PIO2_0,        0x00 ); break;
         case 0x0201: pin_gp_conf( &LPC_IOCON->PIO2_1,        0x00 ); break;
         case 0x0203: pin_gp_conf( &LPC_IOCON->PIO2_3,        0x00 ); break;
         case 0x0202: pin_gp_conf( &LPC_IOCON->PIO2_2,        0x00 ); break;
         case 0x0204: pin_gp_conf( &LPC_IOCON->PIO2_4,        0x00 ); break;
         case 0x0205: pin_gp_conf( &LPC_IOCON->PIO2_5,        0x00 ); break;
         case 0x0206: pin_gp_conf( &LPC_IOCON->PIO2_6,        0x00 ); break;
         case 0x0207: pin_gp_conf( &LPC_IOCON->PIO2_7,        0x00 ); break;
         case 0x0208: pin_gp_conf( &LPC_IOCON->PIO2_8,        0x00 ); break;
         case 0x0209: pin_gp_conf( &LPC_IOCON->PIO2_9,        0x00 ); break;
         case 0x020A: pin_gp_conf( &LPC_IOCON->PIO2_10,       0x00 ); break;
         case 0x020B: pin_gp_conf( &LPC_IOCON->PIO2_11,       0x00 ); break;
         
         case 0x0300: pin_gp_conf( &LPC_IOCON->PIO3_0,        0x00 ); break;
         case 0x0301: pin_gp_conf( &LPC_IOCON->PIO3_1,        0x00 ); break;
         case 0x0302: pin_gp_conf( &LPC_IOCON->PIO3_2,        0x00 ); break;
         case 0x0303: pin_gp_conf( &LPC_IOCON->PIO3_3,        0x00 ); break;
         case 0x0304: pin_gp_conf( &LPC_IOCON->PIO3_4,        0x00 ); break;
         case 0x0305: pin_gp_conf( &LPC_IOCON->PIO3_5,        0x00 ); break;
         
         default: HWLIB_PANIC_WITH_LOCATION; 
      }        
   } 
   
   // configure a pin as ADC
   uint32_t HWLIB_WEAK configure_as_adc( uint32_t port, uint32_t pin ){ 
   
         // enable IOCON & A/D clock
      LPC_SYSCON->SYSAHBCLKCTRL |= ( 0x01 << 16 ) | ( 0x01 << 13 );
   
         // enable A/D power
      LPC_SYSCON->PDRUNCFG &= ~( 1 << 4 );      

      switch( ( port << 8 ) | pin ){
         case 0x000B: pin_ad_conf( &LPC_IOCON->R_PIO0_11,    0x02 ); return 0;
         
         case 0x0100: pin_ad_conf( &LPC_IOCON->R_PIO1_0,     0x02 ); return 1;
         case 0x0101: pin_ad_conf( &LPC_IOCON->R_PIO1_1,     0x02 ); return 2;
         case 0x0102: pin_ad_conf( &LPC_IOCON->R_PIO1_2,     0x02 ); return 3;
         case 0x0103: pin_ad_conf( &LPC_IOCON->SWDIO_PIO1_3, 0x02 ); return 4;
         case 0x0104: pin_ad_conf( &LPC_IOCON->PIO1_4,       0x01 ); return 5;
        
         default: HWLIB_PANIC_WITH_LOCATION;
      }          
   }     
   
   /// \endcond  
   
/// pin_in implementation for the LPC1114
class pin_in : public hwlib::pin_in {
private:
   uint32_t port, pin, mask;
   
public:

   /// LPC1114 pin_in constructor
   /// 
   /// Constructor for an LPC11114 input pin.
   ///
   /// This constructor sets the pin direction to input.   
   pin_in( uint32_t port, uint32_t pin ): 
      port{ port },
      pin{ pin },
      mask{ 0x01U << pin }
   {
      configure_as_gpio( port, pin );
      *gpioreg( port, 0x8000 ) &= ~ mask;
   }
   
   bool read() override {
      return *gpioreg( port, 0x3FFC ) & mask;
   }
   
   void refresh() override{
   }
   
};   

/// pin_out implementation for the LPC1114
class pin_out : public hwlib::pin_out {
private:
   uint32_t port, pin, mask;
   
public:

   /// LPC1114 pin_out constructor
   /// 
   /// Constructor for an LPC11114 output pin.
   ///
   /// This constructor sets the pin direction to output.   
   pin_out( uint32_t port, uint32_t pin ): 
      port{ port },
      pin{ pin },
      mask{ 0x01U << pin }
   {
      configure_as_gpio( port, pin );
      *gpioreg( port, 0x8000 ) |= mask ;   
   }
   
   void write( bool v ) override {
      *gpioreg( port, 0x04 << pin ) = v ? -1 : 0;
   }
   
   void flush() override{
   }   
   
};

/// pin_in_out implementation for the LPC1114
class pin_in_out : public hwlib::pin_in_out {
private:
   uint32_t port, pin, mask;
   
public:

   /// LPC1114 pin_out constructor
   ///
   /// Constructor for an LPC1114 input pin.
   ///
   /// This constructor doesn't set the pin direction 
   /// to input or output, a direction_set function must
   /// be called to do so.   
   pin_in_out( uint32_t port, uint32_t pin ): 
      port{ port },
      pin{ pin }, 
      mask{ 0x1U << pin }
   {
      configure_as_gpio( port, pin );
   }
   
   virtual void direction_set_input() override {
      *gpioreg( port, 0x8000 ) &= ~ mask;
   }
   
   bool read() override {
      return *gpioreg( port, 0x3FFC ) & mask;
   }
   
   virtual void direction_set_output() override {
     *gpioreg( port, 0x8000 ) |= mask ;    
   }
   
   void write( bool v ) override {
      *gpioreg( port, 0x04 << pin ) = v ? -1 : 0;
   }
   
   void refresh() override{
   }
   
   void flush() override{
   }   
   
   void direction_flush() override{
   } 
   
};   

/// pin_oc implementation for the LPC1114
class pin_oc : public hwlib::pin_oc {
private:
   uint32_t port, pin, mask;
   
public:

   /// LPC1114 pin_oc constructor
   ///
   /// Constructor for an LPC1114 input pin.
   ///
   /// This constructor sets the pin to high (high-impedance). 
   pin_oc( uint32_t port, uint32_t pin ): 
      port{ port },
      pin{ pin }, 
      mask{ 0x1U << pin }
   {
      configure_as_gpio( port, pin );
      *gpioreg( port, 0x8000 ) &= ~ mask;
   }
   
   bool read() override {
      return *gpioreg( port, 0x3FFC ) & mask;
   } 
   
   void write( bool v ) override {
      if( v ){
      
         // make the pin an input
         *gpioreg( port, 0x8000 ) &= ~ mask;
         
      } else {
         // make the pin an output
         *gpioreg( port, 0x8000 ) |= mask ;   
         
         // make the pin low
         *gpioreg( port, 0x04 << pin ) = 0;
         
      }
   }

   void refresh() override{
   }
   
   void flush() override{
   }   
   
};   

/// adc implementation for an LPC1114
class pin_adc : public hwlib::adc {   
private:
   uint32_t channel;      
      
public:
   
   /// create an A/D pin from its port and pin numbers
   pin_adc( uint32_t port, uint32_t pin )
      : adc{ 10 }, channel{ configure_as_adc( port, pin ) }
   {}         
      
   adc_value_type read() override {
      
      // configure the A/D for the pin
      LPC_ADC->CR = ( 0x01 << channel ) | ( 12 << 8 );
     
      // start the conversion
      LPC_ADC->CR |= ( 0x01 << 24 );
   
      // wait for the conversion to complete
      while( ( LPC_ADC->GDR & ( 1 << 31 )) == 0 );
         
      hwlib::wait_ms( 10 );
     
      // return the A/D result
      return 3 | (( LPC_ADC->GDR >> 6 ) & 0x3FF);   
   }
   
   void refresh() override {
   }
      
};

}; // namespace db103

namespace hwlib {

namespace target = db103;


// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE

/// the number of ticks per us
uint_fast64_t HWLIB_WEAK ticks_per_us(){
   return 12;
}

/// returns the number of ticks since some fixed starting point
uint_fast64_t HWLIB_WEAK now_ticks(){
   static bool init_done = false;
   if( ! init_done ){
            
      SysTick->CTRL  = 0;         // stop the timer
      SysTick->LOAD  = 0xFFFFFF;  // use its as a 24-bit timer
      SysTick->VAL   = 0;         // clear the timer
      SysTick->CTRL  = 5;         // start the timer, 1:1

      init_done = true;      
   }
   
   static unsigned int last_low = 0;
   static unsigned long long int high = 0;

   // the timer ticks down, but we want an up counter
   unsigned int low = 0xFFFFFF - ( SysTick->VAL & 0xFFFFFF );
   if( low < last_low ){
   
      // the timer rolled over, so increment the high part
      high += 0x1ULL << 24;
   }
   last_low = low;

   // return the aggregated ticks value
   // the counter runs at 84 MHz 
   return ( low | high ); 

} 

uint64_t now_us(){
   return now_ticks() / ticks_per_us();
} 

// busy waits

void wait_ns_busy( int_fast32_t n ){
   wait_us_busy( ( n + 999 ) / 1000 );
}

void HWLIB_WEAK wait_us_busy( int_fast32_t n ){
   // for the default clock frequency of 12 MHz:
   // the loop uses 12 cycles
   __asm volatile( 
      "   mov r0, %[reg]   \t\n"
      "   b   1f           \t\n"
      "   .align 4         \t\n"
      "1: sub r0, #1       \t\n" 
      "   b   2f           \t\n"
      "2: b   3f           \t\n"
      "3: nop              \t\n"
      "   nop              \t\n"
      "   bgt 1b           \t\n" 
      :: [reg] "r" (n) : "r0"
   );
}

void wait_ms_busy( int_fast32_t n ){
   while( n > 0 ){
      wait_us_busy( 1000 );
      --n;
   }   
} 

// non-busy waits

void HWLIB_WEAK wait_ns( int_fast32_t n ){
   wait_us( ( n + 999 ) / 1000 );
}

void HWLIB_WEAK wait_us( int_fast32_t n ){
   auto end = now_us() + n;
   while( now_us() < end ){
      background::do_background_work();	   
   }
}

void HWLIB_WEAK wait_ms( int_fast32_t n ){
   while( n > 0 ){
      wait_us( 1000 );
      --n;
   }   
} 

// hardware UART
// from https://github.com/zinahe/lpc1114/blob/master/UART.c
// and https://github.com/zinahe/lpc1114/blob/master/LPC1114.h

#define SYSAHBCLKCTRL_IOCON_BIT 		16
#define SYSAHBCLKCTRL_UART_BIT			12
#define UART_LCR_WORDLENGTH_08			0x03
#define UART_LCR_WORDLENGTH_BIT			0
#define UART_LCR_DLAB_BIT				7	
#define  MMIO(addr) 					(*(volatile int*) addr)
#define IOCON_PIO1_6					MMIO(0x400440A4)	
#define IOCON_PIO1_7					MMIO(0x400440A8)	
#define UART_LCR						MMIO(0x4000800C)
#define UART_RBR						MMIO(0x40008000)		
#define UART_THR						MMIO(0x40008000)
#define UART_DLL						MMIO(0x40008000)
#define UART_FDR						MMIO(0x40008028)	
#define UART_LSR						MMIO(0x40008014)
#define UARTCLKDIV						MMIO(0x40048098)
#define UART_LSR_THRE_BIT				5
#define UART_LSR_RDA_BIT				0
#define UART_LSR_RXFE_BIT				7

void hw_uart_init(void) {
   
   static bool init_done = false;
   if( init_done ){
      return;
   }
   init_done = true;   
	
	// Enable IOCON block  
	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << SYSAHBCLKCTRL_IOCON_BIT);
   
    LPC_IOCON->PIO1_6 &= ~0x07;    //Clear the first 3 bits in the FUNC of the 'PIO1_6'
    LPC_IOCON->PIO1_6 |= 0x01;     //Set PIO1_6 as UART RXD
    LPC_IOCON->PIO1_7 &= ~0x07;       //Clear the first 3 bits in the FUNC of the 'PIO1_7'
    LPC_IOCON->PIO1_7 |= 0x01;     //Set PIO1_7 as UART TXD   
	
	// Enable power to UART block
	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << SYSAHBCLKCTRL_UART_BIT);
	
	// Enable UART_PCKL divider to supply clock to the baud generator
	UARTCLKDIV = 0x01;
   
	// Set transmission parameters to 8N1 (8 data bits, NO partity, 1 stop bit, DLAB=1)
	UART_LCR = (UART_LCR_WORDLENGTH_08 << UART_LCR_WORDLENGTH_BIT) | (1 << UART_LCR_DLAB_BIT);
	
	// Set baud rate to 115200 kb/s @ UART_CLK of 12Mhz  (DLM = 0, DLL = 4, DIVADDVAL = 5, and MULVAL = 8)
	// UART_DLM = 0x00;		// Default
	UART_DLL = 0x04;
	UART_FDR = 0x85;		// FDR = (MULVAL << 4 ) | DIVADDVAL
	
	// Set baud rate to 115200 kb/s @ UART_CLK of 48Mhz  (DLM = 0, DLL = 17, DIVADDVAL = 8, and MULVAL = 15)
	// UART_DLM = 0x00;		// Default
	//UART_DLL = 0x11;		
	//UART_FDR = 0xF8;		// FDR = (MULVAL << 4 ) | DIVADDVAL
	
	// Turn off DLAB
	UART_LCR ^= (1 << UART_LCR_DLAB_BIT);
	
}

void hw_uart_write(char c) {
   
   hw_uart_init();
	
	// Wait while THR contains data (until empty)
	while( (UART_LSR & (1 << UART_LSR_THRE_BIT)) == 0 );
      
	// Send a byte from buffer
	UART_THR = c;
}

char hw_uart_read() {

   hw_uart_init();

	// Wait until there is data in RBR
	while( (UART_LSR & (1 << UART_LSR_RDA_BIT)) == 0);

	return UART_RBR;
}

// char IO

#ifdef BB_UART

void HWLIB_WEAK uart_putc( char c ){
   static target::pin_out pin( 1, 7 );
   uart_putc_bit_banged_pin( c, pin );
}

char HWLIB_WEAK uart_getc(){
   static target::pin_in pin( 1, 6 );
   return uart_getc_bit_banged_pin( pin );
}

#else
   
void uart_putc( char c ){
   hw_uart_write( c );
}

char uart_getc(){
   return hw_uart_read();
}
   
#endif

#endif // _HWLIB_ONCE

}; //namespace hwlib   

#endif // HWLIB_DB103_H