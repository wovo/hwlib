// ==========================================================================
//
// File      : hwlib-color.hpp
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
   
enum class color_special : uint8_t {
   normal,
   transparent,
   unspecified
};   

/// color
/// 
/// This class abstracts a color as used in a graphics window.
/// A color can either be the special value default or transparent, 
/// or be represented by 3 RGB bytes.
class color final {
private:    
              
   static constexpr uint8_t clip( int_fast32_t x ){
      return ( x < 0 ) 
         ? 0 
         : ( x > 0xFF ? 0xFF : x ); 
   }
    
   constexpr color( 
      color_special special,
      int_fast32_t red, 
      int_fast32_t green, 
      int_fast32_t blue
   ): 
      special{ special },
      red{   clip( red   ) }, 
      green{ clip( green ) }, 
      blue{  clip( blue  ) }
   {}   
      
public:

   /// the special color values
   /// 
   /// When a color is default or transparent, 
   /// the read green and blue attributes are meaningless.
   color_special special;
   
   /// the RED attribute (part) of the color
   uint8_t red;
      
   /// the GREEN attribute (part) of the color
   uint8_t green;
      
   /// the BLUE attribute (part) of the color
   uint8_t blue;
   
   /// return whether the color is transparent
   constexpr bool is_transparent() const {
      return special == color_special::transparent;      
   }
   
   /// the 3-byte RGB representation of the color
   /// 
   /// This function returns the RGB representation of the color.
   /// For a special color (transparent or default), 
   /// the returned value will not be meaningful.
   uint_fast32_t rgb() const {
      return ( static_cast< uint_fast32_t >( red )   << 16 )
           | ( static_cast< uint_fast32_t >( green ) << 8  )
           | ( static_cast< uint_fast32_t >( blue )  << 0  );
   }
   
   /// construct a special color
   ///
   /// This constructor can be used to construct a special
   /// color value, but better use the pre-defined constants.  
   constexpr color( 
      color_special special
   ): 
      special{ special },
      red( 0 ),
      green( 0 ),
      blue( 0 )
   {}   
   
   /// construct a color from its RGB components
   /// 
   /// The arguments are integers, but they are clipped
   /// to the 0..255 range by the constructor.   
   constexpr color( 
      uint_fast32_t red, 
      uint_fast32_t green, 
      uint_fast32_t blue
   ): 
      special{ color_special::normal },
      red{   clip( red   ) }, 
      green{ clip( green ) }, 
      blue{  clip( blue  ) }
   {}   
   
   /// constructs a color from a three-byte integer value
   /// 
   /// For instance, color( 0xFF00FF ) is magenta.   
   constexpr explicit color( uint_fast32_t rgb32 = 0 ):
      special( color_special::normal ),  
      red{   clip( ( rgb32 & 0xFF0000 ) >> 16 ) }, 
      green{ clip( ( rgb32 & 0x00FF00 ) >>  8 ) }, 
      blue{  clip( ( rgb32 & 0x0000FF ) >>  0 ) }
   {}   
   
   /// return the negative of a color   
   constexpr color operator- ( void ) const {
      return color( 
         special,      
         0xFF - static_cast< uint8_t >( red ), 
         0xFF - static_cast< uint8_t >( green ), 
         0xFF - static_cast< uint8_t >( blue )
      ); 
   }   
   
   /// return a color divided by a value (reduced intensity)  
   constexpr color operator/ ( int n ) const {
      return color( 
         special,      
         ( red / n ), 
         ( green / n ), 
         ( blue / n)
      ); 
   }   
   
   /// reports whether two colors are equal   
   constexpr bool operator== ( const color c ) const {
      return special != color_special::normal 
         ? special == c.special
         : ( 
               ( red    == c.red ) 
            && ( green  == c.green ) 
            && ( blue   == c.blue )
         ); 
   }

   /// reports whether two colors are unequal
   constexpr bool operator!= ( const color c ) const {
      return ! ( *this == c );  
   }     
   
   /// return ourselves, or c when we are unspecified
   constexpr color specify( const color & c ) const {
      return 
         ( special == color_special::unspecified )
            ? c 
            : *this;
   }

};

/// print a color pair
///
/// An color is printed in [NNNN,NNNN,NNNN] format,
/// or [transparent] or (unspecified). 
/// The NNNN's are the hexadecimal value of the
/// red, green and blue components.
template< typename T >
T & operator<<( T & lhs, const color & rhs ){
   if( rhs.special == color_special::transparent ){
      return lhs << "[transparent]"; 
   } else if( rhs.special == color_special::unspecified ){
      return lhs << "[unspecified]"; 
   } else {
      lhs << "[";
      lhs.base( 16 );
      lhs.width( 4 );
      lhs.fill( '0' );
      return lhs   
         << rhs.red << "," 
         << rhs.green << ","
         << rhs.blue << "]";
   }
}

/// some basic colors
//@{ 
constexpr color black       = color( 0,       0,    0 );
constexpr color white       = color( 0xFF, 0xFF, 0xFF );
constexpr color red         = color( 0xFF,    0,    0 ); 
constexpr color green       = color( 0,    0xFF,    0 );
constexpr color blue        = color( 0,       0, 0xFF );
constexpr color gray        = color( 0x80, 0x80, 0x80 );
constexpr color yellow      = color( 0xFF, 0xFF,    0 );
constexpr color cyan        = color(    0, 0xFF, 0xFF );
constexpr color magenta     = color( 0xFF,    0, 0xFF );

constexpr color transparent = color( color_special::transparent );      
constexpr color unspecified = color( color_special::unspecified );      

constexpr color violet      = color( 0xEE82EE );        
constexpr color sienna      = color( 0xA0522D );        
constexpr color purple      = color( 0x800080 );         
constexpr color pink        = color( 0xFFC8CB );        
constexpr color silver      = color( 0xC0C0C0 );        
constexpr color brown       = color( 0xA52A2A );        
constexpr color salmon      = color( 0xFA8072 );
//@}


}; // namespace hwlib
