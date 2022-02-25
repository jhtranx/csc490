#ifndef REGIONDATA_H
#define REGIONDATA_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class regionData {
   public:
      regionData (string in_region_name_, vector<string> in_states_, int in_tot_pop_) : 
         region_name_(in_region_name_), states_(in_states_), tot_pop_(in_tot_pop_) {}
      regionData (string in_region_name_) :
         region_name_(in_region_name_), states_({}), tot_pop_(0) {}
         
      friend std::ostream& operator<<(std::ostream &out, const regionData& RD);
         
      // Getters
      string GetRegionName() const { return region_name_; }
      vector<string> GetStates() const { return states_; }
      int GetTotPop() const { return tot_pop_; }

      // Setters
      void SetRegionName(string new_region_name_) { region_name_ = new_region_name_; }
      void AddState(string new_state_) { states_.push_back(new_state_); }
      void IncTotPop() { tot_pop_ += 1; }

   protected:
      string region_name_;
      vector<string> states_;
      int tot_pop_;
};

#endif