#ifndef PPM_H
#define PPM_H

#include <math.h>
#include "color.h"
// HMC_CR: Include some form of ostream, for ostream type.

using namespace std;

class ppmR  {

	public:
		ppmR(int w, int h) : width(w), height(h) {}

	    void writePixel(ostream& out, int x, int y, color cOut) const;
	    void writeHeader(ostream& out) const;
	    void writeNewLine(ostream& out) const;
		// HMC_CR: style: indentation

	public:
		int width;
		int height;
		// HMC_CR: style: member var naming?
};

void ppmR::writePixel(ostream& out, int x, int y, color cOut) const {

 	out << static_cast<int>(clamp(cOut.r(), 0.0, 255)) << " "
 					<< static_cast<int>(clamp(cOut.g(), 0.0, 255)) << " "
 					<< static_cast<int>(clamp(cOut.b(), 0.0, 255)) << endl; 
	// HMC_CR: Be particularly careful with respect to the types here. I usually find (though perhaps it is due to the compiler options I'm usually under) that clamp is particularly sensitive to type mismatches between arguments -- ie, 255 -> 255.0, if the type of cOut.{r,g, b}() is double.
	// HMC_CR:  I discovered after my initial reading that that "clamp" is actually defined in "util.h" -- this is type of ambiguity that "using namespace std" introduces, which can make things ambiguous for readers.
	// HMC_CR:  If the version from "util.h" is desired here, it should be included from this file, rather relying upon transitive inclusion via color.h.
 		
}

void ppmR::writeNewLine(ostream& out) const {
 	out << "\n"; 
 }

void ppmR::writeHeader(ostream& out) const {
	//PPM format header
 	out << "P3\n" << width << " " << height << "\n255\n"; 
 }

#endif


