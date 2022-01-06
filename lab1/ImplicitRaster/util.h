#ifndef UTIL_H
#define UTIL_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;
// HMC_CR: Avoid "using" directives in public headers (they transitively affect all includers).

//constants
const double pi = 3.141592653897932385;
const double infinity = std::numeric_limits<double>::infinity();
const double epsilon = 0.001;

inline double degToRad(double degrees) {
	return degrees * pi/180.0;
}

// HMC_CR: It is probably worth describing the range of the returned value (ie, returns [0.0f, 1.0f)...).
// HMC_CR: Is niceRand more descriptively something like "UniformFloat" or "RandomFloatZeroToOne" ?
inline double niceRand() {
 return rand() / (RAND_MAX+1.0);
 // HMC_CR: Consider delegating the range adaptation (here and below) to one of the standard library functions (ie, https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution).
}

inline double nicerRand(double min, double max) {
 return min + (max-min)*niceRand();
}

// HMC_CR: Prefer std::clamp (available since C++17).
inline double clamp(double x, double min, double max) {
  	if (x < min) return min;
  	if (x > max) return max;
	return x;
}

#endif
