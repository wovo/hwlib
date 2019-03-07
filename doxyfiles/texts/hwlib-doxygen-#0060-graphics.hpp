// ==========================================================================
//
// File      : hwlib-doxygen-char-io.hpp
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


/// \page graphics Graphics
///
/// The (abstract) types
/// \ref hwlib::istream istream and \ref hwlib::ostream ostream 
/// are used to read and write characters.
///
/// <BR>
///
/// =========================================================================
///
/// \section xy xy
///
/// An \ref hwlib::xy "xy" is a value type that stores two int__fst16_t 
/// values x and y. xy values can be added and subtracted, and can be 
/// multiplied and divided by an integer value.
/// An xy can also be printed
/// to an \ref hwlib::ostream "ostream" using operator<<. 
///
/// attributes and operations        | meaning or effect
/// -------------------------------- | ------------------------------------------
/// \ref hwlib::xy::x "x"            | x value
/// \ref hwlib::xy::y "y"            | y value
/// \ref hwlib::xy::operator+ "+"    | adds two xy values
/// \ref hwlib::xy::operator+ "-"    | subtracts to xy values
/// \ref hwlib::xy::operator+ "*"    | multiplies the  x and y value by an integer
/// \ref hwlib::xy::operator/ "/"    | divides the x and y values by an integer
/// \ref hwlib::xy::operator<< "<<"  | prints an xy to an \ref hwlib::ostream "ostream" 
///
/// The overloaded all() function can be used to iterate over all (x,y) values
/// within the (0 .. x-1, 0 .. y-1) range (in some unspecified order).
///
/// <BR>
///
/// =========================================================================
///
/// \section color color
///
/// A \ref hwlib::color "color" is a value type that stores a color as
/// three 8-bit red, green and blue values, plus a 'is_transparent' flag.
/// When the transparent flag is not set, the color values determine the
/// color. When it is set, the color values have no meaning.
/// An color can also be printed
/// to an \ref hwlib::ostream "ostream" using operator<<.
///
/// Colors can be constructed, negated,
/// and compared for equality or inequality.
///
/// attributes and operations                           | meaning or effect
/// --------------------------------------------------- | ------------------------------------------
/// \ref hwlib::color::is_transparent "is_transparent"  | transparency flag
/// \ref hwlib::color::red "rad"                        | red intensity
/// \ref hwlib::color::green "green"                    | green intensity
/// \ref hwlib::color::blue "blue"                      | blue intensity
/// \ref hwlib::color::color(uint_fast32_t red,uint_fast32_t green,uint_fast32_t blue,bool transparent) "color(r,g,b)"      | construct a color from its components
/// \ref hwlib::color::color(uint_fast32_t) "color(v)"              | construct a color from its 24-bit RGB value
/// \ref hwlib::color::operator- "-"                    | yields the inverse of a color
/// \ref hwlib::color::operator== "=="                  | tests for equality
/// \ref hwlib::color::operator!= "!="                  | tests for inequality
/// \ref hwlib::color::operator<< "<<"                  | prints an xy to an \ref hwlib::ostream "ostream" 
///
/// The following color constants are available:
/// - \ref hwlib::black "black"
/// - \ref hwlib::white "white"    
/// - \ref hwlib::red "red"  
/// - \ref hwlib::green "green"    
/// - \ref hwlib::blue "blue"    
/// - \ref hwlib::gray "gray"     
/// - \ref hwlib::yellow "yellow"    
/// - \ref hwlib::cyan "cyan"       
/// - \ref hwlib::magenta "magenta"    
/// - \ref hwlib::transparent "transparent"  
/// - \ref hwlib::violet "violet"    
/// - \ref hwlib::sienna "sienna"       
/// - \ref hwlib::purple "purple"          
/// - \ref hwlib::pink "pink"            
/// - \ref hwlib::silver "silver"       
/// - \ref hwlib::brown "brown"         
/// - \ref hwlib::salmon "salmon"   
///
/// <BR>
///
/// =========================================================================
///
/// \section image image
///
/// An \ref hwlib::image image is an abstract class that defines 
/// an interface to a picture, that is: a rectangle of read-only pixels.
/// An image is used to embed a picture in the application.
///
/// attributes and operations                  | meaning or effect
/// ------------------------------------------ | ------------------------------------------
/// \ref hwlib::image::size "size"             | size in pixels in x and y direction
/// \ref hwlib::image::operator[] operator []  | the color of the pixel at location loc
///
/// <BR>
///
/// =========================================================================
///
/// \section font font
///
/// An \ref hwlib::font font is an abstract class that defines 
/// an interface to a set of pictures that show characters as a graphic 
/// images.
/// A font is used to implement a character 
/// \ref hwlib::terminal "terminal" on a graphic 
/// \ref hwlib::window window.
///
/// attributes and operations                       | meaning or effect
/// ----------------------------------------------- | ------------------------------------------
/// \ref hwlib::image::operator[] "operator[ c ]"   | returns the image for char c
///
/// Two concrete built-in font classes are available:
/// - \ref hwlib::font_default_8x8 font_default_8x8
/// - \ref hwlib::font_default_16x16 font_default_16x16
///
/// The font_default_16x16 is not available on AVR8 targets because
/// the AVR compiler can't handle it.
///
/// <BR>
///
/// =========================================================================
///
/// \section window window
///
/// An \ref hwlib::window window is an abstract class that defines
/// an interface to a graphics display. The display can be cleared,
/// and a pixel can be set to a color.
///
/// Window operations are (potentially) buffered: a subsequent 
/// \ref hwlib::window::flush "flush()" call is required in order
/// for the previous operations to take effect. 
///
/// attributes and operations                       | meaning or effect
/// ----------------------------------------------- | ------------------------------------------
/// \ref hwlib::window::size "size"                 | size of the display, in pixels in a x any direction
/// \ref hwlib::window::background "background"     | the background color
/// \ref hwlib::window::foreground "foreground"     | the foreground color
/// \ref hwlib::window::clear "clear()"             | write the background color to all pixels
/// \ref hwlib::window::clear "clear(col)"          | write color col to tall pixels
/// \ref hwlib::window::write "write(loc, col)"     | write color col to the pixel at loc
/// \ref hwlib::window::write "write(loc, img)"     | write image img to the location loc
/// \ref hwlib::window::flush "flush()"             | flush all pending changes to the window
///
/// The \ref hwlib::window_part "window_part" decorator creates a 
/// window in a rectangular part of another window.
///
/// The \ref hwlib::window_invert "window_invert" decorator creates a 
/// window that writes inverted (the color of each pixel negated) to the 
/// underlying window.
///
/// <BR>
///
/// =========================================================================
///
/// \section drawables drawables
///
/// A \ref hwlib::drawable drawable is an abstract class that defines
/// an interface for something that cab be drawn 
/// on a \ref hwlib::window window.
///
/// attributes and operations                       | meaning or effect
/// ----------------------------------------------- | ------------------------------------------
/// \ref hwlib::drawable::start "start"             | origin (top left corner) of where the drawable is to be drawn
/// \ref hwlib::drawable::draw "draw(w)"            | draw the drawable on window w
///
/// A \ref hwlib::line "line" is a drawable. 
/// It is created by specifying its origin and its endpoint.
/// A color can be specified. 
/// If none is, the foreground color of the window is used.
///
/// A \ref hwlib::circle "circle" is a drawable.
/// It is created by specifying its midpoint and its radius
/// A color can be specified. 
/// If none is, the foreground color of the window is used.
///
/// <BR>
///
/// =========================================================================
///
/// \section terminal_from terminal_from
///
/// A \ref hwlib::terminal_from "terminal_from" creates a 
/// character \ref hwlib::terminal "terminal" from a window and
/// a character \ref hwlib::font "font".
///
///
/// <BR>
///

