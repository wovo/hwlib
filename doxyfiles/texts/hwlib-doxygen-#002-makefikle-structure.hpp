// ==========================================================================
//
// File      : hwlib-doxygen-makefile-structure.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017-2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ===========================================================  ===============

// this file contains Doxygen lines (of course, that is its only purpose)
/// @file


/// \brief
/// bmptk build (makefile) structure
///
/// This page is relevant (only) if you want to work on the library 
/// itself and use its bmptk-bases makefile structure. 
/// 
/// To build and run a single project, 
/// run *bmptk-make run* in its directory.
/// 
/// Each project is in a separate directory and has its own bmptk makefile
/// that builds that project. 
/// This project makefile specifies project-specific properties, 
/// sets the symbol RELATIVE, and includes the makefile.link 
/// in the next higher directory, which can specify things
/// that are common to the projects in its subdirectories, 
/// updates RELATIVE to RELATIVE\.., and includes the
/// makefile.link in the next higher directory, up to the one in the main
/// directory of the library, which includes a makefile.custom (if present)
/// or else the makefile.local. It also adds some global specifications,
/// and finally includes the bmptk makefile.inc.
/// 
/// To build everything in a directory and below, run *bmptk-make build*.
/// 
/// Each directory that contains subdirectories that contain projects has 
/// a makefile that responds to this command by re-issuing it in all its
/// subdirectories. To do this, it also uses bmptk, so it uses
/// 'bmptk-make -f makefile.link <target>' to include bmptk.inc, using the
/// above mechanism.
/// 
/// De makefile.inc is included by the bmptk makefile.inc to update the bmptk
/// SEARCH, HEADERS and SOURCES with the itmes from the hwlib library.
/// 
/// Each directory that contains project sub-directories has a file 
/// update_codelite_workspace.bat. When executed, it creates a CodeLite 
/// workspace that contains the projects.
/// 
/// To use the library with bmptk:
///    - define HWLIB to be the path where you placed your copy of hwlib
///    - include $(HWLIB)/Makefile.include in your makefile
///    - include "hwlib.hpp" in your code
///    
/// To use the library without bmptk:
///    - add the hwlib/library directory to your search
///    - (if you want to edit hwlib files) 
///        add the hwlib files to your dependencies
///    - define the appropriate target as -DHWLIB_TARGET_* (see hwlib.hpp)	   
///        in your compiler parameters
///    - add hwlib.cpp to your sources
///    - include hwlib.hpp in your application source(s)      
/// 
