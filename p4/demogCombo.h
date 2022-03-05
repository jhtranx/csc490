#ifndef DEMOGCOMBO_H
#define DEMOGCOMBO_H

// add #include here
#include <string>
#include <iostream>
#include <utility>
#include "raceAndEthnicity.h"
#include "demogData.h"

// aggrCount or aggregation count i.e. totCounties or totStates

using namespace std;

//Should not have enable_shared_from_this
//inherits visit abilities from demogData
class demogCombo : public demogData {
   public:
      demogCombo() : 
         aggr_count_(0), pop_over_65_count_ (0),
         pop_under_18_count_(0), pop_under_5_count_(0),
         female_count_(0), high_school_grad_count_(0),
         bachelors_deg_count_(0), foreign_born_count_(0)
      {}
      
      // Getters
      int GetAggrCount() const { return aggr_count_; }
      int GetPopOver65Count() const {return pop_over_65_count_;}
      int GetPopUnder18Count() const {return pop_under_18_count_;}
      int GetPopUnder5Count() const {return pop_under_5_count_;}
      int GetFemaleCount() const {return female_count_;}
      int GetHighSchoolGradCount() const { return high_school_grad_count_; }
      int GetBachelorsDegCount() const {return bachelors_deg_count_;}
      int GetForeignBornCount() const { return foreign_born_count_; }

      // Setters
      void IncAggrCount() { aggr_count_ += 1; }

      void UpdatePopOver65Ct(int increase) {pop_over_65_count_ += increase;}
      void UpdatePopUnder18Ct(int increase) {pop_under_18_count_ += increase;}
      void UpdatePopUnder5Ct(int increase) {pop_under_5_count_ += increase;}
      void UpdateFemaleCt(int increase) {female_count_ += increase;}
      void UpdateHighSchoolGradCt(int increase) {high_school_grad_count_ += increase;}
      void UpdateBachelorsDegCt(int increase) {bachelors_deg_count_ += increase;}
      void UpdateForeignBornCt(int increase) {foreign_born_count_ += increase;}

      friend std::ostream& operator<<(std::ostream &out, const demogCombo& DC);

   private:
      int aggr_count_;
      int pop_over_65_count_;
      int pop_under_18_count_;
      int pop_under_5_count_;
      int female_count_;
      int high_school_grad_count_;
      int bachelors_deg_count_;
      int foreign_born_count_;
};

#endif