These directories contain the tests for one target.

The makefile can clean, build or run the applications.

string   : test the hwlib::string<> classs
two      : test whether an application can have two source files 
           (weak symbols etc.)
separate : test whether each hwlib .hpp file can be included on its own

The makefile.link is included by the makefiles in the subdirectories;
it sets the target-specific things and defers to the
makefile.link in the parent directory.

(c) Wouter van Ooijen (wouter@voti.nl) 2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at 
http://www.boost.org/LICENSE_1_0.txt) 
      
      
      