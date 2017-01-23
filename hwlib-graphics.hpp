// ==========================================================================
//
// File      : hwlib-graphics.hpp
// Part of   : hwlib library for V1OOPC and V1IPAS
// Copyright : wouter@voti.nl 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef HWLIB_GRAPHICS_H
#define HWLIB_GRAPHICS_H

#include <stdint.h>

namespace hwlib {

/// a pixel coordinate
//
/// This class abstracts a coordinate (pixel location) on a graphics screen,
/// or the distance between two coordinates.
class location final {
public:
   /// x value of the location
   int x;
   
   /// y value of the location
   int y;
   
   /// construct a location from its x and y values
   constexpr location( int x, int y ): x{ x }, y{ y }{}

   /// add two locations
   constexpr location operator+( const location rhs ) const {
      return location{ x + rhs.x, y + rhs.y };      
   }      
   
   /// subtract two locations
   constexpr location operator-( const location rhs ) const {
      return location{ x - rhs.x, y - rhs.y };      
   }      
   
}; 

/// graphics color
//
/// This class abstracts a color as used in a graphics window.
/// A color is represented by 3 RGB bytes an a transparency flag.
class color final {
private:    
              
   static constexpr uint8_t clip( int x, bool transparent = false ){
      return ( transparent )
         ? 0
         : ( x < 0 ) 
            ? 0 
            : ( x > 0xFF ? 0xFF : x ); 
   }   
      
public:
   /// the transparency of the color
   //
   /// When a color is tranparent, the read green and blue atrributes
   /// are meaningless.
   bool is_transparent;
   
   /// the RED attribute (part) of the color
   uint8_t red;
      
   /// the GREEN attribute (part) of the color
   uint8_t green;
      
   /// the BLUE attribute (part) of the color
   uint8_t blue;
   
   /// the 3-byte RGB representation of the color
   //
   /// This function returns the RGB reprsentation of the color.
   /// For a transparent color, the returned value will 
   /// not be meaningfull.
   uint_fast32_t rgb() const {
      return ( static_cast< uint_fast32_t >( red )   << 16 )
           | ( static_cast< uint_fast32_t >( green ) << 8  )
           | ( static_cast< uint_fast32_t >( blue )  << 0  );
   }
   
   /// construct a color from its RGB components
   //
   /// The transparency flag can be specified, but better use
   /// the transparent constant.
   /// 
   /// The arguments are integers, but they are clipped
   /// to the 0..255 range by the constructor.   
   constexpr color( 
      int red, 
      int green, 
      int blue, 
      bool transparent = false 
   ): 
      is_transparent{ transparent },
      red{   clip( red,   transparent ) }, 
      green{ clip( green, transparent ) }, 
      blue{  clip( blue,  transparent ) }
   {}   
   
   /// constructs a color from a three-byte integer value
   //
   /// For instance, color( 0xFF00FF ) is magenta.   
   constexpr color( uint_fast32_t rgb32 = 0 ):
      is_transparent( false ),  
      red{   clip( ( rgb32 & 0xFF0000 ) >> 16 ) }, 
      green{ clip( ( rgb32 & 0x00FF00 ) >>  8 ) }, 
      blue{  clip( ( rgb32 & 0x0000FF ) >>  0 ) }
   {}   
   
   /// return the negative of a color   
   constexpr color operator - ( void ) const {
      return color( 
         0xFF - static_cast< int >( red ), 
         0xFF - static_cast< int >( green ), 
         0xFF - static_cast< int >( blue ), 
         is_transparent ); 
   }   
   
   /// reports whether two colors are equal   
   constexpr bool operator == ( const color c ) const {
      return is_transparent 
         ? c.is_transparent 
         : ( 
            ( ! c.is_transparent ) 
            && ( red    == c.red ) 
            && ( green  == c.green ) 
            && ( blue   == c.blue )
         ); 
   }

   /// reports whether two colors are unequal
   constexpr bool operator != ( const color c ) const {
      return ! ( *this == c );  
   }     
      
};

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
constexpr color transparent = color( 0,       0,    0,   1 );      
constexpr color violet      = color( 0xEE82EE );        
constexpr color sienna      = color( 0xA0522D );        
constexpr color purple      = color( 0x800080 );         
constexpr color pink        = color( 0xFFC8CB );        
constexpr color silver      = color( 0xC0C0C0 );        
constexpr color brown       = color( 0xA52A2A );        
constexpr color salmon      = color( 0xFA8072 );
//@}

// ==========================================================================
   
/// a graphics windows
//
/// This class abstracts the interface to a graphic window.
class window {
private:

   /// write a pixel - implementation
   //
   /// This NVI function writes a the color col to the pixel at location loc.
   /// Loc is guaranteed to be within the window, and the color
   /// is guranteed to be not transparent.
   virtual void write_implementation( location pos, color col ) = 0;
   
public:
   /// the size of the window
   //
   /// This is the size of the window: the number of pixels
   /// in the x and y direction.
   const location size;
   
   /// the foreground color of the window
   //
   /// This color could be used to draw graphics.
   color foreground;
   
    /// the background color of the window
   //
   /// This is the color use by the clear() function.
   color background;
   
  /// construct a window by specifying its size and foreground and background colors.
   window( location size, color foreground, color background )
      : size{ size }, foreground{ foreground }, background{ background }
   {}
   
   /// write a pixel
   //
   /// This function writes a the color col to the pixel at location loc.
   /// If either the color is transparent, or the location is outside the window 
   /// the call has no effect. When no locor is specificied, the window's
   /// foreground color is used.
   void write( location pos, color col ){
      if(  ( ! col.is_transparent )
        && ( pos.x >= 0 ) && ( pos.x < size.x ) 
        && ( pos.y >= 0 ) && ( pos.y < size.y ) 
      ){
         write_implementation( pos, col );
      }   
   }
   
   #ifndef DOXYGEN // hide from doxygen
   void write( location pos ){
      write( pos, foreground );
   }   
   #endif
   
   /// clear the window
   //
   /// This function clears the windows by writing the background
   /// color to all pixels.
   /// The default implementation writes to all pixels in sequence.
   /// A concrete window can probably provide a faster implementation.
   virtual void clear(){
      for( int x = 0; x < size.x; ++x ){
         for( int y = 0; y < size.y; ++y ){
            write( location{ x, y }, background );    
         }                 
      }         
   }
};


// ==========================================================================

/// a window_part (subwindow of a larger window)
//
/// A window_part is a rectangular part of a larger window.
class window_part : public window {
private:
   window & w;
   location start;
   
   void write_implementation( location pos, color col ) override {
      w.write( start + pos, col );
   }      
   
public:      
   /// create a window_part from a larger window, its origin and its size
   //
   /// This call constructs a subwindow from a window, the start 
   /// (top-left pixel) of the subwindow, and the size of the subwindow.
   /// The foreground and background color are copied from the larger
   /// window.
   window_part( window &w, location start, location size ):
      window( size, w.foreground, w.background ),
      w( w ),
      start( start )
   {}   
      
};


// ==========================================================================

/// window_invert (invert writes to a window)
//
/// A window_inverts writes inverted to its larger window.
class window_invert : public window {
private:
   window & w;
   
   void write_implementation( location pos, color col ) override {
      w.write( pos, - col );
   }      
   
public:      
   /// create a window_invert from a window
   //
   /// This call constructs a window_invert from a window.
   /// The foreground and background color are copied from the larger
   /// window, but writes to the window_invert write the invert
   /// pixel to the underlying window.
   window_invert( window &w ):
      window( w.size, w.foreground, w.background ),
      w( w )
   {}   
      
};

// ==========================================================================

class drawable {
public: 
   location start;
    
   drawable( location start ): start{ start }{}
   
   virtual void draw( window & w ) = 0;
};

class line : public drawable {
private:   
   location end;
   color fg;
   
   static void swap( int & a, int & b ){
      unsigned int t;
      t = a; 
      a = b;
      b = t;
   }

   static int abs( int x ){
      return x >= 0 ? x : -x;
   }

public:
   line( location start, location end, color fg = black )
      : drawable{ start }, end{ end }, fg{ fg }
   {}   
   
   
   void draw( window & w ) override { 
      int x0 = start.x;
      int y0 = start.y;
      int x1 = end.x; 
      int y1 = end.y;
                   
      // http://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
      // http://homepages.enterprise.net/murphy/thickline/index.html
     
      int Dx = x1 - x0; 
      int Dy = y1 - y0;
   
      int steep = (abs(Dy) >= abs(Dx));
   
      if( steep ){
         swap( x0, y0 );
         swap( x1, y1 );
      
         // recompute Dx, Dy after swap
         Dx = x1 - x0;
         Dy = y1 - y0;
      }
   
      int xstep = 1;
      if( Dx < 0 ){
         xstep = -1;
         Dx = -Dx;
      }
   
      int ystep = 1;
      if( Dy < 0 ){
         ystep = -1;    
         Dy = -Dy; 
      }
      int TwoDy = 2*Dy; 
      int TwoDyTwoDx = TwoDy - 2*Dx; // 2*Dy - 2*Dx
      int E = TwoDy - Dx; //2*Dy - Dx
      int y = y0;
      int xDraw, yDraw, x;  
      for( x = x0; x != x1; x += xstep ){    
         if (steep) {     
            xDraw = y;
            yDraw = x;
         } else {     
            xDraw = x;
            yDraw = y;
         }

         w.write( location{ xDraw, yDraw }, fg );

         if( E > 0 ){
            E += TwoDyTwoDx; //E += 2*Dy - 2*Dx;
            y = y + ystep;
         } else {
            E += TwoDy; //E += 2*Dy;
         }
      }
   }
   
}; // class line   

class circle : public drawable {
private:   
   int radius;
   color fg;
   color bg;
   
public:
   circle( location start, int radius, color fg = black, color bg = transparent )
      : drawable{ start }, radius{ radius }, fg{ fg }, bg{ bg }
   {}     
   
   void draw( window & w ) override { 

      // don't draw anything when the size would be 0 
      if( radius < 1 ){
         return;       
      }
   
      // http://en.wikipedia.org/wiki/Midpoint_circle_algorithm
   
      int fx = 1 - radius;
      int ddFx = 1;
      int ddFy = -2 * radius;
      int x = 0;
      int y = radius;
    
      // top and bottom
      w.write( start + location( 0, + radius ), fg );
      w.write( start + location( 0, - radius ), fg );

      // left and right 
      w.write( start + location( + radius, 0 ), fg );
      w.write( start + location( - radius, 0 ), fg );
         
      if( bg != transparent ){
   
         // top and bottom
         w.write( start + location( 0, + radius ), fg );
         w.write( start + location( 0, - radius ), fg );

         // left and right
         line(  
		        start - location( radius, 0 ), 
		        start + location( radius, 0 ), 
		        fg 
	       ).draw( w );
      } 
    
      while( x < y ){
      
         // calculate next outer circle point
         if( fx >= 0 ){
           y--;
           ddFy += 2;
           fx += ddFy;
         }
         x++;
         ddFx += 2;
         fx += ddFx;   
                    
         w.write( start + location( + x, + y ), fg );
         w.write( start + location( - x, + y ), fg );
         w.write( start + location( + x, - y ), fg );
         w.write( start + location( - x, - y ), fg );
         w.write( start + location( + y, + x ), fg );
         w.write( start + location( - y, + x ), fg );
         w.write( start + location( + y, - x ), fg );
         w.write( start + location( - y, - x ), fg );
            
         if( bg != transparent  ){
            line( start + location( -x,  y ), start + location(  x,  y ), bg ).draw( w );
            line( start + location( -x, -y ), start + location(  x, -y ), bg ).draw( w );
            line( start + location( -y,  x ), start + location(  y,  x ), bg ).draw( w );
            line( start + location( -y, -x ), start + location(  y, -x ), bg ).draw( w );
         }
      }
   }   
    
}; // class circle

}; // namespace hwlib

#endif // HWLIB_GRAPHICS_H