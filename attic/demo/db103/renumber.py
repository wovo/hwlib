import os

def rename( s, n ):
   for char in "0123456789":
       s = s.replace( char, "" )
   s = s.replace( "#", ( "##%04d" % ( 10 * n )))
   return s
   
def renumber():
   list = os.listdir( "." )
   list.sort()
   n = 1
   for file_name in list:
      if file_name.find( "#" ) > -1:
         temp_name = rename( file_name, n )
         n += 1
         os.rename( file_name, temp_name )

   for file_name in os.listdir( "." ):
      if file_name.find( "#" ) > -1:
         new_name = file_name.replace( "##", "#" )
         os.rename( file_name, new_name )
      
renumber()