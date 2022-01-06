#include <iostream>
#include "color.h"

/* simple data representation of an implicit ellipse */
class ellipse {
  public:
	ellipse(double cX, double cY, double r1, double r2, color C) :  
		centerX(cX), centerY(cY), radi1(r1), radi2(r2), inC(C) {}

	double eval(double x, double y) {
		const float shiftx = x - centerX;
		const float shifty = y - centerY;

		return ( (shiftx*shiftx)/(radi1*radi1) + 
				(shifty*shifty)/(radi2*radi2) - 1.0f);
	}
	
	color getInC() const {return inC; }

  private:
	double centerX, centerY; //center point of ellipse
	double radi1, radi2; //radii of the ellipse
	color inC;
};