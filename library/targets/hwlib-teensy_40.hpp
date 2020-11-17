///@file
// ==========================================================================
//
// File      : hwlib-teensy_40.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017-2019
// Author    : Oscar Kromhout
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// this file contains Doxygen lines
#include HWLIB_INCLUDE(../hwlib-all.hpp)
#include "hwlib-mimxrt1062.hpp"

#ifndef TEENSY_40
#define TEENSY_40
namespace teensy_40
{
    /**
     * @brief Function that return the number of ticks per microsecond within the cpu. Ticks are equal to Mhz
     * 
     * @return uint64_t The ticks per microsecond
     */
    uint64_t ticks_per_us();

    uint64_t now_us();

    /**
     * @brief Enumerator with the pins.
     * @details Each entry corresponds to a number that maps to the index number from the core_pin_struct_array
     * 
     */
    enum class pins : uint8_t
    {
        d0 = 0,
        d1,
        d2,
        d3,
        d4,
        d5,
        d6,
        d7,
        d8,
        d9,
        d10,
        d11,
        d12,
        d13,
        d14,
        d15,
        d16,
        d17,
        d18,
        d19,
        d20,
        d21,
        d22,
        d23,
        a0 = 14,
        a1,
        a2,
        a3,
        a4,
        a5,
        a6,
        a7,
        a8,
        a9,
        rx1 = 0,
        tx1,
        rx2 = 7,
        tx2,
        tx3 = 14,
        rx3,
        rx4,
        tx4,
        tx5 = 20,
        rx5
    };

    /**
     * @brief Enumerator that holds the numbers that map the analog pins to the right index in the core_pin_struct_array
     * 
     */
    enum class ad_pins : uint8_t
    {
        a0 = 14,
        a1,
        a2,
        a3,
        a4,
        a5,
        a6,
        a7,
        a8,
        a9
    };

    class pin_out : public hwlib::pin_out
    {
    private:
        const mimxrt1062::core_pin &myPin;
        const uint32_t configMask = 0b00001000010110000; // config mask for setting the pin_in pull up and such. starting from p. 559, setting pull down in this case

    public:
        pin_out(pins pin_number) : myPin(mimxrt1062::core_pin_struct_array[(int)pin_number])
        {
            mimxrt1062::writeIOMUXMUXCTL(myPin.IOMUXC_MUX_control_register_array_index, 0b0101);
            mimxrt1062::writeIOMUXPADCTL(myPin.IOMUXC_PAD_control_register_array_index, configMask);
            reinterpret_cast<GPIO_Type *>(myPin.GPIO_port_base_adress)->GDIR |= 1 << myPin.GPIO_port_bit_number;
        }

        void write(bool x)
        {
            if (x)
            {
                reinterpret_cast<GPIO_Type *>(myPin.GPIO_port_base_adress)->DR |= (1 << myPin.GPIO_port_bit_number);
            }
            else
            {
                reinterpret_cast<GPIO_Type *>(myPin.GPIO_port_base_adress)->DR_CLEAR |= (1 << myPin.GPIO_port_bit_number);
            }
        }

        void flush()
        {}
        /**
         * @brief Function to Toggle the GPIO on and off
         * 
         */
        void toggle()
        {
            reinterpret_cast<GPIO_Type *>(myPin.GPIO_port_base_adress)->DR_TOGGLE |= (1 << myPin.GPIO_port_bit_number);
        }
    };

    class pin_in : public hwlib::pin_in
    {
    private:
        const mimxrt1062::core_pin &myPin;
        uint32_t configMask = 0b10011000010111000; // config mask for setting the pin_in pull up and such. starting from p. 559, setting pull down in this case
    public:
        pin_in(pins pin_number) : myPin(mimxrt1062::core_pin_struct_array[(int)pin_number])
        {
            mimxrt1062::writeIOMUXMUXCTL(myPin.IOMUXC_MUX_control_register_array_index, 0b0101);
            mimxrt1062::writeIOMUXPADCTL(myPin.IOMUXC_PAD_control_register_array_index, configMask);
            reinterpret_cast<GPIO_Type *>(myPin.GPIO_port_base_adress)->GDIR &= (0 << myPin.GPIO_port_base_adress);
        }

        bool read()
        {
            return reinterpret_cast<uint32_t>(reinterpret_cast<GPIO_Type *>(myPin.GPIO_port_base_adress)->DR) & (1 << myPin.GPIO_port_bit_number);
        }

        void refresh()
        {
            reinterpret_cast<GPIO_Type *>(myPin.GPIO_port_base_adress)->DR_CLEAR |= (1 << myPin.GPIO_port_bit_number);
        }
    };

    class pin_adc : public hwlib::adc
    {
        // p. 3328 consumers guide
        private:
        const mimxrt1062::core_pin & myPin;
        uint32_t configMask = 0b00000000010110000; // config mask, everything default, except PKE (bit 12) which turns off the pull/keeper
        public:
        pin_adc(pins pin_number) : hwlib::adc(12), myPin(mimxrt1062::core_pin_struct_array[(int)pin_number])
        {   
            if (myPin.ad_channel == 255) // what to do if pin_number is not an adc pin
            {
                return;
            }
            mimxrt1062::writeIOMUXPADCTL(myPin.IOMUXC_PAD_control_register_array_index,configMask); // disable keeper, NOTE on p.3331
            mimxrt1062::writeIOMUXMUXCTL(myPin.IOMUXC_MUX_control_register_array_index, 0b0101); // enable the gpio that adc uses
            // enable the adc clocks to adc1.
            CCM->CCGR1 &= ~(0b11 <<16); // adc1
            CCM->CCGR1 |= (0b11 << 16); // adc1
            // CCM->CCGR1 &= ~(0b11 <<8); // adc2
            // CCM->CCGR1 |= (0b11 << 8); // adc2

            ADC1->GC &= ~(0b11111111); // set to: no cal, single conversion, no hardware average, no compare function, no compare function greater than, no compare function range, no DMA, Asynchronous clock enabled for output.
            ADC1->GC |=  (0b00000001);
            // ADC2->GC &= ~(0b11111111); // set to: no cal, single conversion, no hardware average, no compare function, no compare function greater than, no compare function range, no DMA, Asynchronous clock enabled for output.
            // ADC2->GC |=  (0b00000001);
            
            uint32_t config = 0;
            config |= (0b10<<2); // adc conversion to 12 bit resolution
            config |= (0b1<<4); // long sampling on (ADLSMP bit)
            config |= (0b11<<8); // sample period to 25 clocks (highest, ADSTS bits)
            config |= (0b11); // Asynchronous clock as input
            config |= (0b01 << 5); // divide input clock by 2
            ADC1->CFG &= ~(0b1111111111111111); // adc1
            ADC1->CFG |= config;
            // ADC2->CFG &= ~(0b1111111111111111); // adc2
            // ADC2->CFG |= config;

            // calibrate using the on chip calibration function
            ADC1->GC |= (0b1 << 7);
            while((ADC1->GC & (0b1 << 7)) != 0){} // check if the CAL bit is still high, if not, calibration is done
            // ADC2->GC |= (0b1 << 7);
            // while((ADC2->GC & (0b1 << 7)) != 0){} // check if the CAL bit is still high, if not, calibration is done
        };
        
        adc_value_type read()
        {
            if (myPin.ad_channel == 0xFFFFFFFF)
            {
                return 0xFFFFFFFF;
            }
            ADC1->HC[0] = myPin.ad_channel;
            while(ADC1->HS & 0b1){} //wait till the conversion complete (ADACT p. 3368)
            return (adc_value_type)ADC1->R[0]; //read from the ADC1 -> R register
        }

        void refresh()
        {
            return;
        }

    };

    /// \cond INTERNAL
    void uart_init();
    /// \endcond 

    bool uart_char_available();
    char uart_getc();
    void uart_putc( char c );

    #ifdef _HWLIB_ONCE

    void uart_init()
    {
        static bool init_done = false;
        if( init_done ){
        return;
        }
        init_done = true;
        //======================================================
        //getting the pin info for uart config
        const mimxrt1062::core_pin & rx = mimxrt1062::core_pin_struct_array[0]; // teensy 4.0 rx1
        const mimxrt1062::core_pin & tx = mimxrt1062::core_pin_struct_array[1]; // teensy 4.0 tx1
        //======================================================
        // this baudrate value was tested and works well, baudrate can only be between 9600 and 100.000. 
        // 115200 gives to high offset because I was not able to find out which clock UART runs on (should be 480 Mhz, but this didn't work in the formula, see TODO below)
        uint32_t baudrate = 38400;
        uint8_t muxCtlConfigmask = 0b010; // uart config number for the mux ctl register
        //======================================================
        // setting all the CCM to UART clock gates on
        CCM->CCGR3 &= ~(0b11 << 6);
        CCM->CCGR3 |= (0b11 << 6);
        // these are only needed when using other pins than rx and tx 0. Default is rx and tx zero so these are not needed
        // CCM->CCGR1 &= ~(0b11 << 24);
        // CCM->CCGR1 |= (0b11 << 24);
        // CCM->CCGR0 &= ~(0b11 << 28);
        // CCM->CCGR0 |= (0b11 << 28);
        // CCM->CCGR0 &= ~(0b11 << 12);
        // CCM->CCGR0 |= (0b11 << 12);
        // CCM->CCGR6 &= ~(0b11 << 14);
        // CCM->CCGR6 |= (0b11 << 14);
        // CCM->CCGR5 &= ~(0b11 << 24);
        // CCM->CCGR5 |= (0b11 << 24);
        // CCM->CCGR5 &= ~(0b11 << 26);
        // CCM->CCGR5 |= (0b11 << 26);
        //======================================================
        // setting the iomux to uart
        mimxrt1062::writeIOMUXMUXCTL(rx.IOMUXC_MUX_control_register_array_index,muxCtlConfigmask);
        mimxrt1062::writeIOMUXMUXCTL(tx.IOMUXC_MUX_control_register_array_index,muxCtlConfigmask);
        //======================================================
        // setting everything else from UART, note that only consecutive rx and tx pins can be used. So rx1 and tx1 and rx2 and tx2 not rx1 and tx3.
        reinterpret_cast<LPUART_Type *>(rx.serial_base_adress) -> CTRL &= ~(0b1 << 18); // disable rx
        reinterpret_cast<LPUART_Type *>(tx.serial_base_adress) -> CTRL &= ~(0b1 << 19); // disable tx
        // baudrate = (PLL3 clock*1000000/6) / BAUD[0:12] * BAUD[24:28]+1
        // Wasn't able to find out the right clockspeed for this formula (should be 480 according to reference manual?) found out that a SBR of 130 = 9600 Baud, so deduced to this formula. magic. Seems to have something to do with the PLL bypass, but can't figure it out.
        // TODO: Find the right settings to crank up the 20'000'000 number to 480'000'000 (or whatever else). So you know for sure how many Mhz is send to the UART clock, so the formula works better and higher baudrates can be found. (this 20 Mhz is backwards calculated because i knew a SBR value of 130 gave me 9600 baud)
        uint32_t SBR = 20'000'000/(16*baudrate);

        reinterpret_cast<LPUART_Type *>(tx.serial_base_adress) -> BAUD &= ~(0b11111 << 23); // clear OSR
        reinterpret_cast<LPUART_Type *>(tx.serial_base_adress) -> BAUD |= 0b01111 << 23; // set OSR to 15
        reinterpret_cast<LPUART_Type *>(rx.serial_base_adress) -> BAUD &= ~(0b1111111111111); // clear the SBR within BAUD register
        reinterpret_cast<LPUART_Type *>(rx.serial_base_adress) -> BAUD |= SBR; // set it to the right baudrate (130 (129.xxx) = 9600)
        
        reinterpret_cast<LPUART_Type *>(rx.serial_base_adress) -> CTRL |= (0b1 << 18); // set the uart rx pin to recieve enable
        reinterpret_cast<LPUART_Type *>(tx.serial_base_adress) -> CTRL |= (0b1 << 19); // set tx pin to transmit enable
    
    }

    inline void dont_optimize()
    {
        volatile int i = 0;
        if (i < 10)
        {
            i++;
        }
        else
        {
            i = 0;
        }
    }

    bool uart_char_available(){
    uart_init();
    const mimxrt1062::core_pin & rx = mimxrt1062::core_pin_struct_array[0]; // teensy 4.0 rx1	
    return ( reinterpret_cast<LPUART_Type*>(rx.serial_base_adress) -> STAT & (0b1 << 21)) != 0; // return if the STAT[RDRF] is full (0 is empty, 1 is full)
    }

    char uart_getc(){
    // uart_init() is not needed because uart_char_available does that
    while( ! uart_char_available() )
    { 
        dont_optimize();
        // TODO: hwlib::background::do_background_work();	
    }
    const mimxrt1062::core_pin & rx = mimxrt1062::core_pin_struct_array[0]; // teensy 4.0 rx1	
    return reinterpret_cast<LPUART_Type *>(rx.serial_base_adress) -> DATA; 
    }

    void uart_putc( char c )
    {
        uart_init();	
        const mimxrt1062::core_pin & tx = mimxrt1062::core_pin_struct_array[1]; // teensy 4.0 tx1
        while((reinterpret_cast<LPUART_Type*>(tx.serial_base_adress) -> STAT & (0b1 << 22)) == 0)
        {
            dont_optimize();
        // TODO: hwlib::background::do_background_work();	
        }
        reinterpret_cast<LPUART_Type *>(tx.serial_base_adress) -> DATA |= c;
    }

    #endif // _HWLIB_ONCE
}; //namespace teensy_40
#endif // TEENSY_40

/**
 * @brief This namespace lets the hwlib::target point to hwlib::teensy_40
 * 
 */
namespace hwlib
{
namespace target = ::teensy_40;

void HWLIB_WEAK uart_putc( char c )
{
    teensy_40::uart_putc( c );
}

bool HWLIB_WEAK uart_char_available()
{
return teensy_40::uart_char_available();
}

char HWLIB_WEAK uart_getc( )
{
return teensy_40::uart_getc();
}

#ifdef _HWLIB_ONCE
    uint64_t now_ticks()
    {
        return mimxrt1062::now_ticks();
    }

    uint64_t ticks_per_us()
    {
        return mimxrt1062::ticks_per_us();
    }

    uint64_t now_us()
    {
        return now_ticks() / ticks_per_us();
    }

    // busy waits

    void wait_ns_busy(int_fast32_t n)
    {
        wait_us_busy((n + 999) / 1000);
    }

    void wait_us_busy(int_fast32_t n)
    {
        auto end = now_us() + n;
        while (now_us() < end)
        {
        }
    }

    void wait_ms_busy(int_fast32_t n)
    {
        while (n > 0)
        {
            wait_us_busy(1000);
            --n;
        }
    }

    // non-busy waits

    void HWLIB_WEAK wait_ns(int_fast32_t n)
    {
        wait_us((n + 999) / 1000);
    }

    void HWLIB_WEAK wait_us(int_fast32_t n)
    {
        auto end = now_us() + n;
        while (now_us() < end)
        {
            // background::do_background_work();
        }
    }

    void HWLIB_WEAK wait_ms(int_fast32_t n)
    {
        while (n > 0)
        {
            wait_us(1000);
            --n;
        }
    }
#endif // _HWLIB_ONCE
};     // namespace hwlib
