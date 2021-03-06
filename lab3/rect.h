#ifndef RECT_H
#define RECT_H

#include "vec2.h"

/* simple data representation of a rectangle */
class Rect {
  public:
   // Rect(vec2 tL, vec2 bR, color C) :
   //    topLeft(tL), botRight(bR), inC(C), depth(0) {};

   Rect(vec2 tL, int x, int y, int d, color C) :
      topLeft(tL), offSetX(x), offSetY(y), depth(d), inC(C) {};


      bool eval(double x, double y) {
      double minX, minY;
      double maxX, maxY;

      minX = topLeft.x();
      maxX = topLeft.x() + offSetX;
      minY = topLeft.y();
      maxY = topLeft.y() + offSetY;

      if (((x >= minX) && (x <= maxX)) &&
         ((y >= minY) && (y <= maxY))) {
         return true;
      }   
      return false;
   }

   color getInC() const {return inC;}
	double getDepth() const {return depth;}

   private:
   vec2 topLeft;
   int offSetX;
   int offSetY;
   color inC;
	double depth;
   };
#endif

//    Rect(vec2 tL, int x, int y, int d, color C) :
//       topLeft(tL), botRight(vec2(tL.x() + x, tL.y() + y)), depth(d), inC(C) {};


    
//    bool eval(double x, double y) {
//       double minX, minY;
//       double maxX, maxY;

//       minX = topLeft.x();
//       maxX = botRight.x();
//       minY = topLeft.y();
//       maxY = botRight.y();

//       if (((x >= minX) && (x <= maxX)) &&
//          ((y >= minY) && (y <= maxY))) {
//          return true;
//       }   
//       return false;
//    }

//    color getInC() const {return inC;}
// 	double getDepth() const {return depth;}

//   private:
//    vec2 topLeft, botRight;
//    color inC;
// 	double depth;
// };
// #endif