#ifndef COLOR_H
#define COLOR_H

#include <cmath>
#include <iostream>
// HMC_CR: This code doesn't seem to utilize iostream, itself.

#include "util.h"

using std::sqrt;
// HMC_CR: Avoid "using" statements in public headers. This influences the name resolution of any code which (even transitively) includes this header.
// HMC_CR:   (also, sqrt is unused in this header).

/* A color for a PPM file is red, greem blue amounts as whole numbers 0-255 */
// HMC_CR: nit: "greem" -> "green".
// HMC_CR: This class (at the moment) doesn't really have anything to do with PPM; in particular, the referenced range here is unutilized and unenforced (which is fine! But if we're quantizing later, this comment should probably be elsewhere).
class color {
// HMC_CR: style: consider consistent capitalization differentiation for "class" / "struct" types. (ie, "color" -> "Color", https://google.github.io/styleguide/cppguide.html#Type_Names).
public:
		color(double in1, double in2, double in3) : val{in1, in2, in3} {}
		// HMC_CR: Why double, rather than float? For color, even float is usually overkill in terms of precision (though very useful in terms of semantics compared with integral types).
		color() : val{0,0,0} {} //default constructor
		// HMC_CR: super-nit: "0" (integer) -> "0.0" (double).
		color(double in) : val{in,in,in} {} //alt constructor
		// HMC_CR: nit: This would often be called a "broadcast" in similar usage (ie, SIMD / etc).

		//getters
		double r() const { return val[0]; }
		double g() const { return val[1]; }
		double b() const { return val[2]; }
		void setR(double inX) { val[0] = inX; }
		void setG(double inY) { val[1] = inY; }
		void setB(double inZ) { val[2] = inZ; }
		// HMC_CR: These are good, but you might consider some alternatives / additions:
		// HMC_CR: 1. "setR" -> "set_r", for homogeneity / clear differentiation of the name of the member var.
		// HMC_CR: 2. For setting, you might consider a non-const version of "r()", which returns a reference to val[0] (which could then be used to modify it), a la :
		// HMC_CR:   double& r() { return val[0]; }

		//overload operators
		color& operator+=(const color &v) {
			val[0] += v.val[0];
			val[1] += v.val[1];
			val[2] += v.val[2];
			return *this;
		}

		//mult by scalar
		color& operator*=(const double Sc) {
			val[0] *=Sc; 
			val[1] *=Sc;
			val[2] *=Sc;
			return *this;
		}
    // HMC_CR: I would strongly consider rounding these out with general "+" -- both operator+(const color& v) and operator+(double Sc).
		// HMC_CR:   Note that for binary operators of different types, both ordering should be defined (color + double) vs (double + color).
		// HMC_CR:   From personal experience, trying to do "0.5 * vec", compiling, and realizing only "vec * 0.5" was supported is pretty annoying =).
	
		inline static color random() {
			return color(niceRand(), niceRand(), niceRand());
		}
		
		inline static color random(double min, double max) {
			return color(nicerRand(min, max), nicerRand(min, max), nicerRand(min, max));
		}


	private:
		double val[3];
		// HMC_CR: nit: Consider padding out to 4 elements (ie, rgba) (so 16 or 32 bytes) for alignment purposes -- though potentially with a silent / non-functional "a".
		// HMC_CR:   Admittedly, this is more on the optimization side, and can maybe _should_ be omitted in the interested of ease of understanding.
};


#endif
