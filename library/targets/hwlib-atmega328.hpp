// ==========================================================================
//
// File      : hwlib-atmega328.hpp
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

#ifndef HWLIB_ATMEGA328_H
#define HWLIB_ATMEGA328_H

#define _HWLIB_TARGET_WAIT_US_BUSY
#include HWLIB_INCLUDE( ../hwlib-all.hpp )

#include <stdint.h>

#include "avr/io.h"

namespace atmega328 {

volatile uint8_t & HWLIB_WEAK port_data( uint_fast8_t port ){
   switch( port ){
      // case 0  : return PORTA;
      case 1  : return PORTB;
      case 2  : return PORTC;
      case 3  : return PORTD;
      default : break;
   }   
   HWLIB_PANIC_WITH_LOCATION; 
   // doesn't return
}

volatile uint8_t & HWLIB_WEAK port_input( uint_fast8_t port ){
   switch( port ){
      // case 0  : return DDRA;
      case 1  : return PINB;
      case 2  : return PINC;
      case 3  : return PIND;
      default : break;
   }   
   HWLIB_PANIC_WITH_LOCATION; 
   // doesn't return
}

volatile uint8_t & HWLIB_WEAK port_direction( uint_fast8_t port ){
   switch( port ){
      // case 0  : return DDRA;
      case 1  : return DDRB;
      case 2  : return DDRC;
      case 3  : return DDRD;
      default : break;
   }   
   HWLIB_PANIC_WITH_LOCATION; 
   // doesn't return
}

void HWLIB_WEAK configure_as_gpio( uint_fast8_t port, uint_fast8_t pin ){
   if( port == 3 ){
      if( pin == 0 ) {
         UCSR0B &= ~ 0x10; // disable UART receive
      }
      if( pin == 1 ){
         UCSR0B &= ~ 0x08; // disable UART transmit
      }
   }
}

class pin_adc : public hwlib::adc {
private:
   uint_fast8_t pin;

public:

   pin_adc( uint_fast8_t pin ):
      adc( 10 ),
      pin( pin )
   {
      
      // reference is AVCC
      ADMUX = 0x01 << REFS0;
	  
      // Enable the ADC and prescale
      ADCSRA = 7 | ( 0x01 << ADEN );  
   }

   uint_fast32_t read() override {
	   
      // select the ADC input pin 
      ADMUX = ( 0x01 << REFS0 ) | pin;

      // start the conversion.
      ADCSRA |= 0x01 << ADSC;

      // wait for the conversion to finish
      while ( (ADCSRA & ( 0x01 << ADSC )) != 0 ){}

      return ADCW;
   }

   void refresh() override {}
   
};
   
/// pin_in implementation for an ATMega328P
class pin_in : public hwlib::pin_in {
private:

   volatile uint8_t & port_out;
   volatile uint8_t & port_in;
   uint8_t mask;
   
   void write( bool v ){
      if( v ){
         port_out |= mask;
      } else {
         port_out &= ~mask;
      }
   }   
 
public:

   /// pin_in constructor from ATMega328P port/pin numbers
   ///
   /// This call creates a pin_in from an ATMega328P port/pin
   /// number pair.
   ///
   /// This constructor sets the pin direction to input.
   pin_in( uint8_t port_number, uint8_t pin_number ): 
      port_out{ port_data( port_number ) },   
      port_in{ port_input( port_number ) }, 
      mask( 0x1 << pin_number )
   {
      configure_as_gpio( port_number, pin_number );
      port_direction( port_number ) &= ~mask;
   }
      
   bool read() override {
      return ( port_in & mask ) != 0;   
   }
   
   void refresh() override {}
   
   void pullup_enable(){
      write( 1 );
   }

   void pullup_disable(){
      write( 0 );
   }   
   
};

/// pin_out implementation for a ATMega328P
class pin_out : public hwlib::pin_out {
private:
   volatile uint8_t & port_out;
   uint8_t mask;
   
public:

   /// pin_out constructor from ATMega328P port/pin numbers
   ///
   /// This call creates a pin_out from an ATMega328P port/pin
   /// number pair.
   ///
   /// This constructor sets the pin direction to output.
   pin_out( uint8_t port_number, uint8_t pin_number ): 
      port_out{ port_data( port_number ) }, 
      mask( 0x1 << pin_number )
   {
      configure_as_gpio( port_number, pin_number );
      port_direction( port_number ) |= mask;
   }
     
   void write( bool v ) override {
      if( v ){
         port_out |= mask;
      } else {
         port_out &= ~mask;
      }
   }

   void flush() override {}

};

/// pin_in_out implementation for a ATMega328P
class pin_in_out : public hwlib::pin_in_out {
private:

   volatile uint8_t & port_in;
   volatile uint8_t & port_out;
   uint8_t port_number;
   uint8_t mask;
   
public:

   /// pin_in_out constructor
   ///
   /// Constructor for a ATMega328P input/output pin.
   ///
   /// This constructor doesn't set the pin direction 
   /// to input or output, a direction_set function must
   /// be called to do so.
   pin_in_out( uint8_t port_number, uint8_t pin_number ): 
      port_in{ port_input( port_number ) }, 
      port_out{ port_data( port_number ) }, 
      port_number( port_number ),
      mask( 0x1 << pin_number )
   {
      configure_as_gpio( port_number, pin_number );
   }
      
   virtual void direction_set_input() override {
      port_direction( port_number ) &= ~ mask;
   }
   
   bool read() override {
      return ( port_in & mask ) != 0;   
   }
   
   virtual void direction_set_output() override {
      port_direction( port_number ) |= mask;   
   }
   
   void write( bool v ) override {
      if( v ){
         port_out |= mask;
      } else {
         port_out &= ~mask;
      }
   }
   
   void refresh() override {}
   
   void flush() override {}

   void direction_flush() override {}
   
   void pullup_enable(){
      write( 1 );
   }

   void pullup_disable(){
      write( 0 );
   }      
   
};   

/// pin_oc implementation for a ATMega328P
class pin_oc : public hwlib::pin_oc {
private:

   volatile uint8_t & port_in;
   volatile uint8_t & port_out;
   uint8_t port_number;
   uint8_t mask;
   
public:

   /// pin_oc constructor
   ///
   /// The port_number and pin_number refer to the chip, 
   /// not to the Arduino board pin names.
   ///
   /// This constructor sets the pin to high (high-impedance). 
   pin_oc( uint8_t port_number, uint8_t pin_number ): 
      port_in{ port_input( port_number ) }, 
      port_out{ port_data( port_number ) }, 
      port_number( port_number ),
      mask( 0x1 << pin_number )
   {
      configure_as_gpio( port_number, pin_number );
   }
     
   bool read() override {
      return ( port_in & mask ) != 0;   
   }   
   
   void write( bool v ) override {
      if( v ){
         port_direction( port_number ) &= ~ mask;
      } else {
         port_direction( port_number ) |= mask;
         port_out &= ~mask;
      }
   }

   void refresh() override {}
   
   void flush() override {}
};

bool uart_char_available();
char uart_getc();
void uart_putc( char c );

#ifdef _HWLIB_ONCE

void uart_init(){
   static bool init_done = false;
   if( init_done ){
      return;
   }
   init_done = true;

   // set baudrate	   
   uint64_t UBRR_VALUE = ((( 16'000'000 / ( BMPTK_BAUDRATE * 16UL ))) - 1 );
   UBRR0H = (uint8_t) ( UBRR_VALUE >> 8 );
   UBRR0L = (uint8_t) UBRR_VALUE;
	  
   // format : 8 data bits, no parity, 1 stop bit
   UCSR0C = 0x06;
  
  // enable rx and tx
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
}

bool uart_char_available(){
   uart_init();	
   return ( UCSR0A & ( 0x01<<RXC0 ));
}

char uart_getc(){
   // uart_init() is not needed because uart_char_available does that
   while( ! uart_char_available() ){
      hwlib::background::do_background_work();	   
   }
   return UDR0; 
}

void uart_putc( char c ){
   uart_init();	
   while( !( UCSR0A & ( 0x01 << UDRE0 ))){
      hwlib::background::do_background_work();	   
   }
   UDR0 = c;
}

#endif // _HWLIB_ONCE

}; // namespace atmega328

namespace hwlib {
   
const auto target_chip  = target_chips::atmega328p;   
  
#ifdef _HWLIB_ONCE
   
void HWLIB_WEAK wait_us_asm( int n ){ 
    // first int parameter is passd in r24/r25
    __asm volatile(                  // clocks
       "1:  cp    r1, r24     \t\n"   // 1
       "    cpc   r1, r25     \t\n"   // 1
       "    brge  3f          \t\n"   // 1
       "    rcall 3f          \t\n"   // 7
       "    rjmp  2f          \t\n"   // 2
       "2:  sbiw  r24, 0x01   \t\n"   // 2
       "    rjmp  1b          \t\n"   // 2
       "3:                    \t\n"   // 16 total
       : : "r" ( n )                  // uses (reads) n
   ); 
    
}

/*
void HWLIB_WEAK wait_us_busy( int_fast32_t n ){ 
   while( n > 0 ){
      if( n < 10'000 ){
          wait_us_asm( n );
          return;
      }
      wait_us_asm( 1'000 );
      n -= 1'000;
   }
}
*/ 

/// the number of ticks per us
uint_fast64_t ticks_per_us(){
   return 16;
}

//static inline uint16_t       last_low = 0;
//static inline uint_fast64_t  high = 0;
static uint16_t       last_low = 0;
static uint_fast64_t  high = 0;

uint_fast64_t now_ticks(){
   
   static bool init_done = false;
   if( ! init_done ){
      // set up timer 1 without prescaler (input=CPU clock)
      TCCR1B = 0x01;   
      init_done = true;      
   }

   uint16_t low = TCNT1L;
   low |= ( TCNT1H << 8 );

   if( low < last_low ){
   
       // the timer rolled over, so increment the high part
      high += 0x1ULL << 16;
   }
   last_low = low;

   return ( low | high ); 
} 

uint64_t now_us(){
   return now_ticks() / ticks_per_us();
}   

// busy waits

void wait_ns_busy( int_fast32_t n ){
   wait_us_busy( ( n + 999 ) / 1000 );
}

void wait_us_busy( int_fast32_t n ){
   auto end = now_us() + n;
   while( now_us() < end ){}
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

#define HWLIB_USE_HW_UART 
#ifdef HWLIB_USE_HW_UART

void HWLIB_WEAK uart_putc( char c ){
   atmega328::uart_putc( c );
}

bool HWLIB_WEAK uart_char_available(){
   return atmega328::uart_char_available();
}

char HWLIB_WEAK uart_getc( ){
   return atmega328::uart_getc();
}

#else

void HWLIB_WEAK uart_putc( char c ){
   static atmega328::pin_out pin( 3, 1 );
   uart_putc_bit_banged_pin( c, pin );
}

char HWLIB_WEAK uart_getc(){
   static atmega328::pin_in pin( 1, 6 );
   return uart_getc_bit_banged_pin( pin );
}

#endif

#endif

}; //namespace hwlib   

#endif // HWLIB_ATMGEA328_H
