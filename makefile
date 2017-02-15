#############################################################################
# 
# hwlib top-level Makefile 
#
# (c) Wouter van Ooijen (wouter@voti.nl) 2017
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at 
# http://www.boost.org/LICENSE_1_0.txt)
# 
#############################################################################

.PHONY: clean build run error test notab doxygen

run: error

MSG  = You are trying to run in a library directory.
MSG += Make one of the project source files your current editor file.

error:
	$(error $(MSG) )   
   
BMPTK  := ../bmptk
   
REMOVE := $(BMPTK)/tools/bmptk-rm 

doxygen:
	doxygen doxyfiles/Doxyfile
      
build: doxygen  
	cd demo && bmptk-make build
	cd test && bmptk-make build
	@echo "**** build completed succesfully"   
   
notab:
	cd demo && bmptk-make notab
	cd test && bmptk-make notab
	@echo "**** no tabs found"     
   
test:
	cd test && bmptk-make build && bmptk-make run
	@echo "**** test completed succesfully"   
   
clean:   
	$(REMOVE) -rf html
	cd demo && bmptk-make clean   
	cd test && bmptk-make clean   
	@echo "**** cleanup completed succesfully"  
   
# git commit -a -m 'work'   
# git config core.ignorecase false
push: 
	bmptk-make clean
	git add -A
	git commit -a
	git push		
   
push-as-work: 
	git add -A
	git commit -a -m 'small changes'
	git push				