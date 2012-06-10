/**     ______________________________________
	   /  _______    _______    ________     /\
      /	 / ___  /\  / ___  /\  / ______/\   / /\
     / 	/ /__/ / / / /  / / / / /\_____\/  / / /
    /  / _____/ / / /  / / / / / /        / / /
   /  / /\____\/ / /__/ / / / /_/___     / / /
  /  /_/ /      /______/ / /_______/\   / / /
 /   \_\/       \______\/  \_______\/  / / /
/_____________________________________/ / /
\_____________________________________\/ /
 \_____________________________________\/

**/

#ifndef _MACRO_HEADER
#define _MACRO_HEADER

/** The following macros are used to turn flags on/off, or check if
 * a flag is turned on inside the variable(a). 
 *
**/
#define flagOn(a,b) ( a |= b )
#define flagOff(a,b) ( a &= ~(b) )
#define hasFlag(a,b) ( ((a & b) == b) ? true : false )
#define hasFlags(a,b,c) ( ((a & (b | c)) == (b | c)) ? true : false )
#define excludesFlag(a,b) ( ((a & b) == 0) ? true : false ) //un-tested

#define SWAP(a, b)  {                   \
                        a ^= b;         \
                        b ^= a;         \
                        a ^= b;         \
                    } 
#define PRINT_TOKEN(token) printf(#token " is %d", token)

#endif
