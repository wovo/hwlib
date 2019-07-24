// ==========================================================================
//
// File      : hwlib-glcd-oled.hpp
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
   

/// \brief
/// Oled B/W graphics LCD
/// \details
/// This class implements an interface to an 128 x 64 pixel
/// monochrome (on/off) OLED display. These displays are available
/// in various colcors (green, red, white, etc.).
/// The interface is I2C.
/// The driver chip is an SSD1306.
///
/// The interface is buffered: all writes
/// are buffered in memory until flush() is called.
///
/// When the PCB has regulator (3-legged component) the power can be 3 - 5V. 
/// If it hasn't, you can use only 3.3V.
///
/// There are variations of this display with more pins, which 
/// have more interface options (SPI as alternative interface).
///
/// This type of display is reasonably priced 
/// and available from lots of sources.
///
/// \image html oled.jpg
//

/// SSD1306 chip commands
enum class ssd1306_commands : uint8_t {
   set_contrast                          = 0x81,
   display_all_on_resume                 = 0xa4,
   display_all_on                        = 0xa5,
   normal_display                        = 0xa6,
   invert_display                        = 0xa7,
   display_off                           = 0xae,
   display_on                            = 0xaf,
   set_display_offset                    = 0xd3,
   set_compins                           = 0xda,
   set_vcom_detect                       = 0xdb,
   set_display_clock_div                 = 0xd5,
   set_precharge                         = 0xd9,
   set_multiplex                         = 0xa8,
   set_low_column                        = 0x00,
   set_high_column                       = 0x10,
   set_start_line                        = 0x40,
   memory_mode                           = 0x20,
   column_addr                           = 0x21,
   page_addr                             = 0x22,
   com_scan_inc                          = 0xc0,
   com_scan_dec                          = 0xc8,
   seg_remap                             = 0xa0,
   charge_pump                           = 0x8d,
   external_vcc                          = 0x01,
   switch_cap_vcc                        = 0x02,
   activate_scroll                       = 0x2f,
   deactivate_scroll                     = 0x2e,
   set_vertical_scroll_area              = 0xa3,
   right_horizontal_scroll               = 0x26,
   left_horizontal_scroll                = 0x27,
   vertical_and_right_horizontal_scroll  = 0x29,
   vertical_and_left_horizontal_scroll   = 0x2A   
};   

/// value to send over i2c before a command
constexpr uint8_t ssd1306_cmd_prefix  = 0x80;

/// value to send over i2c before a command
constexpr uint8_t ssd1306_data_prefix = 0x40;

/// SSD1306 chip initialization
constexpr const uint8_t ssd1306_initialization[] = {
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::display_off,                  
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::set_display_clock_div, 0x80,
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::set_multiplex,         0x3f,   
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::set_display_offset,    0x00,   
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::set_start_line       | 0x00,  
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::charge_pump,           0x14,   
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::memory_mode,           0x00,   
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::seg_remap            | 0x01,
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::com_scan_dec,
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::set_compins,           0x12,   
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::set_contrast,          0xcf,   
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::set_precharge,         0xf1,  
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::set_vcom_detect,       0x40,   
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::display_all_on_resume,          
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::normal_display,                
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::display_on                     
};


// ==========================================================================
//
// ssd1306, accessed by i2c
//
// ==========================================================================

class ssd1306_i2c {
protected:

   /// the i2c channel
   i2c_bus & bus;
   uint_fast8_t address;
   
   /// current cursor location in the controller
   xy cursor;
	   
public:	
    
   /// construct by providing the i2c channel	
   ssd1306_i2c( i2c_bus & bus, uint_fast8_t address = 0x3C ):
      bus( bus ),
      address( address ),
	   cursor( 255, 255 )
   {
      // wait for the controller to be ready for the initialization       
      wait_ms( 20 );
   }      
   
   /// send a command without data
   void command( ssd1306_commands c ){
      uint8_t data[] = { 
         ssd1306_cmd_prefix, (uint8_t) c 
      };
      bus.write( address ).write( 
         data, 
         sizeof( data ) / sizeof( uint8_t ) 
      );      
   } 
   
   /// send a command with one data byte
   void command( ssd1306_commands c, uint8_t d0 ){
      uint8_t data[] = { 
         ssd1306_cmd_prefix, (uint8_t) c, 
         ssd1306_cmd_prefix, d0 
      };
      bus.write( address ).write( 
         data, 
         sizeof( data ) / sizeof( uint8_t ) 
      );    
   } 	
   
   /// send a command with two data bytes
   void command( ssd1306_commands c , uint8_t d0, uint8_t d1 ){
      uint8_t data[] = { 
         ssd1306_cmd_prefix, (uint8_t) c, 
         ssd1306_cmd_prefix, d0, 
         ssd1306_cmd_prefix, d1 
      };
      bus.write( address ).write( 
         data, 
         sizeof( data ) / sizeof( uint8_t ) 
      );     
   } 	
  
   /// write the pixel byte d at column x page y
   void pixels_byte_write( 
      xy location,
      uint8_t d 
   ){

      if( location != cursor ){
         command( ssd1306_commands::column_addr,  location.x,  127 );
         command( ssd1306_commands::page_addr,    location.y,    7 );
         cursor = location;
      }   

      uint8_t data[] = { ssd1306_data_prefix, d };
      bus.write( address ).write( 
         data, 
         sizeof( data ) / sizeof( uint8_t ) 
      ); 
      cursor.x++;  
    
   }
      
}; // class ssd1306_i2c


// ==========================================================================
//
// ssd1306, accessed by spi
//
// ==========================================================================

class ssd1306_spi_res_dc_cs {
protected:

   // the spi bus & pins
   spi_bus & bus;
   pin_out & res;
   pin_out & dc;
   pin_out & cs;
   
   // current cursor location in the controller
   xy cursor;
	   
public:	
    
   /// construct by providing the spi bus and the res, dc and cs pins	
   ssd1306_spi_res_dc_cs( spi_bus & bus, pin_out & res, pin_out & dc, pin_out & cs ):
      bus( bus ),
      res( res ),
      dc( dc ),
      cs( cs ),
	   cursor( 255, 255 )
   {
      res.write( 0 );
      wait_ms( 1 );      
      res.write( 1 );
      
      // wait for the controller to be ready for the initialization       
      wait_ms( 20 );
   }      
   
   /// send a command without data
   void command( ssd1306_commands c ){
      dc.write( 0 );
      auto t = bus.transaction( cs );
      t.write( static_cast< uint8_t >( c ) );      
   } 
   
   /// send a command with one data byte
   void command( ssd1306_commands c, uint8_t d0 ){
      dc.write( 0 );
      auto t = bus.transaction( cs );
      t.write( static_cast< uint8_t >( c ) );      
      t.write( d0 );      
   } 	
   
   /// send a command with two data bytes
   void command( ssd1306_commands c , uint8_t d0, uint8_t d1 ){
      dc.write( 0 );
      auto t = bus.transaction( cs );
      t.write( static_cast< uint8_t >( c ) );      
      t.write( d0 );      
      t.write( d1 );      
   } 	
   
   /// write the pixel byte d at column x page y
   void pixels_byte_write( 
      xy location,
      uint8_t d 
   ){

      if( location != cursor ){
         command( ssd1306_commands::column_addr,  location.x,  127 );
         command( ssd1306_commands::page_addr,    location.y,    7 );
         cursor = location;
      }   

      dc.write( 1 );
      auto t = bus.transaction( cs );
      t.write( d );
      cursor.x++;  
    
   }
      
}; // class ssd1306_spi


// ==========================================================================
//
// direct i2c
//
// ==========================================================================

/// buffered oled window
class glcd_oled_i2c_128x64_direct : public ssd1306_i2c, public window {
private:

   static auto constexpr wsize = xy( 128, 64 );

   uint8_t buffer[ wsize.x * wsize.y / 8 ];
      
   void write_implementation( 
      xy pos, 
      color col
   ) override {

      int a = pos.x + ( pos.y / 8 ) * size.x;
      
      if( col == white ){ 
         buffer[ a ] |=  ( 0x01 << ( pos.y % 8 ));  
      } else {
         buffer[ a ] &= ~( 0x01 << ( pos.y % 8 )); 
      }   

      pixels_byte_write( xy( pos.x, pos.y / 8 ), buffer[ a ] );   

   }   
   
   void clear_implementation( color c ) override {
      const uint8_t d = ( c == white ) ? 0xFF : 0x00;
      command( ssd1306_commands::column_addr,  0,  127 );
      command( ssd1306_commands::page_addr,    0,    7 );  
      auto t = bus.write( address );
      t.write( ssd1306_data_prefix );
      for( uint_fast16_t x = 0; x < sizeof( buffer ); ++x ){                
	      buffer[ x ] = d;
		   t.write( d );
      }        
	  cursor = xy( 255, 255 );
   }   
     
public:
   
   /// construct by providing the i2c channel
   glcd_oled_i2c_128x64_direct( i2c_bus & bus, uint_fast8_t address = 0x3C ): 
      ssd1306_i2c( bus, address ),
      window( wsize, white, black )
   {
      bus.write( address ).write( 
         ssd1306_initialization, 
         sizeof( ssd1306_initialization ) / sizeof( uint8_t ) 
      );     
   }
   
   void flush() override {}  

}; // class glcd_oled_i2c_128x64_direct


// ==========================================================================
//
// direct spi
//
// ==========================================================================

/// buffered oled window
class glcd_oled_spi_128x64_direct_res_dc_cs : 
   public ssd1306_spi_res_dc_cs, 
   public window 
{
private:

   static auto constexpr wsize = xy( 128, 64 );

   uint8_t buffer[ wsize.x * wsize.y / 8 ];
      
   void write_implementation( 
      xy pos, 
      color col
   ) override {

      int a = pos.x + ( pos.y / 8 ) * size.x;
      
      if( col == white ){ 
         buffer[ a ] |=  ( 0x01 << ( pos.y % 8 ));  
      } else {
         buffer[ a ] &= ~( 0x01 << ( pos.y % 8 )); 
      }   

      pixels_byte_write( xy( pos.x, pos.y / 8 ), buffer[ a ] );   

   }   
     
public:
   
   /// construct by providing the i2c channel
   glcd_oled_spi_128x64_direct_res_dc_cs( spi_bus & bus, pin_out & res, pin_out & dc, pin_out & cs ):
      ssd1306_spi_res_dc_cs( bus, res, dc, cs ),
      window( wsize, white, black )
   {
      command( ssd1306_commands::display_off );
      command( ssd1306_commands::set_display_clock_div, 0x80 );
      command( ssd1306_commands::set_multiplex,         0x3f ); 
      command( ssd1306_commands::set_display_offset,    0x00 ); 
      command( (ssd1306_commands) (((int) ssd1306_commands::set_start_line )      | 0x00 ));
      command( ssd1306_commands::charge_pump,           0x14 );   
      command( ssd1306_commands::memory_mode,           0x00 );   
      command( (ssd1306_commands) (((int)  ssd1306_commands::seg_remap  )          | 0x01 ));
      command( ssd1306_commands::com_scan_dec );
      command( ssd1306_commands::set_compins,           0x12 );
      command( ssd1306_commands::set_contrast,          0xcf ); 
      command( ssd1306_commands::set_precharge,         0xf1 );
      command( ssd1306_commands::set_vcom_detect,       0x40 );
      command( ssd1306_commands::display_all_on_resume );  
      command( ssd1306_commands::normal_display );
      command( ssd1306_commands::display_on );
      
   }
   
   void clear_implementation(  color c ) override {
      const uint8_t d = ( c == white ) ? 0xFF : 0x00;
      command( ssd1306_commands::column_addr,  0,  127 );
      command( ssd1306_commands::page_addr,    0,    7 );  
      auto t = bus.transaction( cs );
      t.write( ssd1306_data_prefix );
      for( uint_fast16_t x = 0; x < sizeof( buffer ); ++x ){                
	      buffer[ x ] = d;
		   t.write( d );
      }        
	  cursor = xy( 255, 255 );
   }
   
   void flush() override {}  


}; // class glcd_oled_i2c_128x64_direct


// ==========================================================================
//
// buffered
//
// ==========================================================================

/// buffered oled window
class glcd_oled_i2c_128x64_buffered : public ssd1306_i2c, public window {
private:

   static auto constexpr wsize = xy( 128, 64 );

   uint8_t buffer[ wsize.x * wsize.y / 8 ];
         
   void write_implementation( 
      xy pos, 
      color col
   ) override {
      int a = pos.x + ( pos.y / 8 ) * size.x;

      if( col == white ){ 
         buffer[ a ] |=  ( 0x01 << (pos.y % 8 ));  
      } else {
         buffer[ a ] &= ~( 0x01 << ( pos.y % 8 )); 
      }   
   }   
     
public:
   
   /// construct by providing the i2c channel
   glcd_oled_i2c_128x64_buffered( i2c_bus & bus, int address = 0x3C ):
      ssd1306_i2c( bus, address ),
      window( wsize, white, black )
   {
      bus.write( address ).write( 
         ssd1306_initialization, 
         sizeof( ssd1306_initialization ) / sizeof( uint8_t ) 
      );     
   }
   
   void flush() override {
      command( ssd1306_commands::column_addr,  0,  127 );
      command( ssd1306_commands::page_addr,    0,    7 );   
      if(0) for( int y = 0; y < 64 / 8; y++ ){
         for( int x = 0; x < 128; x++ ){
            uint8_t d = buffer[ x + 128 * y ];
            uint8_t data[] = { 0x40, d };
            bus.write( address ).write( 
               data, 
               sizeof( data ) / sizeof( uint8_t ) 
            );
         }   
		 
		 // yield the CPU when this is run with an I2C implementation 
		 // that doesn't ever wait, to
		 //    - prevent polling timing from missing an overflow
		 //    - keep other threads in a in a multi-threading context alive
         wait_us( 0 );		 
      }  
      //for( int y = 0; y < 64 / 8; y++ ){
         auto t = bus.write( address );
         t.write( ssd1306_data_prefix );
         t.write( buffer, sizeof( buffer ) / sizeof( uint8_t )  );
      //}   
   }     
   
}; // class glcd_oled_i2c_128x64_buffered

// ==========================================================================
//
// fast buffered
//
// ==========================================================================

/// buffered oled window
class glcd_oled_i2c_128x64_fast_buffered : public ssd1306_i2c, public window {
private:

   static auto constexpr wsize = xy( 128, 64 );
   
   static auto constexpr buf_size = wsize.x * wsize.y / 8;

   uint8_t buffer[ buf_size  ];
   bool     dirty[ buf_size ];
         
   void write_implementation( 
      xy pos, 
      color col
   ) override {
      int a = pos.x + ( pos.y / 8 ) * size.x;

      if( col == white ){ 
         buffer[ a ] |=  ( 0x01 << (pos.y % 8 ));  
      } else {
         buffer[ a ] &= ~( 0x01 << ( pos.y % 8 )); 
      }   
      
      dirty[ a ] = true;
   }   
     
public:
   
   /// construct by providing the i2c channel
   glcd_oled_i2c_128x64_fast_buffered( i2c_bus & bus, int address = 0x3C ):
      ssd1306_i2c( bus, address ),
      window( wsize, white, black )
   {
      bus.write( address ).write( 
         ssd1306_initialization, 
         sizeof( ssd1306_initialization ) / sizeof( uint8_t ) 
      );     
   }
   
   void flush() override {
      unsigned int start = 0;
      while( start < buf_size ){
         
         // find first/next dirty pixel
         while( !dirty[ start ] ){ 
            ++start;
            if( start == buf_size ){ 
               // no dirty pixels: nothing to do
               return;
            }               
         }    
         
         // find the extent of the next message
         unsigned int tail    = start;
         unsigned int cursor  = start;
         unsigned int gap     = 0;
         for(;;){
            if( dirty[ cursor ] ){
               gap = 0;
               tail = cursor;
               dirty[ cursor ] = false;
            } else {                 
               // if gap larger than 10: flush upto last visited dirty pixel
               if( ++gap > 10 ){
                  break;
               }                  
            }   
            ++cursor;
            // if end of buffer: flush 
            if( cursor == buf_size ){
               break;
            }               
         }            
         
         command( ssd1306_commands::column_addr,  start % wsize.x,  127 );
         command( ssd1306_commands::page_addr,    start / wsize.x,    7 );   
         auto t = bus.write( address );
         t.write( ssd1306_data_prefix );
         t.write( & buffer[ start ], 1 + ( tail - start ) );
      }
   }     
   
}; // class glcd_oled_i2c_128x64_fast_buffered

using glcd_oled = glcd_oled_i2c_128x64_buffered;

}; // namespace hwlib
