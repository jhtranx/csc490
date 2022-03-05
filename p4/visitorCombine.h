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
      void PrintNCombo(int n) {
         int i = 0;
         cout << "All Combo data: " << endl;
         for (auto entry : all_demog_combo_data_) {
            if (i < n) {
               cout << "name: " << entry.first << endl;
               //cout << "d: " << ((entry.second).get()->*f1)() << endl;
               cout << *(entry.second).get() << endl;
               if (all_ps_combo_data_.count(entry.first)> 0) {
                  //cout << "ps: " << (all_ps_combo_data_[entry.first].get()->*f2)() << endl;
                  cout << *(all_ps_combo_data_[entry.first].get()) << endl;
               }
            }
            i++;
         }
      }

   // region_name_ could either be a county or state based on aggr
   shared_ptr<demogCombo> GetDemogComboData(string region_name_) { return all_demog_combo_data_[region_name_]; }
   shared_ptr<psCombo> GetPoliceComboData(string region_name_) { return all_ps_combo_data_[region_name_]; }

   std::map<string, shared_ptr<demogCombo>>& GetDemogComboMap()  { return all_demog_combo_data_; }
   std::map<string, shared_ptr<psCombo>>& GetPoliceComboMap() { return all_ps_combo_data_; }

   protected:
   //combo maps
      std::map<string, shared_ptr<demogCombo>> all_demog_combo_data_;
      std::map<string, shared_ptr<psCombo>> all_ps_combo_data_;
};

#endif
