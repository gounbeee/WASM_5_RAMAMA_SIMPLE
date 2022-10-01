#ifndef INCLUDE_GUARD_GLOBALMATH_H
#define INCLUDE_GUARD_GLOBALMATH_H


static unsigned int remap( unsigned int val, unsigned int old_low, unsigned int old_high, unsigned int new_low , unsigned int new_high ) {
	return ( old_high*new_low - old_low*new_high - val*( new_low - new_high ) ) / (old_high - old_low );
}




#endif



