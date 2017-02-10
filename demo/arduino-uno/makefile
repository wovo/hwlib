#############################################################################
# 
# Makefile that defers to subdirectories
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at 
# http://www.boost.org/LICENSE_1_0.txt)
# 
#############################################################################

SUBDIRS += blink
SUBDIRS += hello

BUILDDIRS = $(SUBDIRS:%=build-%)
CLEANDIRS = $(SUBDIRS:%=clean-%)
NOTABDIRS = $(SUBDIRS:%=notab-%)

.phony: clean build run error notab (BUILDDIRS) $(CLEANDIRS) $(NOTABDIRS)

# include the bmptk makefile, and clean this directory

clean: $(CLEANDIRS)
	bmptk-make -f makefile.link clean
   
# defer to the subdirectories

$(CLEANDIRS): 
	bmptk-make -C $(@:clean-%=%) clean
   
build: $(BUILDDIRS)
$(BUILDDIRS):
	bmptk-make -C $(@:build-%=%) build
   
notab: $(NOTABDIRS)
$(NOTABDIRS):
	bmptk-make -C $(@:notab-%=%) notab 
   
# user error handling   

run: error

MSG  = You are trying to run in a library directory.
MSG += Make one of the project source files your current editor file.

error:
	$(error $(MSG) )        
	
		