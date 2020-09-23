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
/// @file
#include HWLIB_INCLUDE(../hwlib-all.hpp)
#include "hwlib-mimxrt1062.hpp"

#ifndef TEENSY_40
#define TEENSY_40
namespace teensy_40
{
    /**
     * @brief This enum class holds every IOMUXC_SW_CTL_PAD array index number for each teensy pin. This array comes from the manufactures header file.
     * @details From the Arduino IDE header file from Paul Stoffregen, the correct index numbers for the corresponding teensy gpio pins were deducted.
     * 
     */
    enum class pins
    {
        d0 = kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_03,
        d1 = kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_02,
        d2 = kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_04,
        d3 = kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_05,
        d4 = kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_06,
        d5 = kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_08,
        d6 = kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_10,
        d7 = kIOMUXC_SW_MUX_CTL_PAD_GPIO_B1_01,
        d8 = kIOMUXC_SW_MUX_CTL_PAD_GPIO_B1_00,
        d9 = kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_11,
        d10 = kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_00,
        d11 = kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_02,
        d12 = kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_01,
        d13 = kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_03,
        d14 = kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_02,
        d15 = kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_03,
        d16 = kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_07,
        d17 = kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_06,
        d18 = kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_01,
        d19 = kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_00,
        d20 = kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_10,
        d21 = kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_11,
        d22 = kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_08,
        d23 = kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_09,
        A0 = d14,
        A1 = d15,
        A2 = d16,
        A3 = d17,
        A4 = d18,
        A5 = d19,
        A6 = d20,
        A7 = d21,
        A8 = d22,
        A9 = d23,
    };

    inline void init_chip()
    {
        CCM->CCGR0 |= (0b11 << 30);
    }

    class pin_out : public hwlib::pin_out
    {

        public:
        pin_out(pins pin)
        {
            mimxrt1062::writeIOMUX((int)pin,0b0101);
            //this is hardcoded for pin 13 (led) for now
            GPIO1->GDIR |= 0b11111111111111111111111111111111;
            GPIO1->DR |= 0b11111111111111111111111111111111;
        }

        void write(bool x)
        {
            return;
        }

        void flush()
        {
            return;
        }
    };


};     //namespace teensy_40
namespace hwlib
{
    namespace target = ::teensy_40;
};
#endif // TEENSY_40