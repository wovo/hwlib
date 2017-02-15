// This file supplies the BMPTK stack space variable.
//
// The size is specified by the STACK_SIZE command line argument.
// NATIVE means do not create a stack, the native stack is used.
// supply a dummy size to make the compilation successful.
// AUTOMATIC means calculate the required stack size and allocate a stack 
// of that size, but the application must first be linked, and for that 
// a dummy stack must be used to make the compilation successful.
unsigned char bmptk_stack[ 73728 ]
   __attribute__ (( section( ".bmptk_stack" )));
