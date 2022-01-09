#ifndef RECT_H
#define RECT_H

#include "vec2.h"

/* simple data representation of a rectangle */
class rect {
  public:
   rect(vec2 tL, vec2 bR, color C) :
      topLeft(tL), botRight(bR), inC(C), depth(0) {};
    
   bool eval(double x, double y) {
      double minX, minY;
      double maxX, maxY;

      minX = topLeft.x();
      maxX = botRight.x();
      minY = topLeft.y();
      maxY = botRight.y();

      if (((x >= minX) && (x <= maxX)) &&
         ((y >= minY) && (y <= maxY))) {
         return true;
      }   
      return false;
   }

   color getInC() const {return inC;}
	double getDepth() const {return depth;}

  private:
   vec2 topLeft, botRight;
   color inC;
	double depth;
};
#endif