// ==========================================================================
//
// File      : hwlib-stm32f103c8.hpp
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

#ifndef HWLIB_STM32F103C8_H
#define HWLIB_STM32F103C8_H

#include HWLIB_INCLUDE( ../hwlib-all.hpp )

// the STM header files use 'register' in the pre-C++17 sense
#define register
#include "stm32f103x6.h"
#undef register

/// \brief
/// hwlib HAL for the stm32f103c8 
/// 
/// This namespace contains the hwlib implementation of the pins, timing
/// and (software) UART output for the stm32f103c8.
///
/// Initially, the chip runs from its HSI internal RC oscillator at 8 MHz. 
/// The first wait call configures the chip to run at 72 MHz, 
/// assuming an 8 MHz crystal.
///
/// The chip runs at 3.3 Volt and that is the level on its IO pins.
///
/// References:
///    - <A HREF="http://www.st.com/content/ccc/resource/technical/document/reference_manual/59/b9/ba/7f/11/af/43/d5/CD00171190.pdf/files/CD00171190.pdf/jcr:content/translations/en.CD00171190.pdf">
///       RM0008 STM32F1xxx reference manual</A> (pdf)
///    - <A HREF="http://www.st.com/content/ccc/resource/technical/document/datasheet/33/d4/6f/1d/df/0b/4c/6d/CD00161566.pdf/files/CD00161566.pdf/jcr:content/translations/en.CD00161566.pdf">
///       STM32Fl03x8 datasheet</A> (pdf)
///
namespace stm32f103c8 {
    
/// GPIO pin names
enum class pins {
   a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15,
   b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13, b14, b15,
   c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15,
   led,
/// \cond INTERNAL    
   SIZE_THIS_IS_NOT_A_PIN
/// \endcond   
};  

/// \cond INTERNAL    
struct pin_info_type { 
   uint8_t port; 
   uint8_t pin; 
};  

const HWLIB_WEAK pin_info_type & pin_info( pins name ){
   
   static const pin_info_type pin_info_array[ (int) pins::SIZE_THIS_IS_NOT_A_PIN ] = {
      { 0,  0 },  // a0
      { 0,  1 },  // a1
      { 0,  2 },  // a2
      { 0,  3 },  // a3
      { 0,  4 },  // a4
      { 0,  5 },  // a5
      { 0,  6 },  // a6
      { 0,  7 },  // a7
      
      { 0,  8 },  // a8
      { 0,  9 },  // a9
      { 0, 10 },  // a10
      { 0, 11 },  // a11
      { 0, 12 },  // a12
      { 0, 13 },  // a13
      { 0, 14 },  // a14
      { 0, 15 },  // a15

      { 1,  0 },  // b0
      { 1,  1 },  // b1
      { 1,  2 },  // b2
      { 1,  3 },  // b3
      { 1,  4 },  // b4
      { 1,  5 },  // b5
      { 1,  6 },  // b6
      { 1,  7 },  // b7
      
      { 1,  8 },  // b8
      { 1,  9 },  // b9
      { 1, 10 },  // b10
      { 1, 11 },  // b11
      { 1, 12 },  // b12
      { 1, 13 },  // b13
      { 1, 14 },  // b14
      { 1, 15 },  // b15
      
      { 2,  0 },  // c0
      { 2,  1 },  // c1
      { 2,  2 },  // c2
      { 2,  3 },  // c3
      { 2,  4 },  // c4
      { 2,  5 },  // c5
      { 2,  6 },  // c6
      { 2,  7 },  // c7
      
      { 2,  8 },  // c8
      { 2,  9 },  // c9
      { 2, 10 },  // c10
      { 2, 11 },  // c11
      { 2, 12 },  // c12
      { 2, 13 },  // c13
      { 2, 14 },  // c14
      { 2, 15 },  // c15
      
      { 2, 13 }   // led
      
   };      
      
   uint_fast8_t n = static_cast< uint_fast8_t>( name );
   if( n >= static_cast< uint_fast8_t>( pins::SIZE_THIS_IS_NOT_A_PIN )){
      HWLIB_PANIC_WITH_LOCATION;
   }
   return pin_info_array[ n ];
   
}
/// \endcond   
   
/// \cond INTERNAL 
GPIO_TypeDef & __attribute__((weak)) port_registers( uint32_t port ){
   
   // a bit of a cludge to put this here:
   // enable the clock to all GPIO ports
   RCC->APB2ENR |= 
      RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | 
      RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPDEN;

   switch( port ){
      case 0  : return *GPIOA;
      case 1  : return *GPIOB;
      case 2  : return *GPIOC;
      case 3  : return *GPIOD;
      default : break;
   }  
   
   // doesn't return   
   HWLIB_PANIC_WITH_LOCATION; 
}

class pin_base {
public:
   volatile GPIO_TypeDef & port;
   volatile uint32_t     & config_word;
   uint32_t     pin;
   uint32_t     config_offset;
   uint32_t     mask;   
   
   void config( uint32_t conf ){
      config_word &= ~( 0xF << config_offset );
      config_word |= conf << config_offset;   
   }
   
   pin_base( uint32_t port_number, uint32_t pin_number, uint32_t conf ): 
      port{ port_registers( port_number ) }, 
      config_word{ ( pin_number < 8 ) ? port.CRL : port.CRH },
      pin{ pin_number },
      config_offset{ 4 * ( pin_number % 8 ) }, 
      mask{ 0x1U << pin_number }
   {
      config( conf );     
   }
   
   bool base_read(){
      return (( port.IDR & mask ) != 0 );   
   }   
   
   void base_write( bool v ){
      port.BSRR |= ( v ? mask : ( mask << 16 ));
   }
   
};
/// \endcond 

/// pin_in implementation for an stm32f103c8
class pin_in : public hwlib::pin_in, private pin_base {
public:

   /// stm32f103c8 pin_in constructor
   /// 
   /// Construct an stm32f103c8 input pin 
   /// from its port and pin numbers.
   ///
   /// This constructor sets the pin direction to input.
   /// By default, the internal weak pull-up is enabled.
   pin_in( uint32_t port_number, uint32_t pin_number ): 
      pin_base{ port_number, pin_number, 0x08 }
   {} 
   
   /// stm32f103c8 pin_in constructor
   /// 
   /// Construct an stm32f103c8 input pin 
   /// from its blue-pill pin name.
   ///
   /// This constructor sets the pin direction to input.
   /// By default, the internal weak pull-up is enabled.
   pin_in( pins name ): 
      pin_in{ 
         pin_info( name ).port, 
         pin_info( name ).pin 
      }
   {}     
   
   bool read() override {
      return base_read();  
   }

   void refresh() override {}


};

/// pin_out implementation for an stm32f103c8
class pin_out : public hwlib::pin_out, private pin_base {
public:

   /// stm32f103c8 pin_out constructor
   /// 
   /// Construct an stm32f103c8 output pin
   /// from its port and pin numbers.
   ///
   /// This constructor sets the pin direction to output.
   ///
   /// This constructor doesn't set the pin value 
   /// to high or low, the set function must
   /// be called to do so.   
   pin_out( uint32_t port_number, uint32_t pin_number ):    
      pin_base{ port_number, pin_number, 0x03 }
   {} 
   
    /// stm32f103c8 pin_out constructor
   /// 
   /// Construct an stm32f103c8 output pin
   /// from its blue-pill pin name.
   ///
   /// This constructor sets the pin direction to output.
   ///
   /// This constructor doesn't set the pin value 
   /// to high or low, the set function must
   /// be called to do so.   
   pin_out( pins name ): 
      pin_out{ 
         pin_info( name ).port, 
         pin_info( name ).pin 
      }
   {}    
   
   void write( bool v ) override {
      base_write( v );
   }

   void flush() override {}

};

/// pin_in_out implementation for an stm32f103c8
class pin_in_out : public hwlib::pin_in_out, private pin_base {  
public:

   /// stm32f103c8 pin_out constructor
   /// 
   /// Construct an stm32f103c8 input/output pin
   /// from its port and pin numbers.
   ///
   /// This constructor doesn't set the pin direction 
   /// to input or output, a direction_set function must
   /// be called to do so.
   ///
   /// This constructor doesn't set the pin value 
   /// to high or low, the set function must
   /// be called to do so.
   pin_in_out( uint32_t port_number, uint32_t pin_number ):    
      pin_base{ port_number, pin_number, 0x08 }
   {} 
   
   /// stm32f103c8 pin_out constructor
   /// 
   /// Construct an stm32f103c8 input/output pin
   /// from its blue-pill pin name.
   ///
   /// This constructor doesn't set the pin direction 
   /// to input or output, a direction_set function must
   /// be called to do so.
   ///
   /// This constructor doesn't set the pin value 
   /// to high or low, the set function must
   /// be called to do so.
   pin_in_out( pins name ): 
      pin_in_out{ 
         pin_info( name ).port, 
         pin_info( name ).pin 
      }
   {}    
   
   void direction_set_input() override {
      config( 0x08 );  
   }
   
   bool read() override {
      return base_read();     
   }   
   
   void direction_set_output() override {
      config( 0x03 );   
   }
   
   void write( bool v ) override {
      base_write( v );
   }

   void flush() override {}
   void refresh() override {}
   void direction_flush() override {}

};

/// 36kHz output on pin chip PA6 (blue pill A6)
///
/// This class provides a 36 kHz output on chip pin PA6
///  that can be enabled or disabled by calling
/// write( 1 ) resp. write( 0 ).
class a6_36kHz : public hwlib::pin_out {
public:

    /// create the 36kHz output
    a6_36kHz(){
       RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;  // Enable GPIO port a
       RCC->APB1ENR |= RCC_APB1ENR_TIM3EN ; // Enable Timer 3


       GPIOA->CRL = GPIO_CRL_MODE6 | GPIO_CRL_CNF6_1; // Set Pin A6 to alternate function Push-Pull

       TIM3->ARR = 221; // Auto reload value
       TIM3->PSC = 0; // Capture Compare preload, for duty cycle
       TIM3->CCR1  = 111;

       TIM3->CCMR1  = TIM_CCMR1_OC1M | TIM_CCMR1_OC1PE;
       TIM3->EGR |= TIM_EGR_UG; // Trigger update for Timer 3 (to preload)

       write( 0 );

       TIM3->CR1 |= TIM_CR1_ARPE; // Enable auto-  reload preload on Timer 3
       TIM3->CR1 |= TIM_CR1_CEN; // Enable Timer 3

    }

    /// enable or disable the 36 kHz output
    //
    /// Calling write( 1 ) enables the 36 kHz output, calling write( 0 )
    /// disables the output and makes the output low.
    void write( bool b ) override {
       if( b ){
          TIM3->CCER |= TIM_CCER_CC1E;
       } else {
          TIM3->CCER &= ~TIM_CCER_CC1E;
       }
    }

    void flush() override {};

}; // class a6_36kHz


/// pin_oc implementation for an stm32f103c8
class pin_oc : public hwlib::pin_oc, private pin_base {
public:

   /// stm32f103c8 pin_oc constructor
   /// 
   /// Construct an stm32f103c8 open-collector pin
   /// from its port and pin numbers.
   ///
   /// This constructor doesn't set the pin value 
   /// to high or low, the set function must
   /// be called to do so.
   pin_oc( uint32_t port_number, uint32_t pin_number ):    
      pin_base{ port_number, pin_number, 0x07 }
   {} 
   
   /// stm32f103c8 pin_oc constructor
   /// 
   /// Construct an stm32f103c8 open-collector pin
   /// from its blue-pill pin name.
   ///
   /// This constructor doesn't set the pin value 
   /// to high or low, the set function must
   /// be called to do so.
   pin_oc( pins name ): 
      pin_oc{ 
         pin_info( name ).port, 
         pin_info( name ).pin 
      }
   {}    
   
   bool read() override {
      return base_read();   
   }   
   
   void write( bool v ) override {
      base_write( v );
   }

   void flush() override {}
   void refresh() override {}

};

/// the number of ticks per us
uint_fast64_t HWLIB_WEAK ticks_per_us(){
   return 8; //72;
}

/// returns the number of ticks since some fixed starting point
uint_fast64_t HWLIB_WEAK now_ticks(){
    
   static bool init_done = false;
   if( ! init_done ){
/*      
      // switch to the 72 MHz crystal/PLL clock, from stm32x.cpp,
      // some values taken from
      // https://github.com/rogerclarkmelbourne/STM32duino-bootloader
      
      // Flash 2 wait state 
      FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
      FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;    

      // Enable Prefetch Buffer 
      FLASH->ACR |= FLASH_ACR_PRFTBE;      
	  
	  // enable HSE and wait for it
	  RCC->CR |= RCC_CR_HSEON;
      while((RCC->CR & RCC_CR_HSERDY ) == 0 ){}
          
      
      //  PLL configuration: PLLCLK = HSE * 9 = 72 MHz 
      RCC->CFGR &= (uint32_t)((uint32_t)~( 
	     RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL ));
      RCC->CFGR |= (uint32_t)( RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL9 );
       
      // Enable PLL and wait for it
      RCC->CR |= RCC_CR_PLLON;
      while((RCC->CR & RCC_CR_PLLRDY) == 0){}     

      // HCLK = SYSCLK 
      RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
          
      // PCLK2 = HCLK 
      RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        
      // PCLK1 = HCLK / 2
      RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;

      // Select PLL as system clock source
      RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
      RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

      // Wait till PLL is used as system clock source
      while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08){}
*/
      // start the systick timer      
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

/// \cond INTERNAL    
void uart_init();
/// \endcond   

bool uart_char_available();
char uart_getc();
void uart_putc( char c );

#ifdef _HWLIB_ONCE

// Uart * hw_uart = UART;

void uart_init(){
   static bool init_done = false;
   if( init_done ){
      return;
   }
   init_done = true;
   
   /*

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
*/  
}


/*
bool uart_char_available(){
   uart_init(); 
   return ( hw_uart->UART_SR & 1 ) != 0;
}

char uart_getc(){
   // uart_init() is not needed because uart_char_available does that
   while( ! uart_char_available() ){
      hwlib::background::do_background_work();	   
   }	   
   return hw_uart->UART_RHR; 
}

void uart_putc( char c ){
   uart_init(); 
   while( ( hw_uart->UART_SR & 2 ) == 0 ){
      hwlib::background::do_background_work();	   
   }
   hw_uart->UART_THR = c;
}
*/

#endif

}; // namespace stm32f103c8

namespace hwlib {

namespace target = ::stm32f103c8;
const auto target_chip  = target_chips::stm32f103c8;
const auto target_board = target_boards::blue_pill;
   
void wait_ns( int_fast32_t n );
void wait_us( int_fast32_t n );
void wait_ms( int_fast32_t n );

void wait_ns_busy( int_fast32_t n );
void wait_us_busy( int_fast32_t n );
void wait_ms_busy( int_fast32_t n );

#define HWLIB_USE_HW_UART 
#ifdef HWLIB_USE_HW_UART

void HWLIB_WEAK uart_putc( char c ){
   target::uart_putc( c );
}

bool HWLIB_WEAK uart_char_available(){
   return target::uart_char_available();
}

char HWLIB_WEAK uart_getc( ){
   return target::uart_getc();
}

#else

void HWLIB_WEAK uart_putc( char c ){
   static target::pin_out pin( 0, 9 );
   uart_putc_bit_banged_pin( c, pin );
}

bool HWLIB_WEAK uart_char_available(){
   static target::pin_in pin( 0, 8 );
   return ! pin.read();
}

char HWLIB_WEAK uart_getc( ){
   static target::pin_in pin( 0, 8 );
   return uart_getc_bit_banged_pin( pin );
}

#endif
#ifdef _HWLIB_ONCE

uint64_t now_ticks(){
   return target::now_ticks();
}   

uint64_t ticks_per_us(){
   return target::ticks_per_us();
}   

uint64_t now_us(){
   return now_ticks() / ticks_per_us();
}


// Busy waits
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



#endif

}; //namespace hwlib   

#endif // #ifdef HWLIB_STM32F103C8_H
