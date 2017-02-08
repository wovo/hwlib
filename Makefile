#############################################################################
# 
# hwlib top-level Makefile 
#
# (c) Wouter van Ooijen (www.voti.nl) 2017
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at 
# http://www.boost.org/LICENSE_1_0.txt)
# 
#############################################################################

.PHONY: clean build run error

run: error

MSG  = You are trying to run in a library directory.
MSG += Make one of the project source files your current editor file.

error:
	$(error $(MSG) )   
   
REMOVE := ../bmptk/tools/bmptk-rm 
   
build:   
	Doxygen
	cd demos && bmptk-make build
	@echo "**** build completed succesfully"   
   
clean:   
	$(REMOVE) -rf html
	cd demos && bmptk-make clean   
	@echo "**** cleanup completed succesfully"   
   
push: 
	bmptk-make clean
	git add -A
	git commit -a -m 'work'
	git push		
		