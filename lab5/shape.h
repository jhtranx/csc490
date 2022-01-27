#ifndef SHAPE_H
#define SHAPE_H
#include "vec2.h"

/* a base class for our lecture code! */
class shape {
  public:
  	shape(color theColor, double inDepth) : inC(theColor), depth(inDepth) {}

	color getInC() const {return inC; }
	double getDepth() const {return depth; }

  protected:
	color inC;
	double depth;
};

#endif