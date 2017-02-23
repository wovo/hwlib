// ==========================================================================
//
// File      : hwlib-common.hpp
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

#ifndef HWLIB_COMMON_H
#define HWLIB_COMMON_H

namespace hwlib {

/// \brief
/// indicates whether an operation can be buffered   
/// \details
/// An unbuffered operation is, as it states, not buffered:
/// it works on fresh information, and has immediate effect.
///
/// A buffered operation can work on previously obtained data,
/// or have a delayed effect. 
///
/// Buffering is at the discretion of the implementation:
/// an opearation that is specified as buffered might actually
/// work without buffereing. The reverse is not true: an
/// operation that is specified as unbuffered is always unbuffered.
enum class buffering { 

   /// \brief
   /// the operation is not buffered
   /// \details
   /// For an input operation, the operation will work on or return
   /// information that is freshly obtained.
   ///
   /// For an output operation, the operation will wait untill the
   /// effect of the operation is completed.
   unbuffered, 
   
   /// \brief
   /// the operation can be buffered
   /// \details
   /// For an input operation, the operation might work on or return
   /// information that is buffered (remembered from a previous moment).
   /// A refresh() operation might be required before the operation
   /// to make sure that it works on fresh information.
   ///
   /// For an output operation, the operation might not wait untill the
   /// effect of the operation is completed.   
   /// A flush() operation might be requiired after the operation to
   /// make sure that the operation has effect.
   buffered 
};
   
}; // namespace hwlib

#endif // HWLIB_COMMON_H