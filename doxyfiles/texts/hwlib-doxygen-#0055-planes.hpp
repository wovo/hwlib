// ==========================================================================
//
// File      : hwlib-doxygen-planes.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017-2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// this file contains Doxygen lines (of course, that is its only purpose)
/// @file


/// \page ports Planes
///
/// A plane is a two-dimensional matrix of values.
/// Each value in the matrix is addressed by an xy pair of integers.
/// A plane can be read-only, write-only, or read-write.
/// The value stored at each location in the plane can for instance be
/// a black or white pixel, a color pixel, or an ASCII character.
///
/// The types of planes provided by the library are:
///    - window : a plane of write-only pixels, for instance an
///       LCD screen. A window can be color or only black-and-white.
///    - image: a read-only plane of pixels, for instance a picture
///       stored in the application, or captured by a camera.
///    - terminal: a write-only plane of ASCII characters, for instance
///       a character LCD.
///
/// Plane coordinates start at the top-left corner and extend to the right
/// ( x direction) and down (y direction). The top-left position is (0,0).
/// Each plane has a size attribute. The bottom-left position has
/// coordinate (size.x - 1, size.y - 1).
///
/// Planes of the same type can be manipulated by the same decorators:
///   - part( p, xy start, xy size ) returns a plane that is a part of
///      the original plane, starting at the specified location, 
///      and extending to the specified size.
///   - transpose
///   - mirror_x
///   - mirror_y
///   - extend_x
///   - extend_y
///
/// For the pixel planes there is an additional decorator:
///   - invert
///


