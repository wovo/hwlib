#include <iostream>

#define four

#ifdef one

class xy {
public:    
   int x, y;
   xy( int x, int y ): x( x ), y( y ){}
   xy add( xy rhs ){ 
       return xy( x + rhs.x, y + rhs.y ); 
   }
};
   
void f(){   
   auto a = xy( 1, 2 );
   auto b = xy( 3, 4 );
   auto c =  a.add( b );
   (void)c;
}

#endif

#ifdef two

struct xy {
   int x, y;
};
   
xy add( xy * this_, xy rhs ){ 
   return xy{ this_->x + rhs.x, this_->y + rhs.y }; 
}

void f(){   
   xy a{ 1, 2 };
   xy b{ 3, 4 };
   xy c = add( &a, b );
   (void)c;
}

#endif

#ifdef three

class xy {
public:    
   int x, y;
   xy( int x, int y ): x( x ), y( y ){}
   virtual void print() = 0;
};

class my_xy : public xy {
public:    
   my_xy( int x, int y ): xy( x, y ){}
   void print() override { std::cout<< "[" << x << "," << y << "]"; }
};
   
void f(){   
   auto a = my_xy( 1, 2 );
   a.print();
}

#endif

#ifdef four

struct xy_functions;

struct xy {
   int x, y;
   const xy_functions *vft;
   xy( int x, int y, const xy_functions *vft ): x( x ), y( y ), vft( vft ){}
};

struct xy_functions {
   void (*print)( xy * );
};

void my_xy_print( xy * this_){ 
   std::cout<< "[" << this_->x << "," << this_->y << "]"; 
};

const xy_functions my_xy_vft = { my_xy_print };

struct my_xy : xy {
   my_xy( int x, int y ): xy( x, y, & my_xy_vft ){}
};
   
void f(){   
   auto a = my_xy( 42, 84 );
   (( xy_functions * ) a.vft )->print( & a );
}

#endif



int main(){
   f();
   std::cout << "\n";
}

   
