// ==========================================================================
//
// File      : hwlib-defines.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// this file contains Doxygen lines
/// @file

#ifndef HWLIB_DEFINES_H
#define HWLIB_DEFINES_H

/// \brief
/// mark a function declaration as never returning
/// \details
/// This is useful when other code relies a function not to return.
/// It can also enable the compiler to generate slightly better code.
///
/// This must be done by a macro 
/// because Doxygen can't handle __attribute__.
#define HWLIB_NORETURN __attribute__((noreturn))


/// \brief
/// mark a function definition as weak
/// \details
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
/// MinGW doesn't handle this cvorrectly, hence redefining a weak symbol
/// (as used by the rtos) won't work with MinGW.
#ifdef __MINGW32__
   #define HWLIB_WEAK
#else
   #define HWLIB_WEAK __attribute__((weak))
#endif


/// \brief
/// mark a function definition as to be (always) inlined
/// \details
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

/// \brief
/// mark a function definition as to be never inlined
/// \details
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
   
/// \brief
/// [file-name:line-number] macro
/// \details
/// The macro HWLIB_HERE tranlsates to a newline, the file-name, ":",
/// and the line-number of the place where the HWLIB_HERE macro
/// appears. This can be usefull for debug logging.
#define HWLIB_HERE HWLIB_HERE2( __FILE__, __LINE__ )
   
/// \brief
/// trace macro
/// \details
/// The TRACE macro can be used like hwlib::cout to print to,
/// but what is printed will be prefixed with a newfile
/// and the HWLIB_HERE string.
#define HWLIB_TRACE ( ::hwlib::cout << "\n" << HWLIB_HERE << hwlib::flush )

#endif // HWLIB_DEFINES_H