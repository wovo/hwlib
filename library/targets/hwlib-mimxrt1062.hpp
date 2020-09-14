// ==========================================================================
//
// File      : hwlib-mimxrt1062.hpp
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

#ifndef HWLIB_MIMXRT1062
#define HWLIB_MIMXRT1062

#include "ARMCM7.h"
#include HWLIB_INCLUDE(../hwlib-all.hpp)
//#define __cplusplus //define that we're using c++ for core_cm7.h

namespace mimxrt1062
{
    enum class pins
    {
        a0
    };

    class pin_in : public hwlib::pin_in
    {
    private:
        volatile uint8_t &port_out;
        volatile uint8_t &port_in;
        uint8_t mask;

        void write(bool v)
        {
            if (v)
            {
                port_out |= mask;
            }
            else
            {
                port_out &= ~mask;
            }
        }

    public:
        /// pin_in constructor from ATMega328P port/pin numbers
        ///
        /// This call creates a pin_in from an ATMega328P port/pin
        /// number pair.
        ///
        /// This constructor sets the pin direction to input.
        pin_in(uint8_t port_number, uint8_t pin_number) : port_out{port_data(port_number)},
                                                          port_in{port_input(port_number)},
                                                          mask(0x1 << pin_number)
        {
            configure_as_gpio(port_number, pin_number);
            port_direction(port_number) &= ~mask;
        }

        bool read() override
        {
            // return (port_in & mask) != 0;
            return 1;
        }

        void refresh() override {}

        void pullup_enable()
        {
            write(1);
        }

        void pullup_disable()
        {
            write(0);
        }
    };
}; // namespace mimxrt1062

#endif //HWLIB_MIMXRT1062
