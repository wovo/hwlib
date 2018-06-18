// ==========================================================================
//
// File      : hwlib-frdm-kl27z.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// this file contains Doxygen lines
/// @file

#ifndef HWLIB_FRDM_KL27Z_H
#define HWLIB_FRDM_KL27Z_H

#include HWLIB_INCLUDE( hwlib-all.hpp )
#include "MKL27Z644.h"

namespace frdm_kl27z {

PORT_Type & __attribute__((weak)) port_registers( uint32_t port ){
   
   // a bit of a cludge to put this here:
   // enable the clock to all GPIO ports
   SIM->SCGC5 |= 0x1F << 9;

   switch( port ){
      case 0  : return *PORTA;
      case 1  : return *PORTB;
      case 2  : return *PORTC;
      case 3  : return *PORTD;
      case 4  : return *PORTE;
      default : break;
   }  
   
   // doesn't return   
   HWLIB_PANIC_WITH_LOCATION; 
}

GPIO_Type & __attribute__((weak)) gpio_registers( uint32_t port ){
   
   switch( port ){
      case 0  : return *GPIOA;
      case 1  : return *GPIOB;
      case 2  : return *GPIOC;
      case 3  : return *GPIOD;
      case 4  : return *GPIOE;
      default : break;
   }  
   
   // doesn't return   
   HWLIB_PANIC_WITH_LOCATION; 
}

class pin_in : public hwlib::pin_in {
private:
   GPIO_Type & gpio;
   PORT_Type & port;
   uint32_t mask;
   
public:

   pin_in( uint32_t port_number, uint32_t pin_number ): 
      gpio{ gpio_registers( port_number ) }, 
      port{ port_registers( port_number ) }, 
      mask{ 0x1U << pin_number }
   {
      port.PCR[ pin_number ] = PORT_PCR_MUX( 1 );
      gpio.PDDR &= ~mask;
   }  
     
   bool get( 
      hwlib::buffering buf = hwlib::buffering::unbuffered 
   ) override {
      return (( gpio.PDIR & mask ) != 0 );   
   }
};

class pin_out : public hwlib::pin_out {
private:
   GPIO_Type & gpio;
   PORT_Type & port;
   uint32_t mask;
   
public:

   pin_out( uint32_t port_number, uint32_t pin_number ): 
      gpio{ gpio_registers( port_number ) }, 
      port{ port_registers( port_number ) }, 
      mask{ 0x1U << pin_number }
   {
      port.PCR[ pin_number ] = PORT_PCR_MUX( 1 );
      gpio.PDDR |= mask;
   }   
   
   void set( 
      bool v,
      hwlib::buffering buf = hwlib::buffering::unbuffered  
   ) override {
      ( v 
         ?  gpio.PSOR 
         :  gpio.PCOR 
      )  = mask;
   }
};

class pin_in_out : public hwlib::pin_in_out {
private:
   GPIO_Type & gpio;
   PORT_Type & port;
   uint32_t mask;
   
public:

   pin_in_out( uint32_t port_number, uint32_t pin_number ): 
      gpio{ gpio_registers( port_number ) }, 
      port{ port_registers( port_number ) }, 
      mask{ 0x1U << pin_number }
   {}  
   
   void direction_set_input() override {
      gpio.PDDR &= ~mask;
   }
   
   bool get( 
      hwlib::buffering buf = hwlib::buffering::unbuffered 
   ) override {
      return (( gpio.PDIR & mask ) != 0 );   
   }
   
   void direction_set_output() override {
      gpio.PDDR |= mask;    
   }
   
   void set( 
      bool v,
      hwlib::buffering buf = hwlib::buffering::unbuffered  
   ) override {
      ( v 
         ?  gpio.PSOR 
         :  gpio.PCOR 
      )  = mask;
   }
};   

class pin_oc : public hwlib::pin_oc {
private:
   GPIO_Type & gpio;
   PORT_Type & port;
   uint32_t mask;
   
public:

   pin_oc( uint32_t port_number, uint32_t pin_number ): 
      gpio{ gpio_registers( port_number ) }, 
      port{ port_registers( port_number ) }, 
      mask{ 0x1U << pin_number }
   {
      gpio.PDDR &= ~mask;
   }
   
   bool get( 
      hwlib::buffering buf = hwlib::buffering::unbuffered 
   ) override {
      return (( gpio.PDIR & mask ) != 0 );   
   }
   
   void set( 
      bool v,
      hwlib::buffering buf = hwlib::buffering::unbuffered 
   ) override {
      if( v ){
         gpio.PDDR &= ~mask;
      } else {
         gpio.PDDR |= mask;   
         gpio.PCOR = mask;
      }
   }

};

uint_fast64_t HWLIB_WEAK ticks_per_us(){
   return 8;
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
   return ( low | high ); 

} 

#ifdef nono

void uart_init();
bool uart_char_available();
char uart_getc();
void uart_putc( char c );

#ifdef HWLIB_ONCE

Uart * hw_uart = UART;

void uart_init(){
   static bool init_done = false;
   if( init_done ){
      return;
   }
   init_done = true;

    // enable the clock to port A
    PMC->PMC_PCER0 = 1 << ID_PIOA;
	
    // disable PIO Control on PA9 and set up for Peripheral A
	PIOA->PIO_PDR   = PIO_PA8; 
	PIOA->PIO_ABSR &= ~PIO_PA8; 
	PIOA->PIO_PDR   = PIO_PA9; 
	PIOA->PIO_ABSR &= ~PIO_PA9; 

	// enable the clock to the UART
    PMC->PMC_PCER0 = ( 0x01 << ID_UART );

    // Reset and disable receiver and transmitter.
    hw_uart->UART_CR = UART_CR_RSTRX | UART_CR_RSTTX | UART_CR_RXDIS | UART_CR_TXDIS;

    // Set the baudrate to 115200.
    //hw_uart->UART_BRGR = 45; // MASTER_CLK_FREQ / (16 * 45) = 116666 (close enough).
    //uart->UART_BRGR = 546; // For ~9600 baud.
    hw_uart->UART_BRGR = 5241600 / BMPTK_BAUDRATE; 

    // No parity, normal channel mode.
    hw_uart->UART_MR = UART_MR_PAR_NO;

    // Disable all interrupts.	  
    hw_uart->UART_IDR = 0xFFFFFFFF;   

    // Enable the receiver and thes trasmitter.
    hw_uart->UART_CR = UART_CR_RXEN | UART_CR_TXEN;      
}

bool uart_char_available(){
   uart_init();	
   return ( hw_uart->UART_SR & 1 ) != 0;
}

char uart_getc(){
   // uart_init() is not needed because uart_char_available does that
   while( ! uart_char_available() ){}
   return hw_uart->UART_RHR; 
}

void uart_putc( char c ){
   uart_init();	
   while( ( hw_uart->UART_SR & 2 ) == 0 ){}
   hw_uart->UART_THR = c;
}

#endif

#endif // nono

};

namespace hwlib {

namespace target = ::frdm_kl27z;
  
void wait_ns( int_fast32_t n );
void wait_us( int_fast32_t n );
void wait_ms( int_fast32_t n ); 

//#define HWLIB_USE_HW_UART 
#ifdef HWLIB_USE_HW_UART

void HWLIB_WEAK uart_putc( char c ){
   due::uart_putc( c );
}

bool HWLIB_WEAK uart_char_available(){
   return due::uart_char_available();
}

char HWLIB_WEAK uart_getc( ){
   return due::uart_getc();
}

#else

void HWLIB_WEAK uart_putc( char c ){
   static target::pin_out pin( 0, 9 );
   uart_putc_bit_banged_pin( c, pin );
}

bool HWLIB_WEAK uart_char_available(){
   static target::pin_in pin( 0, 8 );
   return ! pin.get();
}

char HWLIB_WEAK uart_getc( ){
   static target::pin_in pin( 0, 8 );
   return uart_getc_bit_banged_pin( pin );
}

#endif

#ifdef HWLIB_ONCE

uint64_t now_ticks(){
   return target::now_ticks();
}   

uint64_t ticks_per_us(){
   return target::ticks_per_us();
}   

uint64_t now_us(){
   return now_ticks() / ticks_per_us();
}   

void wait_us_busy( int_fast32_t n ){
   auto end = now_us() + n;
   while( now_us() < end ){}
}

void HWLIB_WEAK wait_us( int_fast32_t n ){ 
   wait_us_busy( n );
}

void HWLIB_WEAK wait_ms( int_fast32_t n ){
   while( n > 0 ){
      wait_us( 1'000 );
      --n;
   }   
}  

#endif

}; //namespace hwlib   

#endif // #ifdef HWLIB_FRDM_KL27Z_H
