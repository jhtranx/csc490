#ifndef VISITREP_H
#define VISITREP_H

#include "psData.h"
#include "demogData.h"
#include "visitor.h"

//test out redesign to make sure it works with new data structures
class visitorReport : public Visitor {
public:
   visitorReport() : numVisited(0) {}

   void visit(shared_ptr<demogData> e) {
      string region_name_ = e->GetRegionName();
      vector<string> states_ = e->GetStates();
      double homeown_percent_ = e->GetHomeOwnPercent();
      
      cout << "-------------" << endl;
      cout << "Region Name: " << region_name_ << endl;
      cout << "Length of States: " << states_.size() << "  First State: " <<
      states_.at(0)  << endl;
      cout << "HomeOwn Percent: " << homeown_percent_ << endl;
   }
    
   void visit(shared_ptr<psData> e) {
      string region_name_ = e->GetRegionName();
      vector<string> states_ = e->GetStates();
      string armed_with_ = e->GetArmedWith();

      cout << "-------------" << endl;
      cout << "Region Name: " << region_name_ << endl;
      cout << "Length of States: " << states_.size() << "  First State: " << states_.at(0)  << endl;
      cout << "Armed With: " << armed_with_ << endl;
   }

   //Need to finish display()
   // void display() {
   //    cout << "-------------" << endl;
   //    cout << "Region Name: " << region_name_ << endl;
   //    cout << "Length of States: " << states_.size() << "  First State: " << states_.at(0)  << endl;
   //    cout << "Armed With: " << armed_with_ << endl;
   // }

   private:
      int numVisited;
};

#endif