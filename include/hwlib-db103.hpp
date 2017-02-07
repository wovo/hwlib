// ==========================================================================
//
// File      : hwlib-db103.hpp
// Part of   : hwlib library for V1OOPC and V1IPAS
// Copyright : wouter@voti.nl 2016
//
// hwlib implementation for a DB103 (LPC1114FN28 chip)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef HWLIB_DB103_H
#define HWLIB_DB103_H

#include "hwlib-all.hpp"
#include "LPC11xx.h"

/// hwlib implementation for the DB103 board
//
/// \image html db103-pcb.jpg
//
/// This namespace contains the hwlib implementation of the pins, timing
/// and (sotware) UART output for the DB103 board (LPC1111FN28/102 chip).
/// The chip runs at its default speed of 12 MHz, 
/// from its internal RC oscillator.
///
/// The port and pin parameters to the constructors of the pin classes
/// refer to the LPC1114 ports and pins, as shown on the DB103 PCB.
///
/// The chip runs at 3.3 Volt and that is the level on its IO pins.
///
/// References:
///    - <A HREF="http://www.nxp.com/documents/user_manual/UM10398.pdf">
///       LPC1114 user manual</A> (pdf)
///
namespace db103 {
   
   /// \cond INTERNAL    

   // return the pointer to an IO port related register
   volatile __attribute__((weak)) int *gpioreg( int port, int offset ){
      return (volatile int *)( 0x50000000 + port * 0x10000 + offset );
   }
   
   // configure a pin that has no AD capability
   void __attribute__((weak)) pin_gp_conf( volatile uint32_t *p, int value ){
      *p = value | ( *p & ~0x07 );
   }   

   // configure a pin with AD capability  
   void __attribute__((weak)) pin_ad_conf( volatile uint32_t *p, int value ){
      *p = 
         ( value << 0 ) 
         | ( *p & ~ ( ( 0x07 << 0 ) | ( 0x01 << 7 )));
   }   
   
   // configure a pin as GPIO
   void __attribute__((weak)) configure_as_gpio( int port, int pin ){
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
   int __attribute__((weak)) configure_as_adc( int port, int pin ){ 
   
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
   int port, pin, mask;
   
public:

   /// LPC1114 pin_in constructor
   //
   /// Constructor for an LPC11114 input pin.
   ///
   /// This constructor sets the pin direction to input.   
   pin_in( int port, int pin ): 
      port{ port },
      pin{ pin },
      mask{ 0x01 << pin }
   {
      configure_as_gpio( port, pin );
      *gpioreg( port, 0x8000 ) &= ~ mask;
   }
   
   bool get() override {
      return *gpioreg( port, 0x3FFC ) & mask;
   }
};   

/// pin_out implementation for the LPC1114
class pin_out : public hwlib::pin_out {
private:
   int port, pin, mask;
   
public:

   /// LPC1114 pin_out constructor
   //
   /// Constructor for an LPC11114 output pin.
   ///
   /// This constructor sets the pin direction to output.   
   pin_out( int port, int pin ): 
      port{ port },
      pin{ pin },
      mask{ 0x01 << pin }
   {
      configure_as_gpio( port, pin );
      *gpioreg( port, 0x8000 ) |= mask ;   
   }
   
   void set( bool v ) override {
      *gpioreg( port, 0x04 << pin ) = v ? -1 : 0;
   }
};

/// pin_in_out implementation for the LPC1114
class pin_in_out : public hwlib::pin_in_out {
private:
   int port, pin, mask;
   
public:

   /// LPC1114 pin_out constructor
   //
   /// Constructor for an LPC1114 input pin.
   ///
   /// This constructor doesn't set the pin direction 
   /// to input or output, a direction_set function must
   /// be called to do so.   
   pin_in_out( int port, int pin ): 
      port{ port },
      pin{ pin }, 
      mask{ 0x1 << pin }
   {
      configure_as_gpio( port, pin );
   }
   
   virtual void direction_set_input() override {
      *gpioreg( port, 0x8000 ) &= ~ mask;
   }
   
   bool get() override {
      return *gpioreg( port, 0x3FFC ) & mask;
   }
   
   virtual void direction_set_output() override {
     *gpioreg( port, 0x8000 ) |= mask ;    
   }
   
   void set( bool v ) override {
      *gpioreg( port, 0x04 << pin ) = v ? -1 : 0;
   }
};   

/// pin_oc implementation for the LPC1114
class pin_oc : public hwlib::pin_oc {
private:
   int port, pin, mask;
   
public:

   /// LPC1114 pin_oc constructor
   //
   /// Constructor for an LPC1114 input pin.
   ///
   /// This constructor sets the pin to high (high-impedance). 
   pin_oc( int port, int pin ): 
      port{ port },
      pin{ pin }, 
      mask{ 0x1 << pin }
   {
      configure_as_gpio( port, pin );
      *gpioreg( port, 0x8000 ) &= ~ mask;
   }
   
   bool get() override {
      return *gpioreg( port, 0x3FFC ) & mask;
   } 
   
   void set( bool v ) override {
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
};   

   class pin_adc : public hwlib::adc {   
   private:
      int channel;      
      
   public:
   
      pin_adc( int port, int pin )
         : adc{ 10 }, channel{ configure_as_adc( port, pin ) }
      {}         
      
      adc_value_type get() override {
      
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
   };


}; // namespace db103

namespace hwlib {

namespace target = db103;

void HWLIB_WEAK wait_ns( int_fast32_t n ){
   wait_us( n / 1000 );
}

void HWLIB_WEAK wait_us( int_fast32_t n ){
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

void HWLIB_WEAK wait_ms( int_fast32_t n ){
   while( n > 0 ){
      wait_us( 1000 );
      --n;
   }   
}

void HWLIB_WEAK uart_putc( char c ){
   static target::pin_out pin( 1, 7 );
   uart_putc_bit_banged_pin( c, pin );
}

}; //namespace hwlib   

#endif // HWLIB_DB103_H