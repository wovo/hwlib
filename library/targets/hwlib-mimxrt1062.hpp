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

#include "mimxrt1062.h"
namespace mimxrt1062
{
    /**
     * @brief This enumerator corresponds to all the array indices in the SW_MUX_CTL_PAD member array of the IOMUXC_Type from the manufacturers header file. Read like: gpio[port]_[pin]
     * 
     * @details When the GPIO4_02 number is entered into IOMUXC->SW_MUX_CTL_PAD[GPIO4_02], you get the corresponding IO mulitplexer adress so that can be set to GPIO, or something else.
     * So if the port 1, pin 6 is needed, you use IOMUXC->SW_MUX_CTL_PAD[GPIO1_06]. 
     * 
     */
    enum class chip_gpio_chip_pin
    {
        gpio4_00 = 0,
        gpio4_01,
        gpio4_02,
        gpio4_03,
        gpio4_04,
        gpio4_05,
        gpio4_06,
        gpio4_07,
        gpio4_08,
        gpio4_09,
        gpio4_10,
        gpio4_11,
        gpio4_12,
        gpio4_13,
        gpio4_14,
        gpio4_15 = 15,
        gpio4_16,
        gpio4_17,
        gpio4_18,
        gpio4_19,
        gpio4_20,
        gpio4_21,
        gpio4_22,
        gpio4_23,
        gpio4_24,
        gpio4_25,
        gpio4_26,
        gpio4_27,
        gpio4_28,
        gpio4_29,
        gpio4_30,
        gpio4_31 = 31,
        gpio3_18,
        gpio3_19,
        gpio3_20,
        gpio3_21,
        gpio3_22,
        gpio3_23,
        gpio3_24,
        gpio3_25,
        gpio3_26,
        gpio3_27,
        gpio1_00,
        gpio1_01,
        gpio1_02,
        gpio1_03,
        gpio1_04 = 46,
        gpio1_05,
        gpio1_06,
        gpio1_07,
        gpio1_08,
        gpio1_09,
        gpio1_10,
        gpio1_12,
        gpio1_13,
        gpio1_14,
        gpio1_15,
        gpio1_16,
        gpio1_17,
        gpio1_18,
        gpio1_19,
        gpio1_20,
        gpio1_21 = 62,
        gpio1_22,
        gpio1_23,
        gpio1_24,
        gpio1_25,
        gpio1_26,
        gpio1_27,
        gpio1_28,
        gpio1_29,
        gpio1_30,
        gpio1_31,
        gpio2_00,
        gpio2_01,
        gpio2_02,
        gpio2_03,
        gpio2_04 = 77,
        gpio2_05,
        gpio2_06,
        gpio2_07,
        gpio2_08,
        gpio2_09,
        gpio2_10,
        gpio2_11,
        gpio2_12,
        gpio2_13,
        gpio2_14,
        gpio2_15,
        gpio2_16,
        gpio2_17,
        gpio2_18,
        gpio2_19,
        gpio2_20,
        gpio2_21,
        gpio2_22,
        gpio2_23,
        gpio2_24,
        gpio2_25,
        gpio2_26,
        gpio2_27,
        gpio2_28,
        gpio2_29,
        gpio2_30,
        gpio2_31,
        gpio3_12,
        gpio3_13,
        gpio3_14,
        gpio3_15,
        gpio3_16,
        gpio3_17,
        gpio3_00,
        gpio3_01,
        gpio3_02,
        gpio3_03,
        gpio3_04,
        gpio3_05,
        gpio3_06,
        gpio3_07,
        gpio3_08,
        gpio3_09,
        gpio3_10,
        gpio3_11 = 122
    };

    /**
     * @brief Function to set a IO multiplex register to a mode using a mask
     * 
     * @param n Index in the IOMUXC.SW_MUX_CTL_PAD register array from the manufacturer header file 
     * @param mask The mask that needs to be written to the register. 0b0101 to set it to GPIO for example. Read the reference manual for information on this
     */
    void setIOMUX(int n, uint32_t mask)
    {
        IOMUXC->SW_MUX_CTL_PAD[n] |= mask;
    }

} // namespace mimxrt1062
#endif //HWLIB_MIMXRT1062
