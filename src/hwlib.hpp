// ============================================================================
//
// file : src/hwlib.hpp
//
// This file makes HwLib usable as an Arduino library
//
// ============================================================================

#ifndef _HWLIB_INCLUDED
#define _HWLIB_INCLUDED

#define HWCPP_QUOTE( FILE ) #FILE
#define HWCPP_INCLUDE( FILE ) HWCPP_QUOTE( ../library/FILE )

#if defined(ARDUINO_ARCH_AVR)
   #define _HWLIB_TARGET_OK
   #include HWCPP_INCLUDE( hwlib-arduino-uno.hpp )
#endif

#if defined(ARDUINO_ARCH_SAM)
   #define _HWLIB_TARGET_OK
   #include HWCPP_INCLUDE( hwlib-arduino-due.hpp )
#endif

#ifndef _HWLIB_TARGET_OK
   #error no valid ARDUINO_* target for HwLib
#endif

#endif // #ifndef _HWLIB_INCLUDED