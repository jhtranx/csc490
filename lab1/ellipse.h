#include <iostream>
#include "color.h"
#include "vec2.h"

/* simple data representation of an implicit ellipse */
class ellipse {
  public:
	ellipse(vec2 p, double r1, double r2, color C) : 
		center(p), radii1(r1), radii2(r2), inC(C), depth(0) {}
	ellipse(vec2 p, double r1, double r2, color C, double d) : 
		center(p), radii1(r1), radii2(r2), inC(C), depth(d) {}

	double const eval(double x, double y) {
		// return ( ((center.x()-x)*(center.x()-x))/(radi1*radi1) + 
		// 		((center.y()-y)*(center.y()-y))/(radi2*radi2) - 1.0f);
		const float shifted_x = x - center.x();
		const float x2 = shifted_x * shifted_x;
		const float a2 = radii1 * radii1;
		const float shifted_y = y - center.y();
		const float y2 = shifted_y * shifted_y;
		const float b2 = radii2 * radii2;
		return x2 / a2 + y2 / b2 - 1.0f;
	}

	color getInC() const {return inC; }
	double getDepth() const {return depth; }

  private:
	vec2 center; //center point of ellipse
	double radii1, radii2; //radii of the ellipse
	color inC;
	double depth;
};