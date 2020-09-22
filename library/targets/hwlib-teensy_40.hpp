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
    enum class pins
    {
        d0 = (int)mimxrt1062::chip_gpio_chip_pin::gpio1_03,
        d1 = (int)mimxrt1062::chip_gpio_chip_pin::gpio1_02,
        d2 = (int)mimxrt1062::chip_gpio_chip_pin::gpio4_04,
        d3 = (int)mimxrt1062::chip_gpio_chip_pin::gpio4_05,
        d4 = (int)mimxrt1062::chip_gpio_chip_pin::gpio4_06,
        d5 = (int)mimxrt1062::chip_gpio_chip_pin::gpio4_08,
        d6 = (int)mimxrt1062::chip_gpio_chip_pin::gpio2_10,
        d7 = (int)mimxrt1062::chip_gpio_chip_pin::gpio2_17,
        d8 = (int)mimxrt1062::chip_gpio_chip_pin::gpio2_16,
        d9 = (int)mimxrt1062::chip_gpio_chip_pin::gpio2_11,
        d10 = (int)mimxrt1062::chip_gpio_chip_pin::gpio2_00,
        d11 = (int)mimxrt1062::chip_gpio_chip_pin::gpio2_02,
        d12 = (int)mimxrt1062::chip_gpio_chip_pin::gpio2_01,
        d13 = (int)mimxrt1062::chip_gpio_chip_pin::gpio2_03,
        d14 = (int)mimxrt1062::chip_gpio_chip_pin::gpio1_18,
        d15 = (int)mimxrt1062::chip_gpio_chip_pin::gpio1_19,
        d16 = (int)mimxrt1062::chip_gpio_chip_pin::gpio1_23,
        d17 = (int)mimxrt1062::chip_gpio_chip_pin::gpio1_22,
        d18 = (int)mimxrt1062::chip_gpio_chip_pin::gpio1_17,
        d19 = (int)mimxrt1062::chip_gpio_chip_pin::gpio1_16,
        d20 = (int)mimxrt1062::chip_gpio_chip_pin::gpio1_26,
        d21 = (int)mimxrt1062::chip_gpio_chip_pin::gpio1_27,
        d22 = (int)mimxrt1062::chip_gpio_chip_pin::gpio1_24,
        d23 = (int)mimxrt1062::chip_gpio_chip_pin::gpio1_25,
        A0 = d14,
        A1 = d15,
        A2 = d16,
        A3 = d17,
        A4 = d18,
        A5 = d19,
        A6 = d20,
        A7 = d21,
        A8 = d22,
        A9 = d23
    };

    class pin_out : public hwlib::pin_out
    {

        public:
        pin_out(pins pin)
        {
            mimxrt1062::writeIOMUX((int)pin,0b0101);
            GPIO2->GDIR = 0b100;
            GPIO2->DR = 0b100;
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