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


/// \page char-io Character I/O
///
/// The (abstract) types
/// \ref istream "istream" and \ref ostream "ostream"
/// are used to read and write characters.
///
/// <BR>
///
/// =========================================================================
///
/// \section istream istream
///
/// The (bastract) \ref hwlib::istream "istream" class provides a 
/// basic interface to a 
/// source of characters. It allows for the reading of a single character,
/// either blocking (waiting for a character to become available) or
/// non-blocking ('\0' is returned immediately when no character is 
/// available. 
///
/// functions                                               | effect
/// ------------------------------------------------------- | ---------------------------------------------------------
/// \ref hwlib::istream::getc "getc()"                      | wait for a char and return it
/// \ref hwlib::istream::getc_nowait "getc_nowait()"        | immediately return a char, returns '\0' if none available
/// \ref hwlib::istream::char_available "char_available()"  | return whether a char is available
/// \ref hwlib::istream::operator>> "operator>>"            | equivalent to getc()
///
/// Operations on an istream are not buffered.
///
/// <BR>
///
/// =========================================================================
///
/// \section ostream ostream
///
/// The (abstract) \ref hwlib::ostream "ostream" class provides an 
/// interface to a sink of characters. 
/// Both basic (single character) and formatted 
/// operations are provided. Unlike isteram, all ostream operations are
/// (potentially) buffered: a flush() call might be needed to 
/// make sure that everything what was written takes effect.
///
/// basic functions                                         | effect
/// ------------------------------------------------------- | ----------------------------
/// \ref hwlib::ostream::putc "putc(c)"                     | write the char c
/// \ref hwlib::ostream::flush "flush()"                    | flushes all buffered output
///
/// The formatted ostream operations are used via the overloaded << operator 
/// and mimic std::ostream operations.
///
/// write using <<                           | effect
/// ---------------------------------------- | ----------------------------
/// bool                                     | writes the bool value (see boolalpha)
/// char                                     | writes the single char
/// short int, int, long int, long long int  | writes the (signed) integer value 
/// unsigned integers                        | writes the (unsigned) integer value
/// const char *                             | writes the string
/// \ref hwlib::string "string"              | writes the string
/// flush                                    | equivalent to a flush() call
///
/// <BR>
///
/// formatting            | effect
/// ----------------------| ------------------------------------------------
/// boolalpha             | bools are written as '0' or '1'.
/// noboolalpha           | bools are written as 'false' or 'true'
/// showbase              | ints are witten with a base prefix
/// noshowbase            | ints are written without a base prefix
/// setfill(c)            | c is used as the fill character
/// setw(n)               | a write uses a field of n positions
/// right                 | a write is left aligned in its field
/// left                  | a write is right aligned in its field
/// bin                   | integers are written base 2
/// oct                   | integers are written base 8
/// dec                   | integers are written base 10
/// hex                   | integers are written base 16
///
/// <BR>
///
/// =========================================================================
///
/// \section terminal terminal
///
/// An \ref hwlib::terminal terminal is an ostream that writes to
/// a rectangular screen of characters. In addition to the ostream
/// formatting, it provides additional functions that control the cursor
/// and can clear or a part of the screen. A terminal is typically
/// used to display characters on a character LCD or OLED screen.
///
/// Terminal coordinates are 0-origin and count to the right and down.
/// In other words, the top-left character position is (0,0), and the bottom
/// right character position is size - (1,1).
///
/// terminal functions and attributes               | meaning or effect
/// ----------------------------------------------- | ---------------------------------------
/// \ref hwlib::terminal::size "size"               | size in characters in x and y direction
/// \ref hwlib::terminal::cursor "cursor"           | the current cursor position (readonly)
/// \ref hwlib::terminal::cursor_set "cursor_set()" | set the current cursor position
///
/// A terminal can be used 'in-channel' by the characters that are wriiten to it.
/// The following special character sequences are supported:
///
/// special sequence  | effect
/// ----------------- | ---------------------------------------
/// '\\n'             | puts the cursor at the first position of the next line
/// '\\r'             | puts the cursor at the start of the current line
/// '\\f'             | puts the cursor at the top-left position and clears the terminal
/// '\\txxyy'         | puts the cursor at the position (xx,yy)
///
/// <BR>
///
