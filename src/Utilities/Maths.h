#ifndef __MATHS__
#define __MATHS__

#include <stdlib.h>

inline double
max(double x0, double x1);

inline double
min(double x0, double x1);

inline int
rand_int();

inline float
rand_float();

inline void
set_rand_seed(const int seed);


inline float 
rand_float(int l, float h);

inline int
rand_int(int l, int h);

// ----------------------------------------------------------------- max
inline double
max(double x0, double x1)
{
	return((x0 > x1) ? x0 : x1);
}

// ----------------------------------------------------------------- min
inline double
min(double x0, double x1) {
	return ((x0 < x1) ? x0 : x1);
}

// ----------------------------------------------------------------- rand_int
inline int
rand_int(){
	return (lrand48());
}

// ----------------------------------------------------------------- rand_float
inline float
rand_float(){
	return (drand48());
}

// ----------------------------------------------------------------- set_rand_seed
inline void
set_rand_seed(const int seed){
	srand(seed);
}

// ----------------------------------------------------------------- rand_float(low, high)
inline float 
rand_float(int l, float h) {
	return (rand_float() * (h - l) + l);
}

// ----------------------------------------------------------------- rand_int(low, high)
inline int
rand_int(int l, int h) {
	return ((int) (rand_float(0, h - l + 1) + l));
}
#endif
