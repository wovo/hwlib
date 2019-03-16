// ==========================================================================
//
// File      : hwlib-graphics.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017
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

/// \brief
/// a pixel coordinate
/// \details
/// This class abstracts a coordinate (pixel location) on a graphics screen,
/// or the distance between two coordinates.
class location final {
public:
   /// x value of the location
   uint_fast16_t x;
   
   /// y value of the location
   uint_fast16_t y;
   
   /// construct a location from its x and y values
   constexpr location( uint_fast16_t x, uint_fast16_t y ): x{ x }, y{ y }{}
   
   /// default constructor
   constexpr location():x{0}, y{0}{}

   /// add two locations
   constexpr location operator+( const location rhs ) const {
      return location{ 
          static_cast< uint_fast16_t >( x + rhs.x ),
          static_cast< uint_fast16_t >( y + rhs.y )
      };      
   }      
   
   /// subtract two locations
   constexpr location operator-( const location rhs ) const {
      return location{ 
          static_cast< uint_fast16_t >( x - rhs.x ),
          static_cast< uint_fast16_t >( y - rhs.y )
      };         
   }      

   /// divide a location  by an integer
   constexpr location operator/( const uint_fast16_t rhs ) const {
      return location{ 
          static_cast< uint_fast16_t >( x / rhs ),
          static_cast< uint_fast16_t >( y / rhs )
      };         
   }      

}; 

/// print a location
ostream & operator<<( ostream & lhs, location rhs );
#ifdef HWLIB_ONCE
ostream & operator<<( ostream & lhs, location rhs ){
   return lhs << "[" << rhs.x << ":" << rhs.y << "]";
}
#endif

/// \brief
/// graphics color
/// \details
/// This class abstracts a color as used in a graphics window.
/// A color is represented by 3 RGB bytes an a transparency flag.
class color final {
private:    
              
   static constexpr uint8_t clip( uint_fast16_t x, bool transparent = false ){
      return ( transparent )
         ? 0
         : ( x < 0 ) 
            ? 0 
            : ( x > 0xFF ? 0xFF : x ); 
   }   
      
public:

   /// \brief
   /// the transparency of the color
   /// \details
   /// When a color is tranparent, the read green and blue atrributes
   /// are meaningless.
   bool is_transparent;
   
   /// the RED attribute (part) of the color
   uint8_t red;
      
   /// the GREEN attribute (part) of the color
   uint8_t green;
      
   /// the BLUE attribute (part) of the color
   uint8_t blue;
   
   /// \brief
   /// the 3-byte RGB representation of the color
   /// \details
   /// This function returns the RGB reprsentation of the color.
   /// For a transparent color, the returned value will 
   /// not be meaningfull.
   uint_fast32_t rgb() const {
      return ( static_cast< uint_fast32_t >( red )   << 16 )
           | ( static_cast< uint_fast32_t >( green ) << 8  )
           | ( static_cast< uint_fast32_t >( blue )  << 0  );
   }
   
   /// \brief
   /// construct a color from its RGB components
   /// \details
   /// The transparency flag can be specified, but better use
   /// the transparent constant.
   /// 
   /// The arguments are integers, but they are clipped
   /// to the 0..255 range by the constructor.   
   constexpr color( 
      uint8_t red, 
      uint8_t green, 
      uint8_t blue, 
      bool transparent = false 
   ): 
      is_transparent{ transparent },
      red{   clip( red,   transparent ) }, 
      green{ clip( green, transparent ) }, 
      blue{  clip( blue,  transparent ) }
   {}   
   
   /// \brief
   /// constructs a color from a three-byte integer value
   /// \details
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
         0xFF - static_cast< uint8_t >( red ), 
         0xFF - static_cast< uint8_t >( green ), 
         0xFF - static_cast< uint8_t >( blue ), 
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
   
/// \brief
/// an image
/// \details
/// An image is a rectangular set of pixel values (colors).
class image {
private:

   virtual color get_implementation( location pos ) const = 0;

public:

   /// \brief
   /// the size of the image
   /// \details
   /// This is the size of the image: the number of pixels
   /// in the x and y direction.
   // wovo: should be const, but that conflicts with the 16x16 font
   const location size;

   /// construct an image by specifying its size.
   constexpr image( location size)
      : size{ size }
   {}

   /// return the coclor at the specified location
   color operator[]( location pos ) const {
      return (
               ( pos.x >= 0 ) && ( pos.x < size.x )
            && ( pos.y >= 0 ) && ( pos.y < size.y )
         )
            ? get_implementation( pos )
            : black;
   }

};

/// an 8x8 pixel image that contains its pixels
class image_8x8 : public image {
private:
   unsigned char data[ 8 ];

   color get_implementation( location pos ) const override {
      return
         ( data[ pos.y ] & ( 0x01 << pos.x )) == 0
            ? white
            : black;
   }

public:

   /// \brief
   /// create the image_8x8 by supplying the pixels
   /// \details
   /// The d0 argument contains the top row, bit 0 is the leftmost pixel.
   constexpr image_8x8(
      unsigned char d0, unsigned char d1,
      unsigned char d2, unsigned char d3,
      unsigned char d4, unsigned char d5,
      unsigned char d6, unsigned char d7
   ):
      image( location( 8, 8 ) ),
      data{ d0, d1, d2, d3, d4, d5, d6, d7 }
   {}
};


// ==========================================================================

/// \brief
/// a font
/// \details
/// A font provides an image for each supported character
class font {
public:

   /// \brief
   /// get image for a character
   /// \details
   /// This function returns the image for the specified character.
   virtual const image & operator[]( char c ) const = 0;
};


// ==========================================================================


/// \brief
/// a graphics window
/// \details
/// This class abstracts the interface to a graphic window.
class window {
private:

   /// \brief
   /// write a pixel - implementation
   /// \details
   /// This NVI function writes a the color col to the pixel at location loc.
   /// Loc is guaranteed to be within the window, and the color
   /// is guranteed to be not transparent.
   ///
   /// When buffering is specified ( buf == buffered ) the actual writing
   /// can be delayed until the next flush() call.
   virtual void write_implementation( 
      location pos, 
      color col
   ) = 0;      
   
public:
   /// \brief
   /// the size of the window
   /// \details
   /// This is the size of the window: the number of pixels
   /// in the x and y direction.
   const location size;
   
   /// \brief
   /// the foreground color of the window
   /// \details
   /// This color could be used to draw graphics.
   color foreground;
   
   /// \brief
   /// the background color of the window
   /// \details
   /// This is the color use by the clear() function.
   color background;
   
   /// construct a window by specifying its size and foreground and background colors.
   window( location size, color foreground, color background )
      : size{ size }, foreground{ foreground }, background{ background }
   {}
   
   /// \brief
   /// write a pixel
   /// \details
   /// This function writes a the color col to the pixel at location loc.
   /// If either the color is transparent, or the location is outside the window 
   /// the call has no effect. When no color is specificied, the window's
   /// foreground color is used.
   ///
   /// When buffering is specified ( buf == buffered ) the actual writing
   /// can be delayed until the next flush() call.   
   void write( 
      location pos, 
      color col 
   ){
      if(  ( ! col.is_transparent )
        && ( pos.x >= 0 ) && ( pos.x < size.x ) 
        && ( pos.y >= 0 ) && ( pos.y < size.y ) 
      ){
         write_implementation( pos, col );
      }   
   }
   
   /// \brief
   /// flush the pixel buffer
   /// \details
   /// This function fluhses the pixel buffer: it writes pixels that
   /// have not yet been written.
   /// Flushing might occur as a side-effect of other operations.
   virtual void flush(){ }
   
   /// \brief
   /// write a rectangle of pixels
   /// \details
   /// This function writes a rectangle of pixels, as specified by img,
   /// at location pos.        
   ///
   /// When buffering is specified ( buf == buffered ) the actual writing
   /// can be delayed until the next flush() call.   
   void write( 
      location pos, 
      const image & img
   ){                 
      for( uint_fast16_t x = 0; x < img.size.x; ++x ){
         for( uint_fast16_t y = 0; y < img.size.y; ++y ){
            auto loc = hwlib::location( x, y );
            write( pos + loc, img[ loc ] );
         }
      }
   }

   #ifndef DOXYGEN // hide from doxygen
   void write( location pos ){
      write( pos, foreground );
   }   
   #endif 
   
   /// \brief
   /// clear the window
   /// \details
   /// This function clears the windows by writing the background
   /// color to all pixels.
   /// The default implementation writes to all pixels in sequence.
   /// A concrete window can probably provide a faster implementation.
   ///
   /// When buffering is specified ( buf == buffered ) the actual clearing
   /// can be delayed until the next flush() call.    
   virtual void clear( ){
      for( uint_fast16_t x = 0; x < size.x; ++x ){
         for( uint_fast16_t y = 0; y < size.y; ++y ){
            write( location{ x, y }, background );    
         }                 
      }        
   }
   
};


// ==========================================================================

/// implements a console inside graphic window
class window_ostream : public console {
private:
   window & w;
   const font &f;
   location cursor;

   uint_fast16_t x_size( const window & w, const font &f ){
      const image & im = f[ ' ' ];
      return w.size.x / im.size.x;
   }
   uint_fast16_t y_size( const window & w, const font &f ){
      const image & im = f[ ' ' ];
      return w.size.y / im.size.y;
   }

   void goto_xy_implementation( uint_fast16_t x, uint_fast16_t y ) override {
      const image & im = f[ ' ' ];
      cursor.x = x * im.size.x;
      cursor.y = y * im.size.y;
   }

   void putc_implementation( char c ) override {
      const image & im = f[ c ];

      w.write( cursor, im );
      cursor.x += im.size.x;
   }

   void clear() override {
      w.clear();
      goto_xy( 0, 0 );
   }

   void flush() override {
      w.flush();
   }

public:
   /// construct an console from a window and a font
   window_ostream( window & w, const font &f ):
      console( x_size( w, f ), y_size( w, f ) ), w( w ), f( f ), cursor( 0, 0 )
   { }
};


// ==========================================================================

/// \brief
/// a window_part (subwindow of a larger window)
/// \details
/// A window_part is a rectangular part of a larger window.
class window_part : public window {
private:
   window & w;
   location start;
   
   void write_implementation( location pos, color col ) override {
      w.write( start + pos, col );
   }      

   void flush() override {
      w.flush();
   }      
   
public:      
   /// \brief
   /// create a window_part from a larger window, its origin and its size
   /// \details
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

/// \brief
/// window_invert (invert writes to a window)
/// \details
/// A window_inverts writes inverted to its larger window.
class window_invert : public window {
private:
   window & w;
   
   void write_implementation( 
      location pos, 
      color col
   ) override {
      w.write( pos, - col );
   }      

   void flush() override {
      w.flush();
   }      
   
public:      
   /// \brief
   /// create a window_invert from a window
   /// \details
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

/// interface to an drawable object
class drawable {
public:

   /// the location where the object is drawn
   location start;

   /// create a drawable object by bsupplying its (initial) location
   drawable( location start ): start{ start }{}

   /// \brief
   /// interface to draw the object buffered
   /// \details
   /// You must supply the window.
   ///
   /// If buffering is specified, the actuial drawing can be delayed
   /// until flush() is aclled.
   virtual void draw( window & w ) = 0;    

};

/// a line object                 
class line : public drawable {
private:   
   location end;
   color fg;
   
   static void swap( int_fast16_t & a, int_fast16_t & b ){
      auto t = a; 
      a = b;
      b = t;
   }

   static int_fast16_t abs( int_fast16_t x ){
      return x >= 0 ? x : -x;
   }

public:
   /// create a line object
   line( location start, location end, color fg = black )
      : drawable{ start }, end{ end }, fg{ fg }
   {}   
   
   void draw( window & w ) override { 
       
      int_fast16_t x0 = start.x;
      int_fast16_t y0 = start.y;
      int_fast16_t x1 = end.x; 
      int_fast16_t y1 = end.y;
                   
      // http://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
      // http://homepages.enterprise.net/murphy/thickline/index.html
     
      int_fast16_t Dx = x1 - x0; 
      int_fast16_t Dy = y1 - y0;
   
      int_fast16_t steep = (abs(Dy) >= abs(Dx));
   
      if( steep ){
         swap( x0, y0 );
         swap( x1, y1 );
      
         // recompute Dx, Dy after swap
         Dx = x1 - x0;
         Dy = y1 - y0;
      }
   
      int_fast16_t xstep = 1;
      if( Dx < 0 ){
         xstep = -1;
         Dx = -Dx;
      }
   
      int_fast16_t ystep = 1;
      if( Dy < 0 ){
         ystep = -1;    
         Dy = -Dy; 
      }
      int_fast16_t TwoDy = 2*Dy; 
      int_fast16_t TwoDyTwoDx = TwoDy - 2*Dx; // 2*Dy - 2*Dx
      int_fast16_t E = TwoDy - Dx; //2*Dy - Dx
      int_fast16_t y = y0;
      int_fast16_t xDraw, yDraw, x;  
      for( x = x0; x != x1; x += xstep ){    
         if (steep) {     
            xDraw = y;
            yDraw = x;
         } else {     
            xDraw = x;
            yDraw = y;
         }

         w.write( location( xDraw, yDraw ), fg );

         if( E > 0 ){
            E += TwoDyTwoDx; //E += 2*Dy - 2*Dx;
            y = y + ystep;
         } else {
            E += TwoDy; //E += 2*Dy;
         }
      }
   }
   
}; // class line   


/// a circle object                   
class circle : public drawable {
private:   
   uint_fast16_t radius;
   color fg;
   color bg;
   
public:
   /// create a circle object
   circle( location start, uint_fast16_t radius, color fg = black, color bg = transparent )
      : drawable{ start }, radius{ radius }, fg{ fg }, bg{ bg }
   {}     
   
   void draw( window & w ) override { 

      // don't draw anything when the size would be 0 
      if( radius < 1 ){
         return;       
      }
   
      // http://en.wikipedia.org/wiki/Midpoint_circle_algorithm
   
      int_fast16_t fx = 1 - radius;
      int_fast16_t ddFx = 1;
      int_fast16_t ddFy = -2 * radius;
      int_fast16_t x = 0;
      int_fast16_t y = radius;
    
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
            line( 
               start + location( -x,  y ), 
               start + location(  x,  y ), 
               bg ).draw( w );
            line( 
               start + location( -x, -y ), 
               start + location(  x, -y ), 
               bg ).draw( w );
            line( 
               start + location( -y,  x ), 
               start + location(  y,  x ), 
               bg ).draw( w );
            line( 
               start + location( -y, -x ), 
               start + location(  y, -x ), 
               bg ).draw( w );
         }
      }
   }   
    
}; // class circle

}; // namespace hwlib
