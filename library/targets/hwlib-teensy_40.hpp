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
    /**
     * @brief 
     * 
     * @return uint64_t 
     */
    uint64_t now_us();
    
    /// \cond INTERNAL
    void uart_init();
    /// \endcond

    bool uart_char_available();
    char uart_getc();
    void uart_putc(char c); 
    /**
     * @brief This Struct contains information about the relation of the Teensy board pin with the chip Core.
     * 
     */
    struct pin
    {
        /**
         * @brief The corresponding array index number within the IOMUXC->SW_MUX_CTL_PAD and SW_PAD_CTL_PAD arrays for the pin from the manufacturer header file, used to set a chip pad(pin) to a GPIO port and configurate.
         * 
         */
        unsigned int IOMUXC_SW_MUX_CTL_PAD_arrayIndex;
        /**
         * @brief The GPIO port adress in int format to write the registers for each port
         * 
         */
        unsigned int GPIO_port_base;
        /**
         * @brief Bit number from the pin within the chip GPIO port
         * 
         */
        unsigned int port_bit_mask_number;

        constexpr pin(unsigned int IOMUXC_SW_MUX_CTL_PAD_arrayIndex, unsigned int GPIO_port_base, unsigned int port_bit_mask_number = 0) : IOMUXC_SW_MUX_CTL_PAD_arrayIndex(IOMUXC_SW_MUX_CTL_PAD_arrayIndex), GPIO_port_base(GPIO_port_base), port_bit_mask_number(port_bit_mask_number){};
    };

    /**
     * @brief Uart_pin class containing all information for the use of UART protocols
     * 
     */
     struct uart_pin
    {
        /**
         * @brief The corresponding array index number within the IOMUXC->SW_MUX_CTL_PAD and SW_PAD_CTL_PAD arrays for the pin from the manufacturer header file, used to set a chip pad(pin) to a GPIO port and configurate.
         * 
         */
        unsigned int IOMUXC_SW_MUX_CTL_PAD_arrayIndex;
        /**
         * @brief The GPIO port adress in int format to write the registers for each port
         * 
         */
        unsigned int GPIO_port_base;
        /**
         * @brief The UART port adress in int format, to be used for uart things
         * 
         */
        unsigned int LPUART_port_base;
        /**
         * @brief Bit number from the pin within the chip GPIO port
         * 
         */
        unsigned int port_bit_mask_number;

        constexpr uart_pin(unsigned int IOMUXC_SW_MUX_CTL_PAD_arrayIndex, unsigned int GPIO_port_base, unsigned int LPUART_port_base, unsigned int port_bit_mask_number = 0) : IOMUXC_SW_MUX_CTL_PAD_arrayIndex(IOMUXC_SW_MUX_CTL_PAD_arrayIndex), GPIO_port_base(GPIO_port_base), LPUART_port_base(LPUART_port_base), port_bit_mask_number(port_bit_mask_number){};
    };

    /**
     * @brief Enumerator with the pins.
     * @details Each entry corresponds to a number that maps to the index number from the pin_struct_array
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
            reinterpret_cast<GPIO_Type *>(myPin.GPIO_port_base_adress)->GDIR |= 1 << myPin.port_bit_number;
        }

        void write(bool x)
        {
            if (x)
            {
                reinterpret_cast<GPIO_Type *>(myPin.GPIO_port_base_adress)->DR |= (1 << myPin.port_bit_number);
            }
            else
            {
                reinterpret_cast<GPIO_Type *>(myPin.GPIO_port_base_adress)->DR_CLEAR |= (1 << myPin.port_bit_number);
            }
        }

        void flush()
        {
        }
        /**
         * @brief Function to Toggle the GPIO on and off
         * 
         */
        void toggle()
        {
            reinterpret_cast<GPIO_Type *>(myPin.GPIO_port_base_adress)->DR_TOGGLE |= (1 << myPin.port_bit_number);
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
            return reinterpret_cast<uint32_t>(reinterpret_cast<GPIO_Type *>(myPin.GPIO_port_base_adress)->DR) & (1 << myPin.port_bit_number);
        }

        void refresh()
        {
            reinterpret_cast<GPIO_Type *>(myPin.GPIO_port_base_adress)->DR_CLEAR |= (1 << myPin.port_bit_number);
        }
    };

    /**
     * @brief Class containing the constructor and functions to use the Teensy 4.0 uart ports.
     * 
     */
    class uart_port
    {
        private:
        const mimxrt1062::core_pin & rx;
        const mimxrt1062::core_pin & tx;
        uint32_t baudrate;
        uint8_t muxCtlConfigmask = 0b010; // uart config number for the mux ctl register
        uint32_t padCtlConfigmask = 0b10011000010111000; // config mask for setting the pin_in pull up and such. starting from p. 559, setting pull down in this case.
        public:
        uart_port(pins rx_pin_number, pins tx_pin_number, unsigned int x) : rx(mimxrt1062::core_pin_struct_array[(int)rx_pin_number]), tx(mimxrt1062::core_pin_struct_array[(int)tx_pin_number]), baudrate(x)
        {
            mimxrt1062::writeIOMUXMUXCTL(rx.IOMUXC_MUX_control_register_array_index,muxCtlConfigmask);
            mimxrt1062::writeIOMUXMUXCTL(tx.IOMUXC_PAD_control_register_array_index,muxCtlConfigmask);
            reinterpret_cast<GPIO_Type *>(rx.GPIO_port_base_adress)->GDIR &= (0 << rx.port_bit_number);
            reinterpret_cast<GPIO_Type *>(tx.GPIO_port_base_adress)->GDIR &= (1 << tx.port_bit_number);
        };
        /**
         * @brief Transmit a byte over the uart port 
         * 
         * @param value The byte you want to cout
         */
        void transmit(uint32_t value)
        {
            return;
            
        }
    };
    #ifdef _HWLIB_ONCE
        void uart_init()
        {
            static bool uart_init_bool = false;
            if (uart_init_bool)
            {
                return;
            }
            uart_init_bool = true;

        } 
    #endif //_HWLIB_ONCE

}; //namespace teensy_40

/**
 * @brief This namespace lets the hwlib::target point to hwlib::teensy_40
 * 
 */
namespace hwlib
{
    namespace target = ::teensy_40;

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
#endif // TEENSY_40
