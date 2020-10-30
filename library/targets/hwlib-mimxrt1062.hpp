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

    /// the number of ticks per us
    int_fast64_t HWLIB_WEAK ticks_per_us()
    {
        return 600; // this number should be the same as the cpu freq in Mhz
    }

    uint_fast64_t HWLIB_WEAK now_ticks()
    {
        static bool init_done = false;
        if (!init_done)
        {

            // kill the watchdog
            //WDT->WDT_MR = WDT_MR_WDDIS;

            // switch to the 84 MHz crystal/PLL clock
            //   sam3xa::SystemInit();

            //   EFC0->EEFC_FMR = EEFC_FMR_FWS(4);
            //   EFC1->EEFC_FMR = EEFC_FMR_FWS(4);

            SysTick->CTRL = 0;        // stop the timer
            SysTick->LOAD = 0xFFFFFF; // use its as a 24-bit timer
            SysTick->VAL = 0;         // clear the timer
            SysTick->CTRL = 5;        // start the timer, 1:1

            init_done = true;
        }

        static unsigned int last_low = 0;
        static unsigned long long int high = 0;

        // the timer ticks down, but we want an up counter
        unsigned int low = 0xFFFFFF - (SysTick->VAL & 0xFFFFFF);
        if (low < last_low)
        {

            // the timer rolled over, so increment the high part
            high += 0x1ULL << 24;
        }
        last_low = low;

        // return the aggregated ticks value
        // the counter runs at 84 MHz
        return (low | high);
    }

} // namespace mimxrt1062

#endif //HWLIB_MIMXRT1062
