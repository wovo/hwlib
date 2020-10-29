///@file
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
#include "mimxrt1062.h"

#ifndef HWLIB_MIMXRT1062
#define HWLIB_MIMXRT1062

namespace mimxrt1062
{

    /**
     * @brief Function to set a IO multiplex register to a mode using a mask. 
     * 
     * @param n Index in the IOMUXC SW_MUX_CTL_PAD array corresponding to the register adresses from the manufacturer file.
     * @param mask The mask that needs to be written to the register. 0b0101 to set it to GPIO for example. Read the reference manual for information on this.
     */
    inline void writeIOMUXCTL(int n, uint32_t mask)
    {
        IOMUXC->SW_MUX_CTL_PAD[n] |= mask;
    }

    /**
     * @brief Function to set an IO multiplex config register to a mode using a mask.
     * 
     * @param n Index in the IOMUXC SW_PAD_CTL_PAD array corresponding to the register adresses from the manufacturer file.
     * @param mask The mask that needs to be written to the register. Read the reference manual for information on this.
     */
    inline void writeIOMUXCPAD(int n, uint32_t mask)
    {
        IOMUXC->SW_PAD_CTL_PAD[n] |= mask;
    }

} // namespace mimxrt1062
#endif //HWLIB_MIMXRT1062
 