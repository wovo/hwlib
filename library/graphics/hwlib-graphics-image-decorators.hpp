// ==========================================================================
//
// File      : hwlib-graphics-image-decorators.hpp
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
// invert
//
// ==========================================================================

/// \cond INTERNAL    


class image_part_t : public image {
private:

   const image & slave;
   const xy start;
   
   color read_implementation( xy pos ) const override {
      return slave[ start + pos ];
   }	  

public:

   constexpr image_part_t( const image & slave, xy start, xy size ):
      image( size ), slave( slave ), start( start ){}
	  
};  


class image_invert_t : public image {
private:

   const image & slave;
   
   color read_implementation( xy pos ) const override {
      return - slave[ pos ];
   }	  

public:

   constexpr image_invert_t( const image & slave ): 
      image( slave.size ), slave( slave ){}
	  
};  


class image_transpose_t : public image {
private:

   const image & slave;
   
   color read_implementation( xy pos ) const override {
      return slave[ transpose( pos ) ];
   }	  

public:

   constexpr image_transpose_t( const image & slave ): 
      image( transpose( slave.size ) ), slave( slave ){}
	  
};  


class image_mirror_x_t : public image {
private:

   const image & slave;
   
   color read_implementation( xy pos ) const override {
      return slave[ xy( slave.size.x - 1 - pos.x, pos.y ) ];
   }	  

public:

   constexpr image_mirror_x_t( const image & slave ): 
      image( slave.size ), slave( slave ){}
	  
};  


class image_mirror_y_t : public image {
private:

   const image & slave;
   
   color read_implementation( xy pos ) const override {
      return slave[ xy( pos.x, slave.size.y - 1 - pos.y ) ];
   }	  

public:

   constexpr image_mirror_y_t( const image & slave ): 
      image( slave.size ), slave( slave ){}
	  
};  

/// \endcond   


// ===========================================================================
//
// constructor functions
//
// ===========================================================================

/// return a part of an image
const image_part_t part( const image & slave, xy start, xy size );

/// invert an image
///
/// This function returns the image, but with the color of 
/// all its pixels inverted.
const image_invert_t invert( const image & slave );

/// return a part of an image
const image_transpose_t transpose( const image & slave );

/// return a part of an image
const image_mirror_x_t mirror_x( const image & slave );

/// return a part of an image
const image_mirror_y_t mirror_y( const image & slave );


// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE 

const image_part_t part( const image & slave, xy start, xy size ){
   return image_part_t( slave, start, size );
}

const image_invert_t invert( const image & slave ){
   return image_invert_t( slave );
}

const image_transpose_t transpose( const image & slave ){
   return image_transpose_t( slave );
}

const image_mirror_x_t mirror_x( const image & slave ){
   return image_mirror_x_t( slave );
}

const image_mirror_y_t mirror_y( const image & slave ){
   return image_mirror_y_t( slave );
}

#endif   


}; // namespace hwlib
