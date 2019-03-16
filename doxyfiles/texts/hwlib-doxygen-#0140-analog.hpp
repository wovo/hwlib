// ==========================================================================
//
// File      : hwlib-doxygen-analog.hpp
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


/// \page analog Analog interfaces
///
/// The (abstract) types
/// \ref hwlib::adc "adc" and \ref hwlib::dac "dac"
/// are used to read and write analog values.
///
/// <BR>
///
/// =========================================================================
///
/// \section adc adc
///
/// The \ref hwlib::adc adc is an abstract class that provides an interface
/// to an Analog-to-Digital (ADC) converter.
/// Targets that have an ADC, and ADC peripheral chips, 
/// provide this interface.
///
/// attrubutes and functions                          | meaning
/// --------------------------------------------------| -----------------------------------
/// \ref hwlib::adc::adc_value_type "adc_value_type"  | the type returned by read()
/// \ref hwlib::adc::adc_n_bits "adc_n_bits"          | the number of significant bits in the result returned by read()
/// \ref hwlib::adc::read "read()"                    | returns the adc value
/// \ref hwlib::adc::refresh "refresh()"              | makes sure the value returned by read() is up-to-date
///
/// An adc is buffered: a call to \ref hwlib::adc::refresh "refresh()"
/// is needed to make sure that the value returned by read is up-to-date.
///
/// <BR>
///
/// =========================================================================
///
/// \section dac dac
///
/// The \ref hwlib::dac dac is an abstract class that provides an interface
/// to an Digital-to-Analog (DAC) converter.
/// Targets that have a DAC, and DAC peripheral chips, 
/// provide this interface.
///
/// attrubutes and functions                          | meaning
/// --------------------------------------------------| -----------------------------------
/// \ref hwlib::dac::dac_value_type "dac_value_type"  | the type accepted by write()
/// \ref hwlib::dac::dac_n_bits "dac_n_bits"          | the number of significant bits in avlaue written by write()
/// \ref hwlib::dac::write "write(v)"                 | writes the value v to the DAC
/// \ref hwlib::dac::flush "flush()"                  | makes sure the value written appears on the output
///
/// An dac is bufffered: a call to \ref hwlib::dac::flush "flush() "
/// is needed to make sure that a value that was written appears
/// at the analog output.
///
/// <BR>
///
