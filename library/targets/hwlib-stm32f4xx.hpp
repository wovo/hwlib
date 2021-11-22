// ==========================================================================
//
// File      : hwlib-stm32f4xx.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2021
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// todo:
// - ADC wait
// - also change f1
//
// ==========================================================================

// this file contains Doxygen lines
/// @file

#ifndef HWLIB_STM32F4xx_H
#define HWLIB_STM32F4xx_H

#include HWLIB_INCLUDE(../hwlib-all.hpp)

// the STM header files use 'register' in the pre-C++17 sense
#define register
#include "stm32f401xc.h"
#undef register

/// \brief
/// hwlib HAL for the STM32F4xx chips
/// 
/// This namespace contains the hwlib implementation of the pins, timing
/// and UART.
///
/// Initially, the chip runs from its HSI internal RC oscillator at 16 MHz. 
/// The first wait call configures the chip to run at 84 MHz, 
/// assuming a 16 MHz crystal.
///
/// The chip runs at 3.3 Volt and that is the level on its IO pins.
///
/// References:
///    - <A HREF="http://www.st.com/content/ccc/resource/technical/document/reference_manual/59/b9/ba/7f/11/af/43/d5/CD00171190.pdf/files/CD00171190.pdf/jcr:content/translations/en.CD00171190.pdf">
///       RM0008 STM32F4xxx reference manual</A> (pdf)
///
namespace stm32f4xx {

// the 
//   - enum class pins
//   - struct pin_info_type
//   - pin_info array 
// must have been declared before this file is included

/// \cond INTERNAL 
    GPIO_TypeDef &__attribute__((weak)) port_registers(uint32_t port) {

      // a bit of a cludge to put this here:
      // enable the clock to all GPIO ports
      RCC->AHB1ENR |= 
         RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | 
         RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN; 

        switch (port) {
            case 0  :
                return *GPIOA;
            case 1  :
                return *GPIOB;
            case 2  :
                return *GPIOC;
            case 3  :
                return *GPIOD;
            default :
                break;
        }

        // doesn't return
        HWLIB_PANIC_WITH_LOCATION;
    }
    
   void __attribute__((weak)) set_bit_field( 
      volatile uint32_t & reg, 
      int start, 
      int bits, 
      uint32_t value 
   ){
      reg &= ~( (( 1 << ( bits + 1 ) ) - 1 ) << start );
      reg |= value << start;
   }    

   class pin_base {
   public:
      volatile GPIO_TypeDef &port;
      uint32_t pin;
      uint32_t mask;

      pin_base( uint32_t port_number, uint32_t pin_number, uint32_t conf ):
         port{ port_registers( port_number ) },
         pin{ pin_number },
         mask{ 0x1U << pin_number } 
      {
         config( conf );
         port.OTYPER &= ~ mask;
      }
      
      void config( uint32_t conf ) {
         port.MODER &= ~( 0b11 << ( pin * 2 ) );
         port.MODER |= conf << ( pin * 2 );
      }

      bool base_read() {
         return ( port.IDR & mask ) != 0;
      }

      void base_write( bool v ) {
         if( v ){
            port.BSRRL = mask;
         } else {
            port.BSRRH = mask;
         }
      }

    };   

/// \endcond 

   /// pin_in implementation for an stm32f4xx
   class pin_in : public hwlib::pin_in, private pin_base {
   public:

      /// stm32f4xx pin_in constructor
      ///
      /// Construct an stm32f4xx input pin
      /// from its port and pin numbers.
      ///
      /// This constructor sets the pin direction to input.
      /// By default, the internal weak pull-up is enabled.
      pin_in( uint32_t port_number, uint32_t pin_number ) :
         pin_base{ port_number, pin_number, 0x00 } {}

      /// stm32f4xx pin_in constructor
      ///
      /// Construct an stm32f4xx input pin
      /// from its blue-pill pin name.
      ///
      /// This constructor sets the pin direction to input.
      /// By default, the internal weak pull-up is enabled.
      pin_in( pins name ) :
         pin_in{
            pin_info( name ).port,
            pin_info( name ).pin
         } {}

      bool read() override {
         return base_read();
      }

      void refresh() override {}
        
      void pullup_enable(){
         port.PUPDR &= ~( 0b11 << ( pin * 2 ) );
         port.PUPDR |= 0b01 << ( pin * 2 );           
      }

   };

    /// pin_out implementation for an stm32f4xx
    class pin_out : public hwlib::pin_out, private pin_base {
    public:

       /// stm32f4xx pin_out constructor
       ///
       /// Construct an stm32f4xx output pin
       /// from its port and pin numbers.
       ///
       /// This constructor sets the pin direction to output.
       ///
       /// This constructor doesn't set the pin value
       /// to high or low, the set function must
       /// be called to do so.
       pin_out(uint32_t port_number, uint32_t pin_number) :
          pin_base{ port_number, pin_number, 0x01 } {}

       /// stm32f4xx pin_out constructor
       ///
       /// Construct an stm32f4xx output pin
       /// from its blue-pill pin name.
       ///
       /// This constructor sets the pin direction to output.
       ///
       /// This constructor doesn't set the pin value
       /// to high or low, the set function must
       /// be called to do so.
       pin_out( pins name ) :
          pin_out{
             pin_info( name ).port,
             pin_info( name ).pin
          } {}

       void write( bool v ) override {
          base_write( v );
       }

       void flush() override {}

   };

   /// pin_in_out implementation for an stm32f4xx
   class pin_in_out : public hwlib::pin_in_out, private pin_base {
   public:

      /// stm32f4xx pin_out constructor
      ///
      /// Construct an stm32f4xx input/output pin
      /// from its port and pin numbers.
      ///
      /// This constructor doesn't set the pin direction
      /// to input or output, a direction_set function must
      /// be called to do so.
      ///
      /// This constructor doesn't set the pin value
      /// to high or low, the set function must
      /// be called to do so.
      pin_in_out( uint32_t port_number, uint32_t pin_number ) :
         pin_base{ port_number, pin_number, 0x00 } {}

      /// stm32f4xx pin_out constructor
      ///
      /// Construct an stm32f4xx input/output pin
      /// from its blue-pill pin name.
      ///
      /// This constructor doesn't set the pin direction
      /// to input or output, a direction_set function must
      /// be called to do so.
      ///
      /// This constructor doesn't set the pin value
      /// to high or low, the set function must
      /// be called to do so.
      pin_in_out( pins name ) :
         pin_in_out {
            pin_info( name ).port,
            pin_info( name ).pin
         } {}

      void direction_set_input() override {
         config( 0x00 );
      }

      bool read() override {
         return base_read();
      }

      void direction_set_output() override {
         config( 0x01 );
      }

      void write( bool v ) override {
         base_write( v );
      }

      void flush() override {}

      void refresh() override {}

      void direction_flush() override {}

   };

   /// pin_oc implementation for an stm32f4xx
   class pin_oc : public hwlib::pin_oc, private pin_base {
   public:

      /// stm32f4xx pin_oc constructor
      ///
      /// Construct an stm32f4xx open-collector pin
      /// from its port and pin numbers.
      ///
      /// This constructor doesn't set the pin value
      /// to high or low, the set function must
      /// be called to do so.
      pin_oc(uint32_t port_number, uint32_t pin_number) :
         pin_base{port_number, pin_number, 0x07} 
      {
         // a 1 bit selects OD
         port.OTYPER |= mask;
      }

      /// stm32f4xx pin_oc constructor
      ///
      /// Construct an stm32f4xx open-collector pin
      /// from its blue-pill pin name.
      ///
      /// This constructor doesn't set the pin value
      /// to high or low, the set function must
      /// be called to do so.
      pin_oc(pins name) :
         pin_oc {
            pin_info(name).port,
            pin_info(name).pin
      }{}

      bool read() override {
         return base_read();
      }

      void write(bool v) override {
         base_write(v);
      }

      void flush() override {}

      void refresh() override {}

   };
    
   /// pin_adc implementation 
   class pin_adc : public hwlib::adc {
   private:
      uint32_t channel;
   
   public:

      /// Constructor for a ATSAM3X8E AD channel number.
      ///
      /// This constructor initializes the pin to be an ADC input. 
      pin_adc( uint32_t channel ): 
         adc( 12 ),
         channel( channel )
      {
         constexpr uint32_t cyc = 0b111; // 480 cycles (maximum)
         constexpr uint32_t samps = 
            ( cyc < 0 ) | ( cyc << 3 ) | ( cyc << 6 ) | ( cyc < 9 ) | ( cyc << 12 ) |
            ( cyc << 15 ) | ( cyc << 18 ) | ( cyc << 21 ) | ( cyc << 24 );   
      
         RCC->AHB1ENR |= 
            RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | 
            RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN;       
         
         switch( channel ){
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
               set_bit_field( GPIOA->MODER,  2 * channel, 2, 0b11 );      
               set_bit_field( GPIOA->PUPDR,  2 * channel, 2, 0b00 );         
               break;
            case 8:
            case 9:
               set_bit_field( GPIOB->MODER,  2 * (channel - 8), 2, 0b11 );      
               set_bit_field( GPIOB->PUPDR,  2 * (channel - 8), 2, 0b00 );         
               break;
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
               set_bit_field( GPIOC->MODER,  2 * (channel - 10), 2, 0b11 );      
               set_bit_field( GPIOC->PUPDR,  2 * (channel - 10), 2, 0b00 );         
               break;    
         }    
      
         RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;            // Enable ADC clock
         set_bit_field( ADC1->CR1,  11, 1, 1 );         // discontinous mode enabled
         set_bit_field( ADC1->CR1,   8, 1, 0 );         // scan mode disabled
         set_bit_field( ADC1->CR1,  24, 2, 0 );         // 12bit resolution
         set_bit_field( ADC1->CR2,  11, 1, 0 );         // Right alignment
         set_bit_field( ADC1->CR2,   1, 1, 0 );         // Single conversion
         set_bit_field( ADC1->CR2,   0, 1, 1 );         // Enable ADC
         ADC1->SMPR1 = samps;                           // 'cyc' cycles for all channels
         ADC1->SMPR2 = samps | ( cyc << 27 ); 
         set_bit_field( ADC1->SQR1, 23, 4, 0 );         // 1 conversion in the regular sequence
         set_bit_field( ADC1->SQR3,  0, 5, channel );	  // select (only) our channel
         set_bit_field( ADC->CCR,   16, 2, 0b00 );      // /2 prescaler => 42 / 2 = 21 MHz
      }
      
      /// Constructor for a ATSAM3X8E AD channel pin.
      ///
      /// This constructor initializes the pin to be an ADC input. 
      pin_adc( ad_pins pin ): 
         pin_adc( static_cast< int >( pin ) )
      {}
   
      adc_value_type read() override {

         // start the conversion 
         set_bit_field( ADC1->CR2, 30, 1, 1 );
      
         // wait for the conversion to complete
         // should wait on some flag!!
         hwlib::wait_us( 2'000 );     
 
         // return the conversion result
         return ADC1->DR;
      }
   
      void refresh() override {}
   };    

   /// the number of ticks per us
   constexpr uint_fast64_t HWLIB_WEAK ticks_per_us() {
      return 84;
   }

   /// returns the number of ticks since some fixed starting point
   uint_fast64_t HWLIB_WEAK now_ticks() {

      static bool init_done = false;
      if (!init_done) {
        
         // FLASH settings for 84 MHz at > 2.7 V
         FLASH->ACR |= 
            FLASH_ACR_DCEN |     // enable data cache
            FLASH_ACR_ICEN |     // enable instruction cache
            FLASH_ACR_PRFTEN |   // enable prefetch
            2;                   // 2 wait states
           
         // AHB prescaler 1 (not divided), AHB = 84 MHz
         set_bit_field( RCC->CFGR,  4, 4, 0b0000 );
           
         // APBx prescaler APB1 DIV 2, APB2 DIV 1 (not divided)
         set_bit_field( RCC->CFGR,  10, 3, 0b100 ); // APB1 = 84 MHz
         set_bit_field( RCC->CFGR,  13, 3, 0b000 ); // APB2 = 42 MHz
           
         // enable the HSE (external 25 Mhz crystal) and wait for stable
         RCC->CR |= RCC_CR_HSEON;
         while( ( RCC->CR & RCC_CR_HSERDY ) == 0 ){}
           
         //set_bit_field( RCC->CFGR, 0, 2, 0b01 ); // switch to 25 MHz HSE
           
         // configure PLL for 25 Mhz HSE input, 84 and 48 MHz outputs
         set_bit_field( RCC->PLLCFGR,  0, 6,   25 ); // M = 25
         set_bit_field( RCC->PLLCFGR,  6, 9,  336 ); // N = 336
         set_bit_field( RCC->PLLCFGR, 16, 2, 0b01 ); // P = 4
         set_bit_field( RCC->PLLCFGR, 22, 1,  0b1 ); // source = HSE
         set_bit_field( RCC->PLLCFGR, 24, 4,    7 ); // Q = 7
           
         // enable PLL and wait for stable
         RCC->CR |= RCC_CR_PLLON;
         while( ( RCC->CR & RCC_CR_PLLRDY ) == 0 ){}
           
         // switch to the 84 MHz PLL CPU clock
         set_bit_field( RCC->CFGR, 0, 2, 0b10 ); // switch to 84 MHz PLL

         // start the systick timer
         SysTick->CTRL = 0;         // stop the timer
         SysTick->LOAD = 0xFFFFFF;  // use its as a 24-bit timer
         SysTick->VAL = 0;          // clear the timer
         SysTick->CTRL = 5;         // start the timer, 1:1

         init_done = true;
      }

      static unsigned int last_low = 0;
      static unsigned long long int high = 0;

      // the timer ticks down, but we want an up counter
      unsigned int low = 0xFFFFFF - (SysTick->VAL & 0xFFFFFF);
      if (low < last_low) {

         // the timer rolled over, so increment the high part
         high += 0x1ULL << 24;
      }
      last_low = low;

      // return the aggregated ticks value
      // the counter runs at 1 MHz
      return (low | high);

  }

/// \cond INTERNAL    
    void uart_init();
/// \endcond   

    bool uart_char_available();

    char uart_getc();

    void uart_putc(char c);

#ifdef _HWLIB_ONCE

    void uart_init() {
        static bool init_done = false;
        if (init_done) {
            return;
        }
        init_done = true;
        
        // UART1 uses Tx=PA9 Rx=PA10
      
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;   // enable GPIOA clock
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN;  // enable USART1 clock
      
        set_bit_field( GPIOA->MODER,   2 * 9, 2, 0b10 );  // PA9 alternate function
        set_bit_field( GPIOA->MODER,  2 * 10, 2, 0b10 );  // PA10 alternate function
      
        set_bit_field( GPIOA->AFR[ 1 ], 4 * (  9 - 8 ), 4, 7 ); // PA9 AF7 = UART1
        set_bit_field( GPIOA->AFR[ 1 ], 4 * ( 10 - 8 ), 4, 7 ); // PA10 AF7 = UART1
          
        USART1->BRR = ( 84'000'000LL << 4 ) / HWLIB_BAUDRATE;
        
        // enable Tx, enable Rx, no power down
        USART1->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
    }

    bool uart_char_available() {
        uart_init();
        return ( USART1->SR & USART_SR_RXNE ) != 0;
    }

    char uart_getc() {
        // uart_init() is not needed because uart_char_available does that
        while (!uart_char_available()) {
            hwlib::background::do_background_work();
        }
        return USART1->DR;
    }

    void uart_putc(char c) {
        uart_init();
        while (( USART1->SR & USART_SR_TXE ) == 0 ) {
//            hwlib::background::do_background_work();
        }
        USART1->DR = c;
    }


#endif

}; // namespace STM32F4xx

namespace hwlib {

    void wait_ns(int_fast32_t n);

    void wait_us(int_fast32_t n);

    void wait_ms(int_fast32_t n);

    void wait_ns_busy(int_fast32_t n);

    void wait_us_busy(int_fast32_t n);

    void wait_ms_busy(int_fast32_t n);

#define HWLIB_USE_HW_UART
#ifdef HWLIB_USE_HW_UART

    void HWLIB_WEAK uart_putc(char c) {
        stm32f4xx::uart_putc(c);
    }

    bool HWLIB_WEAK uart_char_available() {
        return stm32f4xx::uart_char_available();
    }

    char HWLIB_WEAK uart_getc() {
        return stm32f4xx::uart_getc();
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

    // monotonic clock

    uint64_t now_ticks() {
        return stm32f4xx::now_ticks();
    }

    uint64_t ticks_per_us() {
        return stm32f4xx::ticks_per_us();
    }

    uint64_t now_us() {
        return now_ticks() / ticks_per_us();
    }

    // Busy waits
    
    void wait_ns_busy(int_fast32_t n) {
        wait_us_busy((n + 999) / 1000);
    }

    void wait_us_busy(int_fast32_t n) {
        auto end = now_us() + n;
        while (now_us() < end) {}
    }

    void wait_ms_busy(int_fast32_t n) {
        while (n > 0) {
            wait_us_busy(1000);
            --n;
        }
    }

    void HWLIB_WEAK wait_ns(int_fast32_t n) {
        wait_us((n + 999) / 1000);
    }

    void HWLIB_WEAK wait_us(int_fast32_t n) {
        auto end = now_us() + n;
        while (now_us() < end) {
            background::do_background_work();
        }
    }

    void HWLIB_WEAK wait_ms(int_fast32_t n) {
        while (n > 0) {
            wait_us(1000);
            --n;
        }
    }

#endif

}; //namespace hwlib   

#endif // #ifdef HWLIB_STM32F4xx_H
