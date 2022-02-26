#ifndef VCOMBO_H
#define VCOMBO_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitor.h"
#include <memory>
#include <map>

//The shared combo data
class visitorCombine : public Visitor {
public:
    visitorCombine() {}

    //just a helper to print out various fields
    void printNCombo(int n) {
        int i=0;
        cout << "All Combo data: " << endl;
        for (auto entry : allComboDemogData) {
            if (i < n) {
              cout << "name: " << entry.first << endl;
              //cout << "d: " << ((entry.second).get()->*f1)() << endl;
              cout << *(entry.second).get() << endl;
              if (allComboPoliceData.count(entry.first)> 0) {
                //cout << "ps: " << (allComboPoliceData[entry.first].get()->*f2)() << endl;
                cout << *(allComboPoliceData[entry.first].get()) << endl;
              }
            }
            i++;
        }
    }

    shared_ptr<demogCombo> getComboDemogData(string regionName) { return allComboDemogData[regionName]; }
    shared_ptr<psCombo> getComboPoliceData(string regionName) { return allComboPoliceData[regionName]; }

	std::map<string, shared_ptr<demogCombo> >& getComboDemog()  { return allComboDemogData; }
    std::map<string, shared_ptr<psCombo> > & getComboPolice() { return allComboPoliceData; }

    protected:
    	//combo maps
       std::map<string, shared_ptr<demogCombo> > allComboDemogData;
       std::map<string, shared_ptr<psCombo> > allComboPoliceData;
};

#endif
