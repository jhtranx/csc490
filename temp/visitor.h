#ifndef VISITOR_H
#define VISITOR_H

#include <memory>

class psData;
class psCombo;
class demogData;

/* a visitor can visit any of my specific data types */
class Visitor {
  public:
    virtual void visit(std::shared_ptr<psData> ps) = 0;
    virtual void visit(std::shared_ptr<demogData> d) = 0;
};
#endif

