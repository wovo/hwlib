#############################################################################
# 
# Makefile that
#    - takes care of renumbering 
#    - defers other commands to the subdirectories
#
# (c) Wouter van Ooijen (www.voti.nl) 2019
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at 
# http://www.boost.org/LICENSE_1_0.txt)
# 
#############################################################################

ifeq ($(OS),Windows_NT)
   REMOVE := $(BMPTK)/tools/bmptk-rm 
   MAKE := bmptk-make
else
   REMOVE := rm -rf
   MAKE := make
endif

.PHONY: renumber clean build run error notab

renumber:
	$(MAKE) -f makefile.link renumber

build:
	$(MAKE) -f makefile.link build-subdirs
   
clean:
	$(MAKE) -f makefile.link clean-subdirs
   
notab:
	$(MAKE) -f makefile.link notab-subdirs
   
 
# user error handling   

run: error

MSG  = You are trying to run in a library directory.
MSG += Make one of the project source files your current editor file.

error:
	$(error $(MSG) )     
	
		