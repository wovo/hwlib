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
    uint64_t ticks_per_us();
    uint64_t now_us();
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
        unsigned int IOMUXC_array_pad_number;
        /**
         * @brief The GPIO port adress in int format to write the registers for each port
         * 
         */
        unsigned int port_base;
        /**
         * @brief Bit number from the pin within the chip GPIO port
         * 
         */
        unsigned int  port_bit_mask_number;


       constexpr pin(unsigned int IOMUXC_array_pad_number,unsigned int port_base, unsigned int port_bit_mask_number=0): 
          IOMUXC_array_pad_number(IOMUXC_array_pad_number),port_base(port_base),port_bit_mask_number(port_bit_mask_number){};
    };
    
    /**
     * @brief Array containing all Teensy board pins with a pin object, containing all important chip->pin information
     * 
     */
    constexpr pin pin_struct_array[24] =
    {
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_03,GPIO6_BASE,3},   //d0
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_02,GPIO6_BASE,2},   //d1
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_04,GPIO9_BASE,4},     //d2
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_05,GPIO9_BASE,5},     //d3
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_06,GPIO9_BASE,6},     //d4
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_08,GPIO9_BASE,8},     //d5
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_10,GPIO7_BASE,10},     //d6
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_B1_01,GPIO7_BASE,17},     //d7
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_B1_00,GPIO7_BASE,16},     //d8
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_11,GPIO7_BASE,11},     //d9
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_00,GPIO7_BASE,0},      //d10
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_02,GPIO7_BASE,2},      //d11
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_01,GPIO7_BASE,1},      //d12
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_03,GPIO7_BASE,3},      //d13
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_02,GPIO6_BASE,18},  //d14
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_03,GPIO6_BASE,19},  //d15
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_07,GPIO6_BASE,23},  //d16
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_06,GPIO6_BASE,22},  //d17
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_01,GPIO6_BASE,17},  //d18
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_00,GPIO6_BASE,16},  //d19
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_10,GPIO6_BASE,26},  //d20
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_11,GPIO6_BASE,27},  //d21
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_08,GPIO6_BASE,24},  //d22
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_09,GPIO6_BASE,25}   //d23 the analogs pins need to be placed under here in the future
    };

    /**
     * @brief Enumerator with the pins.
     * @details Each entry corresponds to a number that maps to the index number from the pin_struct_array
     * 
     */
    enum class pins
    {
        d0 =0,
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
    };

    class pin_out : public hwlib::pin_out
    {
        private:
        const pin & myPin;
        const uint32_t configMask = 0b00011000010111000;
        public:
        pin_out(pins pin_number):myPin(pin_struct_array[(int)pin_number])
        {
            mimxrt1062::writeIOMUXCTL(myPin.IOMUXC_array_pad_number,0b0101);
            mimxrt1062::writeIOMUXCPAD(myPin.IOMUXC_array_pad_number,configMask);
	        reinterpret_cast<GPIO_Type*>(myPin.port_base)->GDIR |= (1<<myPin.port_bit_mask_number);
        }

        void write(bool x)
        {
            if (x)
            {
            reinterpret_cast<GPIO_Type*>(myPin.port_base)->DR |= (1 << myPin.port_bit_mask_number);
            }
            else
            {
            reinterpret_cast<GPIO_Type*>(myPin.port_base)->DR_CLEAR |= (1 << myPin.port_bit_mask_number);
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
            reinterpret_cast<GPIO_Type*>(myPin.port_base)->DR_TOGGLE |= (1 << myPin.port_bit_mask_number);
        }
    };

    class pin_in : public hwlib::pin_in
    {
        private:
        const pin & myPin;
        uint32_t configMask = 0b10011000010111000; // config mask for setting the pin_in pull up and such. starting from p. 559 
        public:
        pin_in(pins pin_number):myPin(pin_struct_array[(int)pin_number])
        {
            mimxrt1062::writeIOMUXCTL(myPin.IOMUXC_array_pad_number,0b0101);
            mimxrt1062::writeIOMUXCPAD(myPin.IOMUXC_array_pad_number,configMask);
            reinterpret_cast<GPIO_Type*>(myPin.port_base)->GDIR &= (0 << myPin.port_bit_mask_number);
        }

        bool read()
        {
            return reinterpret_cast<uint32_t>(reinterpret_cast<GPIO_Type*>(myPin.port_base)->DR) & (1 << myPin.port_bit_mask_number);
        }

        void refresh()
        {
            reinterpret_cast<GPIO_Type*>(myPin.port_base)->DR_CLEAR |= (1 << myPin.port_bit_mask_number);
        }

    };


};     //namespace teensy_40

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
};
#endif // TEENSY_40
