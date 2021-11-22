///@file
// ==========================================================================
//
// File      : hwlib-pi-pico.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2021
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

#ifndef H_PI_PICO
#define H_PI_PICO
namespace pi_pico
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

    /**
     * @brief This inline function waits exactly 32 nop instructions and is only used by the pin_oc type. Do not use.
     * @details When the chip switches between a gpio pin as in input or ouput, some time is needed to "let the pin adjust"
     * after trial and error, I deduced that 32 nops were exactly right. No info in the datasheet on this.
     * 
     */
    inline void wait_32_nops()
    {
         asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
         asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
         asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
         asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
         asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
         asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
         asm("nop");
        asm("nop");
    }

    class pin_out : public hwlib::pin_out
    {
    private:
        const mimxrt1062::core_pin &myCorePin;
        const uint32_t configMask = ((0b0 << 16) /*HYS*/| (0b00 << 14) /*PUS*/ | (0b0<<13) /*PUE*/ | (0b1 << 12) /*PKE*/ | (0b0 << 11) /*ODE*/ |  (0b10 << 6) /*SPEED*/ | (0b110 << 3) /*DSE*/ | 0b0 /*SRE*/ );
    public:
        pin_out(pins pin_number) : myCorePin(mimxrt1062::core_pin_struct_array[(int)pin_number])
        {
            mimxrt1062::writeIOMUXMUXCTL(myCorePin.IOMUXC_MUX_control_register_array_index, 0b0101);
            mimxrt1062::writeIOMUXPADCTL(myCorePin.IOMUXC_PAD_control_register_array_index, configMask);
            reinterpret_cast<GPIO_Type *>(myCorePin.GPIO_port_base_adress)->GDIR |= (1 << myCorePin.GPIO_port_bit_number);
        }

        void write(bool x) override
        {
            (x 
                ? reinterpret_cast<GPIO_Type *>(myCorePin.GPIO_port_base_adress)->DR_SET 
                : reinterpret_cast<GPIO_Type *>(myCorePin.GPIO_port_base_adress)->DR_CLEAR
            ) = (1 << myCorePin.GPIO_port_bit_number);
        }

        void flush() override
        {
        }
        /**
         * @brief Function to Toggle the GPIO on and off
         * 
         */
        void toggle()
        {
            reinterpret_cast<GPIO_Type *>(myCorePin.GPIO_port_base_adress)->DR_TOGGLE |= (1 << myCorePin.GPIO_port_bit_number);
        }
    };

    class pin_in : public hwlib::pin_in
    {
    // this class also has pull up and pull down enable functions as these are later added by WOVO to hwlib-examples. The pin is pull down by default
    private:
        const mimxrt1062::core_pin &myCorePin;
        const uint32_t configMask = ((0b1 << 16) /*HYS*/| (0b00 << 14) /*PUS*/ | (0b1<<13) /*PUE*/ | (0b1 << 12) /*PKE*/ | (0b0 << 11) /*ODE*/ |  (0b10 << 6) /*SPEED*/ | (0b111 << 3) /*DSE*/ | 0b0 /*SRE*/ );
    public:
        pin_in(pins pin_number) : myCorePin(mimxrt1062::core_pin_struct_array[(int)pin_number])
        {
            mimxrt1062::writeIOMUXMUXCTL(myCorePin.IOMUXC_MUX_control_register_array_index, 0b0101);
            mimxrt1062::writeIOMUXPADCTL(myCorePin.IOMUXC_PAD_control_register_array_index, configMask);
            reinterpret_cast<GPIO_Type *>(myCorePin.GPIO_port_base_adress)->GDIR &= ~(1 << myCorePin.GPIO_port_bit_number);
        }

        bool read() override
        {
            return (reinterpret_cast<uint32_t>(reinterpret_cast<GPIO_Type *>(myCorePin.GPIO_port_base_adress)->PSR) & (1 << myCorePin.GPIO_port_bit_number)) != 0;
        }

        void refresh() override
        {
            // does this even do something?
            reinterpret_cast<GPIO_Type *>(myCorePin.GPIO_port_base_adress)->DR_CLEAR |= (1 << myCorePin.GPIO_port_bit_number);
        }
        /**
         * @brief Function to enable the embedded 22k pull up resistor. The pin_in class is pulled down by default. 
         * 
         */
        void pullup_enable()
        {
            uint32_t pullupConfigMask = ((0b1 << 16) /*HYS*/| (0b11 << 14) /*PUS*/ | (0b1<<13) /*PUE*/ | (0b1 << 12) /*PKE*/ | (0b0 << 11) /*ODE*/ |  (0b10 << 6) /*SPEED*/ | (0b111 << 3) /*DSE*/ | 0b0 /*SRE*/ );
            mimxrt1062::writeIOMUXPADCTL(myCorePin.IOMUXC_PAD_control_register_array_index, pullupConfigMask);
            wait_32_nops();
        }

        /**
         * @brief Function to disable the 22k pull up resistor (after calling pullup_enable for example) and enable the embedded 100k pull down resistor, which is the standard setting by default.
         * 
         */
        void pulldown_enable()
        {
            mimxrt1062::writeIOMUXPADCTL(myCorePin.IOMUXC_PAD_control_register_array_index, configMask);
            wait_32_nops();
        }
    };

    class pin_adc : public hwlib::adc
    {
        // p. 3328 consumers guide
        private:
        const mimxrt1062::core_pin & myCorePin;
        const uint32_t configMask = ((0b0 << 16) /*HYS*/| (0b00 << 14) /*PUS*/ | (0b0<<13) /*PUE*/ | (0b0 << 12) /*PKE*/ | (0b0 << 11) /*ODE*/ |  (0b10 << 6) /*SPEED*/ | (0b110 << 3) /*DSE*/ | 0b0 /*SRE*/ );
        public:
        pin_adc(pins pin_number) : hwlib::adc(12), myCorePin(mimxrt1062::core_pin_struct_array[(int)pin_number])
        {   
            if (myCorePin.ad_channel == 0XFFFFFFFF) // what to do if pin_number is not an adc pin
            {
                return;
            }
            mimxrt1062::writeIOMUXPADCTL(myCorePin.IOMUXC_PAD_control_register_array_index,configMask); // disable keeper, NOTE on p.3331
            mimxrt1062::writeIOMUXMUXCTL(myCorePin.IOMUXC_MUX_control_register_array_index, 0b0101); // enable the gpio that adc uses
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
        
        adc_value_type read() override
        {
            if (myCorePin.ad_channel == 0xFFFFFFFF) // if channel is this number, the wrong pin is used (need to be a0 / a9)
            {
                return 0xFFFFFFFF;
            }
            ADC1->HC[0] = myCorePin.ad_channel; // write channel in hc to start reading the pin and start the conversion process
            while((ADC1->HS & 0b1) == 0 ){} //wait till the conversion complete (ADACT p. 3368)
            return (adc_value_type)ADC1->R[0]; //read from the ADC1 -> R0 register
        }

        void refresh() override
        {
            // calibrate using the on chip calibration function
            ADC1->GC |= (0b1 << 7);
            while((ADC1->GC & (0b1 << 7)) != 0){} // check if the CAL bit is still high, if not, calibration is done
            return;
        }
    };

    class pin_in_out : public hwlib::pin_in_out
    {
        // mind that the setting of directions, can require a wait in some cases. The chip needs some time to actually set the direction to input or output. 
        private:
        const mimxrt1062::core_pin & myCorePin;
        const uint32_t configMask = ((0b1 << 16) /*HYS*/| (0b00 << 14) /*PUS*/ | (0b1<<13) /*PUE*/ | (0b1 << 12) /*PKE*/ | (0b0 << 11) /*ODE*/ |  (0b10 << 6) /*SPEED*/ | (0b111 << 3) /*DSE*/ | 0b0 /*SRE*/ );
        public:
        pin_in_out(pins pin_number) : myCorePin(mimxrt1062::core_pin_struct_array[(int)pin_number])
        {
            mimxrt1062::writeIOMUXMUXCTL(myCorePin.IOMUXC_MUX_control_register_array_index,0b0101); 
            mimxrt1062::writeIOMUXPADCTL(myCorePin.IOMUXC_MUX_control_register_array_index,configMask);
        }

        void direction_set_input() override
        {
            reinterpret_cast<GPIO_Type *>(myCorePin.GPIO_port_base_adress)->GDIR &= ~(1 << myCorePin.GPIO_port_bit_number); // set the pin to read mode
        }

        bool read() override
        {
            return (reinterpret_cast<uint32_t>(reinterpret_cast<GPIO_Type *>(myCorePin.GPIO_port_base_adress)->PSR) & (1 << myCorePin.GPIO_port_bit_number)) != 0; 
        }

        void refresh() override
        {
            // does this even do something?
            reinterpret_cast<GPIO_Type *>(myCorePin.GPIO_port_base_adress)->DR_CLEAR |= (1 << myCorePin.GPIO_port_bit_number);
        }

          void direction_set_output() override
        {    
            reinterpret_cast<GPIO_Type *>(myCorePin.GPIO_port_base_adress)->GDIR |= (1 << myCorePin.GPIO_port_bit_number); // set the pin to write mode
        }

        void direction_flush() override
        {
            // Function not implemented, calling set input or output immidiately sets the pin direction
        }

        void write( bool x ) override
        {
            (x 
                ? reinterpret_cast<GPIO_Type *>(myCorePin.GPIO_port_base_adress)->DR_SET 
                : reinterpret_cast<GPIO_Type *>(myCorePin.GPIO_port_base_adress)->DR_CLEAR
            ) |= (1 << myCorePin.GPIO_port_bit_number);
        }

        void flush() override
        {
            // Function not implemented, calling write immidiately writes to a pin
        }

    };
    
    class pin_oc : public hwlib::pin_oc
    {
        // Mind that to use this class, an external 4k7 pull up or pull down is needed. For i2c a pull up is needed.
        private:
        const mimxrt1062::core_pin & myCorePin;
        const uint32_t configMask = ((0b1 << 16) /*HYS*/| (0b00 << 14) /*PUS*/ | (0b0<<13) /*PUE*/ | (0b0 << 12) /*PKE*/ | (0b1 << 11) /*ODE*/ |  (0b11 << 6) /*SPEED*/ | (0b110 << 3) /*DSE*/ | 0b0 /*SRE*/ );
        public:
        pin_oc(pins pin_number) : myCorePin(mimxrt1062::core_pin_struct_array[(int)pin_number])
        {
            mimxrt1062::writeIOMUXMUXCTL(myCorePin.IOMUXC_MUX_control_register_array_index,0b0101); 
            mimxrt1062::writeIOMUXPADCTL(myCorePin.IOMUXC_MUX_control_register_array_index,configMask);
        }
        bool read() override
        {
            return (reinterpret_cast<uint32_t>(reinterpret_cast<GPIO_Type *>(myCorePin.GPIO_port_base_adress)->PSR) & (1 << myCorePin.GPIO_port_bit_number)) != 0;
        }
       
        void write(bool x) override
        {
            if (x)
            {
               reinterpret_cast<GPIO_Type *>(myCorePin.GPIO_port_base_adress)->GDIR &= ~(1 << myCorePin.GPIO_port_bit_number); // set the pin to read mode
                wait_32_nops(); // this is needed (tested thoroughly!) do not touch. This is the shortest time that is needed to wait to let the pins change the input mode
            }
            else
            {
                reinterpret_cast<GPIO_Type *>(myCorePin.GPIO_port_base_adress)->GDIR |= (1 << myCorePin.GPIO_port_bit_number); // set the pin to write mode
                wait_32_nops(); // this is needed (tested thoroughly!) do not touch. This is the shortest time that is needed to wait to let the pins change the input mode
            }
        }
        void refresh() override
        {
            //does this even do something?
            reinterpret_cast<GPIO_Type *>(myCorePin.GPIO_port_base_adress)->DR_CLEAR |= (1 << myCorePin.GPIO_port_bit_number);
        }

        void flush() override
        {
        }

    };

    /// \cond INTERNAL
    void uart_init();
    /// \endcond 

    bool uart_char_available();
    char uart_getc();
    void uart_putc( char c );

    #ifdef _HWLIB_ONCE
    // NOTICE! To use UART on the Teensy 4.0, you need to use pin 0 (rx) and pin 1 (tx) in combination with an TTL to USB hardware piece. 
    // Teensy does not have this on board (as fas as I know), and so it is not implemented to use the standard USB. Other TX or RX pins will not work.
    // I used a USB to TTL converter to read out the UART pins. Works good.
    // CIN CURRENTLY DOES NOT WORK! MAYBE SOMEONE ELSE CAN FIX IT?
    /**
     * @brief Function to cout a complete 32 bits number to see what is in registers, for debugging purposes only.    
     * 
     * @param byte le byte
     */
    void binCout(uint32_t byte)
{
	for (int i = 31; i >= 0; i--)
	{
		auto b = byte >> i;
		b &= 1;
		hwlib::cout << b;
	}
}
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
        const uint32_t txConfigMask = ((0b0 << 16) /*HYS*/| (0b00 << 14) /*PUS*/ | (0b1<<13) /*PUE*/ | (0b1 << 12) /*PKE*/ | (0b0 << 11) /*ODE*/ |  (0b11 << 6) /*SPEED*/ | (0b011 << 3) /*DSE*/ | 0b1 /*SRE*/ );
        const uint32_t rxConfigMask = ((0b1 << 16) /*HYS*/| (0b11 << 14) /*PUS*/ | (0b1<<13) /*PUE*/ | (0b1 << 12) /*PKE*/ | (0b0 << 11) /*ODE*/ |  (0b10 << 6) /*SPEED*/ | (0b110 << 3) /*DSE*/ | 0b0 /*SRE*/ );
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
        mimxrt1062::writeIOMUXPADCTL(tx.IOMUXC_MUX_control_register_array_index,txConfigMask);
        mimxrt1062::writeIOMUXPADCTL(rx.IOMUXC_MUX_control_register_array_index,rxConfigMask);
        reinterpret_cast<LPUART_Type *>(rx.serial_base_adress) -> CTRL &= ~(0b11 << 18); // disable rx and tx
        //======================================================
        // Copy paul with the FIFO thing, see if it works
        uint16_t tx_fifo_size = (((reinterpret_cast<LPUART_Type *>(tx.serial_base_adress) -> FIFO >> 4) & 0x07) << 2);
	    uint8_t tx_water = (tx_fifo_size < 16) ? tx_fifo_size >> 1 : 7;
        uint16_t rx_fifo_size = (((reinterpret_cast<LPUART_Type *>(rx.serial_base_adress) -> FIFO >> 0) & 0x07) << 2);
	    uint8_t rx_water = (rx_fifo_size < 16) ? rx_fifo_size >> 1 : 7;
        reinterpret_cast<LPUART_Type *>(rx.serial_base_adress) -> FIFO = (((rx_water & 0x03) << 16) | (tx_water & 0x03));
        reinterpret_cast<LPUART_Type *>(rx.serial_base_adress) -> FIFO |= ((1<<7) | (1<<3));
        //======================================================
        // setting everything else from UART, note that only consecutive rx and tx pins can be used. So rx1 and tx1 and rx2 and tx2 not rx1 and tx3.
        // baudrate = (PLL3 clock*1000000/6) / BAUD[0:12] * BAUD[24:28]+1
        // Wasn't able to find out the right clockspeed for this formula (should be 480 according to reference manual?) found out that a SBR of 130 = 9600 Baud, so deduced to this formula. magic. Seems to have something to do with the PLL bypass, but can't figure it out.
        // TODO: Find the right settings to crank up the 20'000'000 number to 480'000'000 (or whatever else). So you know for sure how many Mhz is send to the UART clock, so the formula works better and higher baudrates can be found. (this 20 Mhz is backwards calculated because i knew a SBR value of 130 gave me 9600 baud)
        uint32_t SBR = 20'000'000/(16*baudrate);
        reinterpret_cast<LPUART_Type *>(tx.serial_base_adress) -> STAT |= (0b1 << 27); // invert the rx pin WHY DOES THIS DO SOMEHTING? BUT NOT THE OTHER WAY AROUND, ASK WOUTER
        reinterpret_cast<LPUART_Type *>(tx.serial_base_adress) -> BAUD &= ~(0b11111 << 24); // clear OSR
        reinterpret_cast<LPUART_Type *>(tx.serial_base_adress) -> BAUD |= (0b01110 << 24); // set OSR to 15
        reinterpret_cast<LPUART_Type *>(tx.serial_base_adress) -> BAUD &= ~(0b1111111111111); // clear the SBR within BAUD register
        reinterpret_cast<LPUART_Type *>(tx.serial_base_adress) -> BAUD |= SBR; // set it to the right baudrate (130 (129.xxx) = 9600)
        reinterpret_cast<LPUART_Type *>(rx.serial_base_adress) -> CTRL |= (0b11 << 18); // set the uart recieve and transmit enable
        // Debug lines for seeing what is in all registers
        // hwlib::cout << "PARAM: ";
        // binCout(reinterpret_cast<LPUART_Type *>(rx.serial_base_adress) -> PARAM);
        // hwlib::cout << "\nGLOBAL: ";
        // binCout(reinterpret_cast<LPUART_Type *>(rx.serial_base_adress) -> GLOBAL);
        // hwlib::cout << "\nBAUD: ";
        // binCout(reinterpret_cast<LPUART_Type *>(rx.serial_base_adress) -> BAUD);
        // hwlib::cout << "\nSTAT: ";
        // binCout(reinterpret_cast<LPUART_Type *>(rx.serial_base_adress) -> STAT);
        // hwlib::cout << "\nCTRL: ";
        // binCout(reinterpret_cast<LPUART_Type *>(rx.serial_base_adress) -> CTRL);
        // hwlib::cout << "\nDATA: ";
        // binCout(reinterpret_cast<LPUART_Type *>(rx.serial_base_adress) -> DATA);
        // hwlib::cout << "\nMATCH: ";
        // binCout(reinterpret_cast<LPUART_Type *>(rx.serial_base_adress) -> MATCH);
        // hwlib::cout << "\nMODIR: ";
        // binCout(reinterpret_cast<LPUART_Type *>(rx.serial_base_adress) -> MODIR);
        // hwlib::cout << "\nFIFO: ";
        // binCout(reinterpret_cast<LPUART_Type *>(rx.serial_base_adress) -> FIFO);
        // hwlib::cout << "\n";
        // hwlib::cout << "\nWATER: ";
        // binCout(reinterpret_cast<LPUART_Type *>(rx.serial_base_adress) -> WATER);
        // hwlib::cout << "\n";
        
       
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
        // NOTICE!
        // CIN CURRENTLY NOT WORKING
        uart_init();
        const mimxrt1062::core_pin & rx = mimxrt1062::core_pin_struct_array[0]; // teensy 4.0 rx1
        uint32_t readdata = reinterpret_cast<LPUART_Type*>(rx.serial_base_adress)->STAT;
        return (readdata & (0b1 << 21)); // return the STAT[RDRF] value
    }

    char uart_getc(){
        // NOTICE!
        // CIN CURRENTLY NOT WORKING
        const mimxrt1062::core_pin & rx = mimxrt1062::core_pin_struct_array[0]; // teensy 4.0 rx1
        while( !uart_char_available()){ 
            hwlib::background::do_background_work();	
        }
        return reinterpret_cast<LPUART_Type *>(rx.serial_base_adress) -> DATA; 
    }

    void uart_putc( char c )
    {
        uart_init();
        const mimxrt1062::core_pin & tx = mimxrt1062::core_pin_struct_array[1]; // teensy 4.0 tx1
        while(!(reinterpret_cast<LPUART_Type*>(tx.serial_base_adress) -> STAT & (0b1 << 22)))
        {
            hwlib::background::do_background_work();	
        }
        reinterpret_cast<LPUART_Type *>(tx.serial_base_adress) -> DATA |= c;
    }

    #endif // _HWLIB_ONCE
}; //namespace teensy_40


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
            background::do_background_work();
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

#endif // H_PI_PICO
