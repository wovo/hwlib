#############################################################################
# 
# Makefile that defers clean and build to subdirectories
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at 
# http://www.boost.org/LICENSE_1_0.txt)
# 
#############################################################################

SUBDIRS += string
SUBDIRS += two
SUBDIRS += separate

BUILDDIRS = $(SUBDIRS:%=build-%)
CLEANDIRS = $(SUBDIRS:%=clean-%)
NOTABDIRS = $(SUBDIRS:%=notab-%)

ifeq ($(OS),Windows_NT)
   REMOVE := $(BMPTK)/tools/bmptk-rm 
   MAKE := bmptk-make
else
   REMOVE := rm -rf
   MAKE := make
endif

.phony: clean build run error notab (BUILDDIRS) $(CLEANDIRS) $(NOTABDIRS)

# include the bmptk makefile, and clean this directory

clean: $(CLEANDIRS)
	$(MAKE) -f makefile.link clean
   
# defer to the subdirectories

$(CLEANDIRS): 
	$(MAKE) -C $(@:clean-%=%) clean
   
build: $(BUILDDIRS)
$(BUILDDIRS):
	$(MAKE) -C $(@:build-%=%) build
   
notab: $(NOTABDIRS)
$(NOTABDIRS):
	$(MAKE) -C $(@:notab-%=%) notab 
   
# user error handling   

run: error

MSG  = You are trying to run in a library directory.
MSG += Make one of the project source files your current editor file.

error:
	$(error $(MSG) )   
	
		