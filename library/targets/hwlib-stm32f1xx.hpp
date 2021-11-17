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

#ifndef HWLIB_STM32F1xx_H
#define HWLIB_STM32F1xx_H

#include HWLIB_INCLUDE(../hwlib-all.hpp)

// the STM header files use 'register' in the pre-C++17 sense
#define register
#include "stm32f103xb.h"
#undef register

/// \brief
/// hwlib HAL for the stm32f1xx chips
/// 
/// This namespace contains the hwlib implementation of the pins, timing
/// and (software) UART output.
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
///
namespace stm32f1xx {

// the 
//   - enum class pins
//   - struct pin_info_type
//   - pin_info array 
// must have been declared before this file is included

/// \cond INTERNAL 
    GPIO_TypeDef &__attribute__((weak)) port_registers(uint32_t port) {

        // a bit of a cludge to put this here:
        // enable the clock to all GPIO ports
        RCC->APB2ENR |=
                RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN |
                RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPDEN;

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

    class pin_base {
    public:
        volatile GPIO_TypeDef &port;
        volatile uint32_t &config_word;
        uint32_t pin;
        uint32_t config_offset;
        uint32_t mask;

        void config(uint32_t conf) {
            config_word &= ~(0xF << config_offset);
            config_word |= conf << config_offset;
        }

        pin_base( uint32_t port_number, uint32_t pin_number, uint32_t conf ):
                port{ port_registers( port_number ) },
                config_word{ ( pin_number < 8 ) ? port.CRL : port.CRH },
                pin{ pin_number },
                config_offset{ 4 * (pin_number % 8) },
                mask{ 0x1U << pin_number } 
        {
            config( conf );
            
            // a15 = JTDI pin
            if(( port_number == 0 ) && ( pin_number == 15 )){
               RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
               AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_1;
            }
            
            // b4 = NJTRST
            if(( port_number == 1 ) && ( pin_number == 4 )){
               RCC->APB2ENR = RCC->APB2ENR | 0b01; // Enable AFIO clock
               AFIO->MAPR = ( AFIO->MAPR & ( ~ ( 0b111 <<24 )))  | ( 0b001 << 24 ); // JTA+SW-DP, but without NJRST
            }   
        }

        bool base_read() {
            return ((port.IDR & mask) != 0);
        }

        void base_write(bool v) {
            port.BSRR |= (v ? mask : (mask << 16));
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
        pin_in(uint32_t port_number, uint32_t pin_number) :
                pin_base{port_number, pin_number, 0x08} {}

        /// stm32f103c8 pin_in constructor
        ///
        /// Construct an stm32f103c8 input pin
        /// from its blue-pill pin name.
        ///
        /// This constructor sets the pin direction to input.
        /// By default, the internal weak pull-up is enabled.
        pin_in(pins name) :
                pin_in{
                        pin_info(name).port,
                        pin_info(name).pin
                } {}

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
        pin_out(uint32_t port_number, uint32_t pin_number) :
                pin_base{port_number, pin_number, 0x03} {}

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
        pin_out(pins name) :
                pin_out{
                        pin_info(name).port,
                        pin_info(name).pin
                } {}

        void write(bool v) override {
            base_write(v);
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
        pin_in_out(uint32_t port_number, uint32_t pin_number) :
                pin_base{port_number, pin_number, 0x08} {}

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
        pin_in_out(pins name) :
                pin_in_out{
                        pin_info(name).port,
                        pin_info(name).pin
                } {}

        void direction_set_input() override {
            config(0x08);
        }

        bool read() override {
            return base_read();
        }

        void direction_set_output() override {
            config(0x03);
        }

        void write(bool v) override {
            base_write(v);
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
        a6_36kHz() {
            RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;  // Enable GPIO port a
            RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;  // Enable Timer 3

            // this resets the other pins to theirv default!!!
            GPIOA->CRL = GPIO_CRL_MODE6 | GPIO_CRL_CNF6_1; // Set Pin A6 to alternate function Push-Pull

            TIM3->ARR = 221; // Auto reload value
            TIM3->PSC = 0; // Capture Compare preload, for duty cycle
            TIM3->CCR1 = 111;

            TIM3->CCMR1 = TIM_CCMR1_OC1M | TIM_CCMR1_OC1PE;
            TIM3->EGR |= TIM_EGR_UG; // Trigger update for Timer 3 (to preload)

            write(0);

            TIM3->CR1 |= TIM_CR1_ARPE; // Enable auto-  reload preload on Timer 3
            TIM3->CR1 |= TIM_CR1_CEN; // Enable Timer 3

        }

        /// enable or disable the 36 kHz output
        //
        /// Calling write( 1 ) enables the 36 kHz output, calling write( 0 )
        /// disables the output and makes the output low.
        void write(bool b) override {
            if (b) {
                TIM3->CCER |= TIM_CCER_CC1E;
            } else {
                TIM3->CCER &= ~TIM_CCER_CC1E;
            }
        }

        void flush() override {};

    }; // class a6_36kHz

    class spi_bus_hardware : public hwlib::spi_bus {
    private:


        void write_and_read(
                const size_t n,
                const uint8_t data_out[],
                uint8_t data_in[]
        ) override {
            for( uint_fast8_t i = 0; i < n; i++ ) {
                if (data_out != nullptr) {
                    SPI1->DR = (uint32_t)data_out[i]; //Write a byte to SPI hardware
                    while (!(SPI1->SR & SPI_SR_TXE)) { // Wait for byte to be processed by SPI hardware
                        hwlib::wait_ns_busy(1);
                    }
                }

                if (data_in != nullptr) {
                    while (! (SPI1->SR & SPI_SR_RXNE) ) { //Wait for byte to be received
                        hwlib::wait_ns_busy(1);
                    }
                    *data_in = SPI1->DR;
                    data_in++;
                }
            }
        }

    public:

        /// construct a hardware spi bus for the stm32f1xx
        ///
        /// This constructor creates a hardware spi bus
        /// on the default spi1 pins.
        ///
        ///
        /// When the SPI bus is used for either only writing or only reading,
        /// the unused pin argument can be specified as pin_out_dummy or
        /// pin_in_dummy.
        ///
        ///
        /// Default pins are:
        /// SCK:    A5
        /// MOSI:   A7
        /// NSS:    A4
        /// MISO:   A6
        spi_bus_hardware(

        ){
            // Setup all the ports needed by the SPI bus
            RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; //enable clock signal to spi
            RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; //enable clock signal to peripheralport A (this is were spi ports reside)

            GPIOA->CRL &= ~(GPIO_CRL_CNF5 | GPIO_CRL_MODE5);//sck
            GPIOA->CRL &= ~(GPIO_CRL_CNF7 | GPIO_CRL_MODE7);//mosi
            GPIOA->CRL &= ~(GPIO_CRL_CNF4 | GPIO_CRL_MODE4);//nss
            GPIOA->CRL &= ~(GPIO_CRL_CNF6 | GPIO_CRL_MODE6);// miso


            GPIOA->CRL |= GPIO_CRL_MODE5_0 | GPIO_CRL_MODE5_1; //sck
            GPIOA->CRL |= GPIO_CRL_CNF5_1;

            GPIOA->CRL |= GPIO_CRL_MODE7_0 | GPIO_CRL_MODE7_1; //mosi
            GPIOA->CRL |= GPIO_CRL_CNF7_1;

            GPIOA->CRL |= GPIO_CRL_MODE4_0 | GPIO_CRL_MODE4_1; //nss
            GPIOA->CRL |= GPIO_CRL_CNF4_1;

            GPIOA->CRL |= GPIO_CRL_CNF6_0; // miso







            SPI1->CR1 |= SPI_CR1_CPOL; //Invert clock polarity

            SPI1->CR2 |= SPI_CR2_SSOE; //Slave select will output
            SPI1->CR1 |= SPI_CR1_MSTR | SPI_CR1_SPE; //Make us the master and enable spi
        }

    };

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
        pin_oc(uint32_t port_number, uint32_t pin_number) :
                pin_base{port_number, pin_number, 0x07} {}

        /// stm32f103c8 pin_oc constructor
        ///
        /// Construct an stm32f103c8 open-collector pin
        /// from its blue-pill pin name.
        ///
        /// This constructor doesn't set the pin value
        /// to high or low, the set function must
        /// be called to do so.
        pin_oc(pins name) :
                pin_oc{
                        pin_info(name).port,
                        pin_info(name).pin
                } {}

        bool read() override {
            return base_read();
        }

        void write(bool v) override {
            base_write(v);
        }

        void flush() override {}

        void refresh() override {}

    };

/// the number of ticks per us
    uint_fast64_t HWLIB_WEAK ticks_per_us() {
        return 64; //72;
    }

/// returns the number of ticks since some fixed starting point
    uint_fast64_t HWLIB_WEAK now_ticks() {

        static bool init_done = false;
        if (!init_done) {

            // switch to the 72 MHz crystal/PLL clock, from stm32x.cpp,
            // some values taken from
            // https://github.com/rogerclarkmelbourne/STM32duino-bootloader

            // Flash 2 wait state
            FLASH->ACR &= (uint32_t) ((uint32_t) ~FLASH_ACR_LATENCY);
            FLASH->ACR |= (uint32_t) FLASH_ACR_LATENCY_2;

            // Enable Prefetch Buffer
            FLASH->ACR |= FLASH_ACR_PRFTBE;

            // enable HSE and wait for it
            RCC->CR |= RCC_CR_HSEON;
            while ((RCC->CR & RCC_CR_HSERDY) == 0) {}


            //  PLL configuration: PLLCLK = HSE * 9 = 72 MHz
            RCC->CFGR &= (uint32_t) ((uint32_t) ~(
                    RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
            RCC->CFGR |= (uint32_t) (RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL4);

            // Enable PLL and wait for it
            RCC->CR |= RCC_CR_PLLON;
            while ((RCC->CR & RCC_CR_PLLRDY) == 0) {}

            // HCLK = SYSCLK
            RCC->CFGR |= (uint32_t) RCC_CFGR_HPRE_DIV1;

            // PCLK2 = HCLK
            RCC->CFGR |= (uint32_t) RCC_CFGR_PPRE2_DIV1;

            // PCLK1 = HCLK / 2
            RCC->CFGR |= (uint32_t) RCC_CFGR_PPRE1_DIV2;

            // Select PLL as system clock source
            RCC->CFGR &= (uint32_t) ((uint32_t) ~(RCC_CFGR_SW));
            RCC->CFGR |= (uint32_t) RCC_CFGR_SW_PLL;

            // Wait till PLL is used as system clock source
            while ((RCC->CFGR & (uint32_t) RCC_CFGR_SWS) != (uint32_t) 0x08) {}

            // start the systick timer
            SysTick->CTRL = 0;         // stop the timer
            SysTick->LOAD = 0xFFFFFF;  // use its as a 24-bit timer
            SysTick->VAL = 0;         // clear the timer
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

    // If hwlib gets to cpp20 minimum make this consteval.
    constexpr uint32_t calculateBoutRate(long long  bout) {
        long long  fck = 64000000; // PCLK2 is getting 64 MHz
        fck *= 100; //doing fck x100 so we don't get floats.
        long long  usartdiv = (fck/bout)/16;
        unsigned int mantissa = std::round(usartdiv/100);
        unsigned int devider = std::round(((usartdiv-(mantissa*100))*16)/100);
        uint32_t baudrateReg = mantissa<<4u | devider;
        return baudrateReg;
    }

    void uart_init() {
        static bool init_done = false;
        if (init_done) {
            return;
        }
        init_done = true;


        RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;      // enable GPIOA clock
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN;    // enable USART1 clock

        GPIOA->CRH &= ~(GPIO_CRH_CNF9 | GPIO_CRH_MODE9);   // reset PA9
        GPIOA->CRH &= ~(GPIO_CRH_CNF10 | GPIO_CRH_MODE10);  // reset PA10

        GPIOA->CRH |= GPIO_CRH_MODE9_1 | GPIO_CRH_MODE9_0;  // 0b11 50MHz output
        GPIOA->CRH |= GPIO_CRH_CNF9_1;    // PA9: output @ 50MHz - Alt-function Push-pull
        GPIOA->CRH |= GPIO_CRH_CNF10_0;   // PA10 RX - Mode = 0b00 (input) - CNF = 0b01 (input floating)
        USART1->BRR = calculateBoutRate(HWLIB_BAUDRATE);
        // configure USART1 registers
        USART1->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;

    }


    bool uart_char_available() {
        uart_init();
        return (USART1->SR & USART_SR_RXNE_Msk);
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
        while (!(USART1->SR & USART_SR_TXE_Msk)) {
            hwlib::background::do_background_work();
        }
        USART1->DR = c;
    }


#endif

}; // namespace stm32f1xx

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
        stm32f1xx::uart_putc(c);
    }

    bool HWLIB_WEAK uart_char_available() {
        return stm32f1xx::uart_char_available();
    }

    char HWLIB_WEAK uart_getc() {
        return stm32f1xx::uart_getc();
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

    uint64_t now_ticks() {
        return stm32f1xx::now_ticks();
    }

    uint64_t ticks_per_us() {
        return stm32f1xx::ticks_per_us();
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

#endif // #ifdef HWLIB_STM32F1xx_H
