#ifndef DEMOG_H
#define DEMOG_H

#include <string>
#include <iostream>
#include "raceAndEthnicity.h"
#include "regionData.h"

using namespace std;

class demogData : public regionData {
   public:
      demogData (
         double in_pop_over_65_pc_, double in_pop_under_18_pc_, 
         double in_pop_under_5_pc_, double in_female_pc_, 
         double in_home_own_pc_, double in_person_per_house_pc_, 
         double in_hs_grad_pc_, double in_bachelors_deg_pc_, 
         double in_foreign_born_pc_, int in_med_household_income_ct_, 
         int in_num_households_ct_, int in_veterans_ct_, 
         raceAndEthnicity in_race_eth_,
         string in_county_, string in_state_, int in_tot_pop_ct_
      ) :
         pop_over_65_percent_(in_pop_over_65_pc_), pop_under_18_percent_(in_pop_under_18_pc_), 
         pop_under_5_percent_(in_pop_under_5_pc_), female_percent_(in_female_pc_), 
         home_own_percent_(in_home_own_pc_), person_per_house_percent_(in_person_per_house_pc_), 
         high_school_grad_percent_(in_hs_grad_pc_), bachelors_deg_percent_(in_bachelors_deg_pc_), 
         foreign_born_percent_(in_foreign_born_pc_), med_household_income_count_(in_med_household_income_ct_), 
         num_households_count_(in_num_households_ct_), veterans_count_(in_veterans_ct_), 
         race_eth_(in_race_eth_)
         regionData {in_county_, [in_state_], in_tot_pop_ct_} 
         // region_name_ : county, states_ : one state, tot_pop_ : total pop
      {}

      // Getters
      double GetPopOver65Percent() const {return pop_over_65_percent_;}
      double GetPopUnder18Percent() const {return pop_under_18_percent_;}
      double GetPopUnder5Percent() const {return pop_under_5_percent_;}
      double GetFemalePercent() const {return female_percent_;}
      double GetHomeOwnPercent() const {return home_own_percent_;}
      double GetPersonPerHousePercent() const {return person_per_house_percent_;}
      double GetHighSchoolGradPercent() const {return high_school_grad_percent_;
      double GetBachelorsDegPercent() const {return bachelors_deg_percent_;}
      double GetForeignBornPercent() const {return foreign_born_percent_;}
      int GetMedHouseholdIncomeCount() const {return med_household_income_count_;}
      int GetNumHouseholdsCount() const {return num_households_count_;}
      int GetVeteransCount() const {return veterans_count_;}
      raceAndEthnicity GetRaceAndEthnicity() const {return race_eth_;}

      friend std::ostream& operator<<(std::ostream &out, const demogData &DD);

   private:
      double pop_over_65_percent_;
      double pop_under_18_percent_;
      double pop_under_5_percent_;
      double female_percent_;
      double home_own_percent_;
      double person_per_house_percent_;
      double high_school_grad_percent_;
      double bachelors_deg_percent_;
      double foreign_born_percent_;
      int tot_population_count_;
      int med_household_income_count_;
      int num_households_count_;
      int veterans_count_;
      raceAndEthnicity race_eth_;
};
#endif