#############################################################################
# 
# Makefile that defers clean and build to its list of subdirectories
#
# It assumes that bmptk-make and bmptk-rm are found in the path.
#
# (c) Wouter van Ooijen (www.voti.nl) 2017
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)
# 
#############################################################################

SUBDIRS += blink

BUILDDIRS = $(SUBDIRS:%=build-%)
CLEANDIRS = $(SUBDIRS:%=clean-%)

.phony: clean build run error $(BUILDDIRS) $(CLEANDIRS)

clean: $(CLEANDIRS)
$(CLEANDIRS): 
	bmptk-make -C $(@:clean-%=%) clean
   
build: $(BUILDDIRS)
$(BUILDDIRS):
	bmptk-make -C $(@:build-%=%) build

run: error

MSG  = You are trying to run in a library directory.
MSG += Make one of the project source files your current editor file.

error:
	$(error $(MSG) )   
	
		