# ===========================================================================
# 
# HwCpp Arduino example file renamer
#
# (c) Wouter van Ooijen (wouter@voti.nl)
# 2016-04-15 version 1.0 work-in-progress
# license: Boost Software License - Version 1.0
#
# ===========================================================================
#
# Known limitations
# 
# tested only on Windows
#
# ===========================================================================


from __future__ import print_function
import os

def entries( path ):
   try:
      return os.listdir( path )
   except:
      return None

def run( root = "." ):
   for subdir in os.listdir( root ):
      files = entries( os.path.join( root, subdir ) )
      if files == None:
         pass
         # print( subdir, "is not a directory" )	  
      elif len( files ) == 0:
         print( subdir, "is empty" )
      elif len( files ) == 1:
         file = files[ 0 ]
         newname = subdir + ".ino"
         if file == newname:
            print( subdir, "contains", file )
         else:          
            print( subdir, "rename", file, "to", newname )
            os.rename( 
               os.path.join( subdir, file ),
               os.path.join( subdir, newname ) )
      else:
         print( subdir, "contains more than one file" )

      
run()     