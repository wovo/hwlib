#############################################################################
# 
# dummy Makefile for bmptk hwcpp directory
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at 
# http://www.boost.org/LICENSE_1_0.txt)
# 
#############################################################################

.PHONY: clean build run error

clean: error
build: error
run: error

MSG  = You are trying to build in a library directory.
MSG += Make one of the project source files your current editor file.

error:
	$(error $(MSG) )
		
		