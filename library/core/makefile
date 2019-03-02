#############################################################################
# 
# hwlib makefile that gives an clear error message 
# when a bmptk build inside the library directory is attempted
#
# (c) Wouter van Ooijen (wouter@voti.nl) 2017-2019
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at 
# http://www.boost.org/LICENSE_1_0.txt)
# 
#############################################################################

.PHONY: clean build run error test notab

# error handling

notab:
test:
build:
clean:
run: error

MSG  = You are trying to run in a library directory.
MSG += Make one of the project source files your current editor file.

error:
	$(error $(MSG) )   			
   
# defer to the next-level makefile.link
RELATIVE          ?= .
RELATIVE          := $(RELATIVE)/..
include           $(RELATIVE)/Makefile.link