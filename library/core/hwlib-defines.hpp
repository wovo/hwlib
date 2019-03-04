// ==========================================================================
//
// File      : hwlib-defines.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017-2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// included only via hwlib.hpp, hence no multiple-include guard is needed

// this file contains Doxygen lines
/// @file

// This file has only macro's, so including them all in this namespace
// is only symbolic.
namespace hwlib {


/// mark a function declaration as never returning
/// 
/// This is useful when other code relies a function not to return.
/// It can also enable the compiler to generate slightly better code.
///
/// This must be done by a macro 
/// because Doxygen can't handle __attribute__.
#define HWLIB_NORETURN __attribute__((noreturn))


/// mark a function definition as weak
/// 
/// This allowed the function definition to be overruled by an 
/// (often application-defined) replacement.
///
/// This attribute also makes it possible to put a function definition
/// in a header, because all but one of the definitions will be 
/// eliminated by the linker.
///
/// This must be done by a macro 
/// because Doxygen can't handle __attribute__.
///
/// MinGW doesn't handle this correctly, hence redefining a weak symbol
/// (as used by the rtos) won't work with MinGW.
#ifdef __MINGW32__
   #define HWLIB_WEAK
#else
   #define HWLIB_WEAK __attribute__((weak))
#endif


/// mark a function definition as to be (always) inlined
/// 
/// Sometimes a function should always be inlined, for instance
/// because it is called only once, or because inlining it
/// will produce better code.
///
/// Use this attribute with care, because it can lead to much larger
/// code.
///
/// This must be done by a macro 
/// because Doxygen can't handle __attribute__.
#define HWLIB_INLINE __attribute__((always_inline))


/// mark a function definition as to be never inlined
/// 
/// Sometimes a function should not be inlined, for instance
/// because inlining would affect it timing.
///
/// Use this attribute with care, in most cases the decision to inline
/// or not should be left to the compiler.
///
/// This must be done by a macro 
/// because Doxygen can't handle __attribute__.
#define HWLIB_NOINLINE __attribute__((never_inline))
   
/// \cond INTERNAL 
#define HWLIB_STRINGYFY( X ) #X
#define HWLIB_HERE2( F, L ) ( "\n" F ":" HWLIB_STRINGYFY( L ) " " )
/// \endcond    
   

/// [file-name:line-number] macro
/// 
/// The macro HWLIB_HERE translates to a newline, the file-name, ":",
/// and the line-number of the place where the HWLIB_HERE macro
/// appears. This can be usefull for debug logging.
/// It is used by HLWIB_TRACE.
#define HWLIB_HERE HWLIB_HERE2( __FILE__, __LINE__ )
   

/// trace macro
/// 
/// The HWLIB_TRACE macro can be used like hwlib::cout to print to,
/// but what is printed will be prefixed with a newfile
/// and the HWLIB_HERE string.
#define HWLIB_TRACE (                                 \
   ::hwlib::cout << "\n" <<                           \
   ::hwlib::dec << HWLIB_HERE << hwlib::flush )       \


/// equality test macro
/// 
/// The HWLIB_TEST_EQUAL checks whether the two parameters compare equal.
/// If not, it outputs a messages that tries to identify the problem.
/// This is meant for use in test scripts. 
// _equal is defined elsewhere, because it needs hwlib::cout.
#define HWLIB_TEST_EQUAL( a, b ) \
   hwlib::_equal( __FILE__, __LINE__, #a, #b, a, b );   
   
   
#ifndef HWLIB_BAUDRATE 
/// console baudrate
///
/// When no HWLIB_BAUDRATE is defined, it will default to 1200 baud.
#define HWLIB_BAUDRATE 1200    
#endif   

   
}; // namespace hwlib   
