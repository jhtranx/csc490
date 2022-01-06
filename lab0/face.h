#include <iostream>
#include "ellipse.h"

/* simple data representation of a face (collection of ellipses) */
class face {
  public:
	face(ellipse h, ellipse lp, ellipse rp, ellipse ls, ellipse rs, ellipse m) :  
		head(h), lPupil(lp), rPupil(rp), lSclera(ls), rSclera(rs), mouth(m) {}

	double eval(double x, double y) {
		const float shiftx = x - centerX;
		const float shifty = y - centerY;

		return ( (shiftx*shiftx)/(radi1*radi1) + 
				(shifty*shifty)/(radi2*radi2) - 1.0f);
	}
	
	color getInC() const {return inC; }

  private:
    ellipse head;
    ellipse lPupil, rPupil;
    ellipse lSclera, rSclera;
    ellipse mouth;
};