// HMC_CR: Include guard ifndef.
#include <iostream>
// HMC_CR: AFAICT, iostream is unused in this code.
#include "color.h"

/* simple data representation of an implicit ellipse */
class ellipse {
  public:
	ellipse(double cX, double cY, double r1, double r2, color C) :  
		centerX(cX), centerY(cY), radi1(r1), radi2(r2), inC(C) {}

	double eval(double x, double y) {
		return ( ((centerX-x)*(centerX-x))/(radi1*radi1) + 
				((centerY-y)*(centerY-y))/(radi2*radi2) - 1.0f);
		// HMC_CR: "x - centerX" might make a better match to literature references (though given the squaring, this isn't of functional consequence).
		//
		// HMC_CR: Consider breaking this into multiple sub-expression for readability, e.g.
		// HMC_CR:  // https://en.wikipedia.org/wiki/Ellipse#Shifted_ellipse 
		// HMC_CR:  const float shifted_x = x - centerX;
		// HMC_CR:  const float x2 = shifted_x * shifted_x;
		// HMC_CR:  const float a2 = radi1 * radi1;
		// HMC_CR:  const float shifted_y = y - centerY;
		// HMC_CR:  const float y2 = shifted_y * shifted_y;
		// HMC_CR:  const float b2 = radi2 * radi2;
		// HMC_CR:  return x2 / a2 + y2 / b2 - 1.0f;
	}
	// HMC_CR: It seems like eval can be "const", since we don't expect evaluation to modify the underlying object.
	color getInC() const {return inC; }

  private:
	double centerX, centerY; //center point of ellipse
	double radi1, radi2; //radii of the ellipse
	// HMC_CR: Saving a character each probably isn't worth the readability hit of "radi1" vs "radii1" or "radiiX".
	color inC;
	// HMC_CR: style: Consider adopting a member variable nomenclature (ie, https://google.github.io/styleguide/cppguide.html#Variable_Names, "Class Data Members").
};
