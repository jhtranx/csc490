#ifndef VISITOR_H
#define VISITOR_H

class psData;
class psCombo;
class demogData;

/* a visitor can visit any of my specific data types */
class Visitor {
  public:
    virtual void visit(shared_ptr<psData> ps) = 0;
    virtual void visit(shared_ptr<demogData> d) = 0;
};
#endif

