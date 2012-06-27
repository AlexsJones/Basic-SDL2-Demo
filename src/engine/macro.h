#ifndef _MACRO_HEADER
#define _MACRO_HEADER

/** The following macros are used to turn flags on/off, or check if
 *  a flag is turned on inside the variable(a).
 *  
 *  Pretty much the only helpful one is hasFlag(). These are used extensibly
 *  for checking the ACTION flags which wil be changed soon.
 *  SO:
 *  TODO::REMOVE ALL OF THEM!!
**/
#define flagOn(a,b) ( a |= b )
#define flagOff(a,b) ( a &= ~(b) )
#define hasFlag(a,b) ( ((a & b) == b) ? true : false )
#define hasFlags(a,b,c) ( ((a & (b | c)) == (b | c)) ? true : false )
#define excludesFlag(a,b) ( ((a & b) == 0) ? true : false ) //un-tested

// Experimental:
#define PRINT_TOKEN(token) printf(#token " is %d", token)

#endif
