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
     * @brief Struct containing all the information needed to map the right Teensy pin to the right core pad/pin and all config registers.
     * 
     */
    struct core_pin
    {
        /**
         * @brief The base adress to the GPIO port.
         * 
         */
        uint32_t GPIO_port_base_adress;
        /**
         * @brief The (bit) number this pin is within the GPIO port.
         * 
         */
        uint8_t GPIO_port_bit_number;
        /**
         * @brief The base adress to the multiplexer control register to multiplex a chip pad to a hardware block.
         * 
         */
        uint32_t IOMUXC_MUX_control_register_array_index;
        /**
         * @brief The base adress to the chip pad configuration adress.
         * 
         */
        uint32_t IOMUXC_PAD_control_register_array_index;
        /**
         * @brief The base adress to the serial port.
         * @details This base adress maps to the base adress of a serial port. The bitnumber within te port is the same as the GPIO_port_bit_number. This port is used for UART communication and defaults to 0XFFFFFFFF.
         * 
         */
        uint32_t serial_base_adress;
        /**
         * @brief The ad conversion channel number. 
         * @details this value defaults to 0xFFFFFFFF.
         */
        uint32_t ad_channel;

        // constructor
        constexpr core_pin(uint32_t GPIO_port_base_adress, uint8_t GPIO_port_bit_number, uint32_t IOMUXC_MUX_control_register_array_index, uint32_t IOMUXC_PAD_control_register_array_index, uint32_t serial_base_adress = 0XFFFFFFFF, uint32_t ad_channel = 0XFFFFFFFF): 
        GPIO_port_base_adress(GPIO_port_base_adress), GPIO_port_bit_number(GPIO_port_bit_number), 
        IOMUXC_MUX_control_register_array_index(IOMUXC_MUX_control_register_array_index),  
        IOMUXC_PAD_control_register_array_index(IOMUXC_PAD_control_register_array_index),
        serial_base_adress(serial_base_adress),
        ad_channel(ad_channel)
        {};
    };
    /**
     * @brief Struct containing the core pin structs that map a chip pad to the configuration register adresses and IO ports
     * 
     */
    constexpr core_pin core_pin_struct_array[40] =
    {
        {GPIO6_BASE,3,kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_03,kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_03,LPUART6_BASE},
        {GPIO6_BASE,2,kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_02,kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_02,LPUART6_BASE},
        {GPIO9_BASE,4,kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_04,kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_04},
        {GPIO9_BASE,5,kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_05,kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_05},
        {GPIO9_BASE,6,kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_06,kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_06},
        {GPIO9_BASE,8,kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_08,kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_08},
        {GPIO7_BASE,10,kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_10,kIOMUXC_SW_PAD_CTL_PAD_GPIO_B0_10},
        {GPIO7_BASE,17,kIOMUXC_SW_MUX_CTL_PAD_GPIO_B1_01,kIOMUXC_SW_PAD_CTL_PAD_GPIO_B1_01,LPUART4_BASE},
        {GPIO7_BASE,16,kIOMUXC_SW_MUX_CTL_PAD_GPIO_B1_00,kIOMUXC_SW_PAD_CTL_PAD_GPIO_B1_00,LPUART4_BASE},
        {GPIO7_BASE,11,kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_11,kIOMUXC_SW_PAD_CTL_PAD_GPIO_B0_11},
        {GPIO7_BASE,0,kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_00,kIOMUXC_SW_PAD_CTL_PAD_GPIO_B0_00},
        {GPIO7_BASE,2,kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_02,kIOMUXC_SW_PAD_CTL_PAD_GPIO_B0_02},
        {GPIO7_BASE,1,kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_01,kIOMUXC_SW_PAD_CTL_PAD_GPIO_B0_01},
        {GPIO7_BASE,3,kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_03,kIOMUXC_SW_PAD_CTL_PAD_GPIO_B0_03},
        {GPIO6_BASE,18,kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_02,kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_02,LPUART2_BASE,7}, 
        {GPIO6_BASE,19,kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_03,kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_03,LPUART2_BASE,8},
        {GPIO6_BASE,23,kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_07,kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_07,LPUART3_BASE,12},
        {GPIO6_BASE,22,kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_06,kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_06,LPUART3_BASE,11},
        {GPIO6_BASE,17,kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_01,kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_01,0,6},
        {GPIO6_BASE,16,kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_00,kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_00,0,5},
        {GPIO6_BASE,26,kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_10,kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_10,LPUART8_BASE,15},
        {GPIO6_BASE,27,kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_11,kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_11,LPUART8_BASE,0},
        {GPIO6_BASE,24,kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_08,kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_08,0,13},
        {GPIO6_BASE,25,kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_09,kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_09,0,14},
        {GPIO6_BASE,12,kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_12,kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_12,LPUART1_BASE},
        {GPIO6_BASE,13,kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_13,kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_13,LPUART1_BASE},
        {GPIO6_BASE,30,kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_14,kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_14},
        {GPIO6_BASE,31,kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_15,kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_15},
        {GPIO8_BASE,18,kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_32,kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_32,LPUART7_BASE},
        {GPIO9_BASE,31,kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_31,kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_31,LPUART7_BASE},
        {GPIO8_BASE,23,kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_37,kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_37},
        {GPIO8_BASE,22,kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_36,kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_36},
        {GPIO7_BASE,12,kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_12,kIOMUXC_SW_PAD_CTL_PAD_GPIO_B0_12},
        {GPIO9_BASE,7,kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_07,kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_07},
        {GPIO8_BASE,15,kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_03,kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_03},
        {GPIO8_BASE,14,kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_02,kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_02},
        {GPIO8_BASE,13,kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_01,kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_01},
        {GPIO8_BASE,12,kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_00,kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_00},
        {GPIO8_BASE,17,kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_05,kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_05},
        {GPIO8_BASE,16,kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_04,kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_04}
    };


    /**
     * @brief Function to set a IO multiplex register to a mode using a mask.
     * @details notice that the first three bits are always set to zero when writing in this register, so set those bits as well. 
     * 
     * @param n Index in the IOMUXC SW_MUX_CTL_PAD array corresponding to the register adresses from the manufacturer file.
     * @param mask The mask that needs to be written to the register. 0b0101 to set it to GPIO for example. Read the reference manual for information on this.
     */
    inline void writeIOMUXMUXCTL(int n, uint32_t mask)
    {
        IOMUXC->SW_MUX_CTL_PAD[n] &= ~(0b111); 
        IOMUXC->SW_MUX_CTL_PAD[n] |= mask;
    }

    /**
     * @brief Function to set an IO multiplex config register to a mode using a mask.
     * @details Notice that the whole registerd is set to 0 except the reserved adresses, in other words, every bit needs to be set to a desired value.
     * 
     * @param n Index in the IOMUXC SW_PAD_CTL_PAD array corresponding to the register adresses from the manufacturer file.
     * @param mask The mask that needs to be written to the register. Read the reference manual for information on this.
     */
    inline void writeIOMUXPADCTL(int n, uint32_t mask)
    {
         IOMUXC->SW_PAD_CTL_PAD[n] &= ~(0b111111 << 10);
         IOMUXC->SW_PAD_CTL_PAD[n] &= ~(0b11111 << 3);
         IOMUXC->SW_PAD_CTL_PAD[n] &= ~0b1;
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
