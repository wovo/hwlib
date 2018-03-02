// ============================================================================
//
// file : src/hwlib.hpp
//
// These files makes HwLib usable as an Arduino library
//
// ============================================================================

#ifndef _HWLIB_INCLUDED
#define _HWLIB_INCLUDED

#define HWLIB_QUOTE( FILE ) #FILE
#define HWLIB_INCLUDE( FILE ) HWLIB_QUOTE( ../library/FILE )

#if defined(ARDUINO_ARCH_AVR)
   #define _HWLIB_TARGET_OK
   #undef putc
   #undef abs
   #include HWLIB_INCLUDE( hwlib-arduino-uno.hpp )
#endif

#if defined(ARDUINO_ARCH_SAM)
   #define _HWLIB_TARGET_OK
   #include HWLIB_INCLUDE( hwlib-arduino-due.hpp )
#endif

#ifndef _HWLIB_TARGET_OK
   #error no valid ARDUINO_* target for HwLib
#endif

#endif // #ifndef _HWLIB_INCLUDED