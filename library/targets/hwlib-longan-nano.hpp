// ==========================================================================
//
// File      : hwlib-longan-nano.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2021
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================


#ifndef HWLIB_LONGAN_NANO_H
#define HWLIB_LONGAN_NANO_H

#include HWLIB_INCLUDE( hwlib-gd32v103c8.hpp ) 

namespace hwlib {

    const auto target_board = target_boards::longan_nano;
    
};   

#endif // #ifdef HWLIB_LONGAN_NANO_H
