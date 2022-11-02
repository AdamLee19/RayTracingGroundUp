#ifndef __MATHS__
#define __MATHS__

#include <stdlib.h>

inline double
max(double x0, double x1);

inline double
max(double x0, double x1)
{
	return((x0 > x1) ? x0 : x1);
}


inline int
rand_int(){
	return (rand());
}

inline float
rand_float(){
	return ((float)rand() / (float)RAND_MAX);
}

inline void
set_rand_seed(const int seed){
	srand(seed);
}

#endif
