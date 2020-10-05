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
     * @brief This Struct contains information about the relation of the Teensy board pin with the chip Core
     * 
     */
    struct pin
    {
        /**
         * @brief The array index number within the IOMUXC->SW_MUX_CTL_PAD array from the manufacturer header file, used to set a chip pad(pin) to a GPIO port
         * 
         */
        unsigned int iomuxc_sw_mux_ctl_pad_GPIO_number;
        /**
         * @brief Bit number from the pin within the chip GPIO port
         * 
         */
        unsigned int  port_bit_mask;

        constexpr pin(unsigned int iomuxc_sw_mux_ctl_pad_GPIO_number,unsigned int port_bit_mask=0): iomuxc_sw_mux_ctl_pad_GPIO_number(iomuxc_sw_mux_ctl_pad_GPIO_number),port_bit_mask(port_bit_mask){};
    };
    
    /**
     * @brief Array containing all Teensy board pins with a pin object, containing all important chip->pin information
     * 
     */
    constexpr pin pin_struct_array[24] =
    {
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_03,3},   //d0
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_02,2},   //d1
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_04,4},     //d2
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_05,5},     //d3
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_06,6},     //d4
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_08,8},     //d5
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_10,10},     //d6
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_B1_01,17},     //d7
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_B1_00,16},     //d8
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_11,11},     //d9
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_00,0},      //d10
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_02,2},      //d11
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_01,1},      //d12
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_03,3},      //d13
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_02,18},  //d14
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_03,19},  //d15
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_07,23},  //d16
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_06,22},  //d17
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_01,17},  //d18
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_00,16},  //d19
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_10,26},  //d20
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_11,27},  //d21
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_08,24},  //d22
        {kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_09,25}   //d23
    };

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
       IOMUXC->SW_MUX_CTL_PAD[(int)pins::d13] |= 0b0101;
       GPIO2->GDIR |= (1<<3);
       GPIO2->DR_SET |= (1<<3); 
        return;
    }

    class pin_out : public hwlib::pin_out
    {

        public:
        pin_out(pins pin_number)
        {
            mimxrt1062::writeIOMUX(pin_struct_array[(int)pin_number].iomuxc_sw_mux_ctl_pad_GPIO_number,0b0101);
            //this is hardcoded for pin 13 (led) for now
            //CCM->CCGR0 |= (0b11 << 30); // set the clock to gpio block 2 on
        //    IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_03 = 5; // pin 13
        //    IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_03 = IOMUXC_PAD_DSE(7);
        //    GPIO2_GDIR |= (1 << 3);
        //    GPIO2_DR_SET = (1 << 3);

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