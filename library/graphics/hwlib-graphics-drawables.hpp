// ==========================================================================
//
// File      : hwlib-graphics-drawables.hpp
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

// ==========================================================================
//
// drawable
//
// ==========================================================================

/// interface to an drawable object
class drawable : public noncopyable {
public:

   /// the location where the object is drawn
   xy start;

   /// create a drawable object by supplying its (initial) location
   drawable( xy start ): start{ start }{}

   /// \brief
   /// interface to draw the object buffered
   /// \details
   /// You must supply the window.
   ///
   /// If buffering is specified, the actual drawing can be delayed
   /// until flush() is called.
   virtual void draw( window & w ) = 0;    

}; // class drawable


// ==========================================================================
//
// line
//
// ==========================================================================

/// a line object                 
class line : public drawable {
private:   
   xy     end;
   color  ink;
   
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
   line( xy start, xy end, color ink = unspecified )
      : drawable{ start }, end{ end }, ink{ ink }
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

         w.write( xy( xDraw, yDraw ), ink );

         if( E > 0 ){
            E += TwoDyTwoDx; //E += 2*Dy - 2*Dx;
            y = y + ystep;
         } else {
            E += TwoDy; //E += 2*Dy;
         }
      }
   }
   
}; // class line   


// ==========================================================================
//
// rectangle
//
// ==========================================================================

/// a rectangle object 
class rectangle : public drawable  {
private:

   xy end;
   color ink;

public:

   rectangle( 
      const xy & start, const xy & end,
      const color & ink = unspecified
   ):
      drawable{ start },
      end( end ), ink( ink )
   {}

   void draw( hwlib::window & w ) override {
      line( 
         xy( start.x, start.y ), xy( start.x,   end.y + 1 ), ink ).draw( w );
      line( 
         xy( end.x,   start.y ), xy( end.x,     end.y + 1 ), ink ).draw( w );
      line( 
         xy( start.x, start.y ), xy( end.x + 1, start.y   ), ink ).draw( w );
      line( 
         xy( start.x, end.y   ), xy( end.x + 1, end.y     ), ink ).draw( w );
   }

};


// ==========================================================================
//
// circle
//
// ==========================================================================

/// a circle object                   
class circle : public drawable {
private:   
   uint_fast16_t  radius;
   color          ink;
   
public:
   /// create a circle object 
   circle( 
      xy start, 
      uint_fast16_t radius, 
      color ink = unspecified
   )
      : drawable{ start }, radius{ radius }, ink{ ink }
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
      w.write( start + xy( 0, + radius ), ink );
      w.write( start + xy( 0, - radius ), ink );

      // left and right 
      w.write( start + xy( + radius, 0 ), ink );
      w.write( start + xy( - radius, 0 ), ink );
         
      // filled circle
      if(0){
   
         // top and bottom
         w.write( start + xy( 0, + radius ), ink );
         w.write( start + xy( 0, - radius ), ink );

         // left and right
         line(  
              start - xy( radius, 0 ), 
              start + xy( radius, 0 ), 
              ink 
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
                    
         w.write( start + xy( + x, + y ), ink );
         w.write( start + xy( - x, + y ), ink );
         w.write( start + xy( + x, - y ), ink );
         w.write( start + xy( - x, - y ), ink );
         w.write( start + xy( + y, + x ), ink );
         w.write( start + xy( - y, + x ), ink );
         w.write( start + xy( + y, - x ), ink );
         w.write( start + xy( - y, - x ), ink );
            
         // filled circle
         if(0) if( ! ink.is_transparent()  ){
            line( 
               start + xy( -x,  y ), 
               start + xy(  x,  y ), 
               ink ).draw( w );
            line( 
               start + xy( -x, -y ), 
               start + xy(  x, -y ), 
               ink ).draw( w );
            line( 
               start + xy( -y,  x ), 
               start + xy(  y,  x ), 
               ink ).draw( w );
            line( 
               start + xy( -y, -x ), 
               start + xy(  y, -x ), 
               ink ).draw( w );
         }
      }
   }   
    
}; // class circle

}; // namespace hwlib
