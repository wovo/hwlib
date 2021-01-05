// ==========================================================================
//
// File      : hwlib-ostream.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017-2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// included only via hwlib.hpp, hence no multiple-include guard is needed

// this file contains Doxygen lines
/// @file

namespace hwlib {

/// end-of-line constant
constexpr char endl = '\n';
   
/// 0-character constant
constexpr char ends = '\0';

// ==========================================================================
//
// ostream format manipulators
//
// ==========================================================================

/// ostream output field width manipulator
struct setw {

   /// \cond INTERNAL  
   const uint_fast16_t x;
   /// \endcond  
      
   /// ostream output field width manipulator
   ///
   /// Writing the setw(N) manipulator to an ostream sets the minimum 
   /// width of the field in which the next item is written to N:
   /// If the item is smaller than N, it will be padded
   /// with fill characters.
   ///
   /// Setting the field width has an effect only on the next
   /// item that is printed, after that the field width
   /// resets to its initial value of 0.
   ///
   /// The same effect can be achieved by calling stream.setw(N).
   constexpr setw( uint_fast16_t x ) : x( x ){}

};
         
struct _setbase {

   /// \cond INTERNAL        
   const uint_fast16_t x;
   /// \endcond        
      
   constexpr _setbase( uint_fast16_t x ) : x( x ){}
};
   
/// set ostream radix to 2
///
/// When this manipulator is written to an ostream the base for
/// printing numbers is set to 2 (binary).
constexpr _setbase bin( 2 );
   
/// set ostream radix to 8
///
/// When this manipulator is written to an ostream the base for
/// printing numbers is set to 8 (octal).
constexpr _setbase oct( 8 );
   
/// set ostream radix to 10
///
/// When this manipulator is written to an ostream the base for
/// printing numbers is set to 10 (decimal).
/// This is the inital situation.
constexpr _setbase dec( 10 );
   
/// set ostream radix to 16
///
/// When this manipulator is written to an ostream the base for
/// printing numbers is set to 16 (hexadecimal).
   constexpr _setbase hex( 16 );
   
struct _showpos {
	
   /// \cond INTERNAL       
   const bool x; 
   /// \endcond     
      
      constexpr _showpos( bool x ) : x( x ){}
}; 
 
/// enable printing of a leading '+'
///
/// When this manipulator is written to an ostream the a leading
/// '+' will be printed when a positive value is printed.  
constexpr _showpos showpos( true );
  
/// disable printing of a leading '+'
///
/// When this manipulator is written to an ostream the a leading
/// '+' will be printed when a positive value is printed.  
/// This is the initial situation.
constexpr _showpos noshowpos( false );
   
struct _showbase {
	
   /// \cond INTERNAL       
   const bool x;
   /// \endcond      

   constexpr _showbase( bool x ) : x( x ){}
};
           
/// enable printing of a leading radix indication
///
/// When this manipulator is written to an ostream a leading
/// radix indication (0b, 0d, 0o, 0x) will be printed 
/// when a integer value is printed.  
constexpr _showbase showbase( true );

/// enable printing of a leading radix indication
///
/// When this manipulator is written to an ostream no a leading
/// radix indication will be printed when a integer value is printed.   
/// This is the initial situation.
constexpr _showbase noshowbase( false );
   
struct _boolalpha {
	
   /// \cond INTERNAL        
   const bool x;
   /// \endcond   
      
      constexpr _boolalpha( bool x ) : x( x ){}
   };
   
/// print a bool value as '0' or '1'
///
/// When this manipulator is written to an ostream subsequent boolean
/// values will be written as '0' or '1'.  
/// This is the initial situation.           
constexpr _boolalpha boolalpha( true );
   
/// print a bool value as 'false' or 'true'
///
/// When this manipulator is written to an ostream subsequent boolean
/// values will be written as 'false' or 'true'.  
/// This is the initial situation.           
constexpr _boolalpha noboolalpha( false );

/// ostream filler character manipulator
struct setfill {

   /// \cond INTERNAL        
   const char x;
   /// \endcond  
  
   /// ostream filler character manipulator
   ///
   /// Writing setfill(C) to an ostream sets filler character
   /// that is used to pad an item when it is smaller
   /// than the current field width.
   ///
   /// The same effect can be achieved by calling stream.setfill(C).   
      constexpr setfill( char x ) : x( x ){}
};
           
struct _right {
   constexpr _right(){}
}; 
           
/// align an item right in its field
///
/// When this manipulator is written to an ostream subsequent
/// items that are smaller than the field width are aligned
/// right (filled out at the left) in their field width.
/// This is the initial situation.                      
constexpr _right right;
   
struct _left {
   constexpr _left(){}
}; 
                 
/// align an item left in its field
///
/// When this manipulator is written to an ostream subsequent
/// items that are smaller than the field width are aligned
/// left (filled out at the right) in their field width.                     
constexpr _left left;
            
struct _flush {
   constexpr _flush( void ){}
}; 
          
/// flush an stream
///
/// Writing this manipulator to an ostream has the same
/// effect as calling its flush() function.           
constexpr _flush flush;
   
   
// ==========================================================================
//
// formatted ostream
//
// ==========================================================================
  
/// formatted character output interface
///
/// This class is an std::ostream work-alike for small embedded systems.
/// Most formatting features of std::ostream are supported.
/// Floating point values are not supported.
/// 
/// This class is abstract: a concrete subclass 
/// must implement putc() and flush().
class ostream : public noncopyable {
private:
   
   uint_fast16_t field_width;
   uint_fast16_t numerical_radix;
   char fill_char;
   char hex_base;
   bool align_right;
   bool show_pos;
   bool bool_alpha;
   bool show_base;
        
   static size_t strlen( const char *s ){
      size_t n = 0;
      while( *s != '\0' ){
         n++;
         s++;
      }
      return n; 
   }     
   
   // must handle negative numbers!
   void filler( int_fast16_t n ){
      while( n-- > 0 ){
         *this << fill_char;
      }
   }      
       
               
   // =======================================================================
   //
   // helper for printing integer values, which are generated
   // in reverse order
   //
   // =======================================================================
      
   struct reverse {
      static constexpr uint_fast16_t length = 70;
      char body[ length ];
      char *content;
         
      reverse(){
         body[ length - 1 ] = '\0';
         content = & body[ length - 1 ];
      }
         
      void add_char( char c ){
         content--;
         *content = c;
      }
         
      void add_digit( char c, char hex_base ){
         if( c > 9 ){
            c += ( hex_base - 10 );
         } else {
            c += '0';
         } 
         add_char( c );
      }
         
      void add_prefix( const ostream & s ){
         if( s.show_base ){
            switch( s.numerical_radix ){
               case 2  : add_char( 'b' ); break;
               case 8  : add_char( 'o' ); break;
               case 10 : return;
               case 16 : add_char( 'x' ); break;
               default : add_char( '?' ); break; 
            }
            add_char( '0' );
         }
      }          
   };
  
public:
      
   constexpr ostream(): 
      field_width( 0 ), 
      numerical_radix( 10 ),
      fill_char( ' ' ), 
      hex_base( 'A' ),
      align_right( true ), 
      show_pos( false ),
      bool_alpha( false ),
      show_base( false )
   {}
      
   /// char output function
   ///
   /// This function is called by the other functions to output
   /// each character.
   virtual void putc( char c ) = 0;    
       
   /// char output operator 
   ostream & operator<< ( char c ){ 
      putc( c ); 
      return *this; 
   }
      
   /// flush 
   ///
   /// This function waits until all characters are realy written
   /// to whatever is their destination.
   ///
   /// Writing the flush constant has the same effect as calling flush().
   virtual void flush( void ) = 0;
      
   /// \cond INTERNAL
   friend ostream & operator<< ( ostream & stream, const _flush x ){
      stream.flush();
      return stream;
   }
   /// \endcond      
      
      
   // =======================================================================
   //
   // manipulators
   //
   // =======================================================================
  
   /// return the current field width
   uint_fast16_t width( void ) const { return field_width; }
      
   /// set the field width, return the old field width
   uint_fast16_t width( uint_fast16_t x ) { 
      auto temp = field_width; 
      field_width = x; 
      return temp;
   }
      
   /// \cond INTERNAL      
   friend ostream & operator<< ( ostream & stream, const setw & x ){
      stream.width( x.x );
      return stream;
   }
   /// \endcond 
      
   /// return the numerical radix       
   uint_fast16_t base( void ) const { return numerical_radix; }
      
   /// set the numerical radix, return the old numerical radix  
   uint_fast16_t base( uint_fast16_t x ) { 
      auto temp = numerical_radix;
      numerical_radix = x; 
      return temp;
   }
      
   /// \cond INTERNAL      
   friend ostream & operator<< ( ostream & stream, const _setbase & x ){
      stream.numerical_radix = x.x;
      return stream;
   }
   /// \endcond 
      
   /// return the current showpos setting        
   bool showpos( void ) const { return show_pos; }
      
   /// set the showpos setting, return the old showpos setting 
   bool showpos( bool x ) { 
      bool temp = show_pos;
      show_pos = x;
      return temp;
   }   
      
   /// \cond INTERNAL      
   friend ostream & operator<< ( ostream & stream, const _showpos & x ){
      stream.show_pos = x.x;
      return stream;
   }
   /// \endcond 
      
   /// return the current showbase setting        e
   bool showbase( void ) const { return show_base; }
      
   /// set the showbase setting, return the old showbase setting     
   bool showbase( bool x ){ 
      bool temp = show_base;
      show_base = x; 
      return temp;
   }
      
   /// \cond INTERNAL      
   friend ostream & operator<< ( ostream & stream, const _showbase & x ){
      stream.show_base = x.x;
      return stream;
   }      
   /// \endcond 
      
   /// return the current boolalpha setting        
   bool boolalpha( void ) const { return bool_alpha; }
      
   /// set the noboolalpha setting, return the old noboolalpha setting       
   bool boolalpha( bool x ) { 
      bool temp = bool_alpha;
      bool_alpha = x; 
      return temp;
   }
      
   /// \cond INTERNAL      
   friend ostream & operator<< ( ostream & stream, const _boolalpha & x ){
      stream.bool_alpha = x.x;
      return stream;
   }
   /// \endcond 
      
   /// return the current fill char setting             
   char fill( void ) const { return fill_char; }
      
   /// set the fill char setting, return the old fill char setting
   char fill( char x ){ 
      char temp = fill_char;
      fill_char = x; 
      return temp;
   }
      
   /// \cond INTERNAL      
   friend ostream & operator<< ( ostream & stream, const setfill x ){
      stream.fill_char = x.x;
      return stream;
   }      
   /// \endcond 
      
   /// \cond INTERNAL      
   void right( void ){ align_right = true; }      
   friend ostream & operator<< ( ostream & stream, const _right x ){
      stream.align_right = true;
      return stream;
   }
   /// \endcond 
      
   /// \cond INTERNAL      
   void left( void ){ align_right = false; }     
   friend ostream & operator<< ( ostream & stream, const _left x ){
      stream.align_right = false;
      return stream;
   }
   /// \endcond 
      
   // bool must_align_right( void ){ return align_right; }
      
      
   // =======================================================================
   //
   // print bool and string types
   //
   // =======================================================================
      
   /// output operator for bool
   friend ostream & operator<< ( ostream & stream, bool x ){
      if( stream.boolalpha()){
         stream << ( x ? "true" : "false" );
      } else {
         stream << ( x ? "1" : "0" );
      }
      return stream;   
   }      
  
   /// output operator for const char pointer (literal string)
   friend ostream & operator<< ( ostream & stream, const char *s ){
      if( stream.align_right ){
         stream.filler( static_cast< int_fast16_t >( 
		    stream.width()) - strlen( s )); 
      }       
      for( const char *p = s; *p != '\0'; p++ ){
         stream << *p;
      }
      if( ! stream.align_right ){
        stream.filler( static_cast< int_fast16_t >( 
		   stream.width()) - strlen( s )); 
      }  
      stream.width( 0 );
      return stream;
   }    
  
  
   // =======================================================================
   //
   // print integers
   //
   // =======================================================================
      
   /// output operator for integer      
   friend ostream & operator<< ( ostream & stream, int x ){
      reverse s;
         
      bool minus = ( x < 0 );
      if( x < 0 ){ x = -x; }
         
      if( x == 0 ){
         s.add_digit( 0, stream.hex_base );
      }
      while( x > 0 ){
         s.add_digit( x % stream.base(), stream.hex_base );
         x = x / stream.base();
      }
      s.add_prefix( stream );
         
      if( minus ){
         s.add_char( '-' );
      } else if( stream.showpos() ){
         s.add_char( '+' );
      }        
         
      stream << s.content;
      return stream;   
   }
   
   /// output operator for short integer   
   friend ostream & operator<< ( ostream & stream, short int x ){
      return stream << static_cast< int >( x );
   }
   
   /// output operator for long integer   
   friend ostream & operator<< ( ostream & stream, long int x ){
      return stream << static_cast< int >( x );
   }
   
   /// output operator for long long integer   
   friend ostream & operator<< ( ostream & stream, long long int x ){
      reverse s;

      bool minus = ( x < 0 );
      if( x < 0 ){ x = -x; }

      if( x == 0 ){
         s.add_digit( 0, stream.hex_base );
      }
      while( x != 0 ){
         s.add_digit( x % stream.base(), stream.hex_base );
         x = x / stream.base();
      }
      s.add_prefix( stream );

      if( minus ){
         s.add_char( '-' );
      } else if( stream.showpos() ){
         s.add_char( '+' );
      }   
         
      stream << s.content;
      return stream;   
   }
   
   /// output operator for short unsigned integer   
   friend ostream & operator<< ( ostream & stream, short unsigned int x ){
      return stream << static_cast< long long int >( x );      
   }
   
   /// output operator for unsigned integer   
   friend ostream & operator<< ( ostream & stream, unsigned int x ){
      return stream << static_cast< long long int >( x );      
   }
   
   /// output operator for unsigned long integer   
   friend ostream & operator<< ( ostream & stream, unsigned long int x ){
      return stream << static_cast< long long int >( x ); 
   }
 
   /// output operator for unsigned long long integer    
   friend ostream & operator<< ( ostream & stream, unsigned long long x ){
      return stream << static_cast< long long int >( x ); 
   }
   
   /// output operator for signed char (prints as integer)   
   friend ostream & operator<< ( ostream & stream, signed char c ){
      return stream << static_cast< int >( c ); 
      //stream.putc( c );
      //return stream;
   }
   
   /// output operator for unsigned char (prints as integer)   
   friend ostream & operator<< ( ostream & stream, unsigned char c ){
      return stream << static_cast< int >( c ); 
      //stream.putc( c );
      //return stream;
   }
      
}; // class ostream  

}; // namespace hwlib
