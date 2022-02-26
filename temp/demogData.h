#ifndef DEMOG_H
#define DEMOG_H

#include <string>
#include <iostream>
#include "raceAndEthnicity.h"
#include "regionData.h"

using namespace std;

class demogData : public regionData, public std::enable_shared_from_this<demogData> {
   public:
      demogData () :
         pop_over_65_percent_(0), pop_under_18_percent_(0), 
         pop_under_5_percent_(0), female_percent_(0), 
         home_own_percent_(0), person_per_house_percent_(0), 
         high_school_grad_percent_(0), bachelors_deg_percent_(0), 
         foreign_born_percent_(0), med_household_income_count_(0), 
         num_households_count_(0), veterans_count_(0), 
         race_eth_(raceAndEthnicity()),
         regionData {"empty", vector<string> {}, 0} 
         // region_name_ : county, states_ : one state, tot_pop_ : total pop
      {}
      
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
         race_eth_(in_race_eth_),
         regionData {in_county_, vector<string> {in_state_}, in_tot_pop_ct_} 
         // region_name_ : county, states_ : one state, tot_pop_ : total pop
      {}

      // Getters
      double GetPopOver65Percent() const {return pop_over_65_percent_;}
      double GetPopUnder18Percent() const {return pop_under_18_percent_;}
      double GetPopUnder5Percent() const {return pop_under_5_percent_;}
      double GetFemalePercent() const {return female_percent_;}
      double GetHomeOwnPercent() const {return home_own_percent_;}
      double GetPersonPerHousePercent() const {return person_per_house_percent_;}
      double GetHighSchoolGradPercent() const {return high_school_grad_percent_;}
      double GetBachelorsDegPercent() const {return bachelors_deg_percent_;}
      double GetForeignBornPercent() const {return foreign_born_percent_;}
      int GetMedHouseholdIncomeCount() const {return med_household_income_count_;}
      int GetNumHouseholdsCount() const {return num_households_count_;}
      int GetVeteransCount() const {return veterans_count_;}
      raceAndEthnicity GetRaceAndEthnicity() const {return race_eth_;}

      string GetStateName() const {
         vector<string> states_ = GetStates(); 
         return states_.at(0);
      }

      // Setters - mainly used for demogCombo (remember this is a diff use of our priv variables)
      void UpdateWhiteCt (int white_ct_) {
         int prev_white_ct_ = race_eth_.GetWhiteAloneCt();
         race_eth_.SetWhiteAloneCt(white_ct_ + prev_white_ct_);
      }
      void UpdateBlackCt (int black_ct_) {
         int prev_black_ct_ = race_eth_.GetBlackAloneCt();
         race_eth_.SetBlackAloneCt(black_ct_ + prev_black_ct_);
      }
      void UpdateIndAlCt (int ind_al_ct_) {
         int prev_ind_al_ct_ = race_eth_.GetAmIndianAlNativeCt();
         race_eth_.SetAmIndianAlNativeCt(ind_al_ct_ + prev_ind_al_ct_);
      }
      void UpdateAsian (int asian_ct_) {
         int prev_asian_ct_ = race_eth_.GetAsianAloneCt();
         race_eth_.SetAsianAloneCt(asian_ct_ + prev_asian_ct_);
      }
      void UpdateHyn (int hyn_ct_) {
         int prev_hyn_ct_ = race_eth_.GetHawaiianPacIslandCt();
         race_eth_.SetHawaiianPacIslandCt(hyn_ct_ + prev_hyn_ct_);
      }
      void UpdateTwoOrMore (int two_or_more_ct_) {
         int prev_two_or_more_ct_ = race_eth_.GetTwoOrMoreCt();
         race_eth_.SetTwoOrMoreCt(prev_two_or_more_ct_ + two_or_more_ct_);
      }
      void UpdateHispLat (int hisp_lat_ct_) {
         int prev_hisp_lat_ct_ = race_eth_.GetHispLatCt();
         race_eth_.SetHispLatCt(hisp_lat_ct_ + prev_hisp_lat_ct_);
      }
      void UpdateWhiteNotHisLat (int white_nh_ct_, int incPop) {
         int prev_white_nh_ct_ = race_eth_.GetWhiteNotHispLatCt();
         race_eth_.SetWhiteNotHispLatCt(white_nh_ct_ + prev_white_nh_ct_);
      }
      
      void UpdateNumHouseholdCt(int increase)  {num_households_count_ += increase;}

      void UpdateHomeOwnPc(double inc_home_own_percent_, int inc_num_household_count_) {
         int old_tot_home_own_ct_ = (double)num_households_count_ * home_own_percent_;
         int new_tot_home_own_ct_ = (double)inc_num_household_count_ * inc_home_own_percent_;
         double new_home_own_pc_ = (double)(old_tot_home_own_ct_ + new_tot_home_own_ct_) / 
            (double)(num_households_count_ + inc_num_household_count_);
         home_own_percent_ = new_home_own_pc_;
      }

      void UpdatePersonPerHousePc(double inc_pph_pc_, int inc_housing_units_)  {
         double old_pph_tot_ = person_per_house_percent_ * (double) num_households_count_;
         double new_pph_tot_ =  inc_pph_pc_ * (double) inc_housing_units_;
         int new_housing_units_ = inc_housing_units_ + num_households_count_;
         double new_pph_percent_ = (old_pph_tot_ + new_pph_tot_) / (double) new_housing_units_;
         person_per_house_percent_ = new_pph_percent_;
      } 

      void Accept(class Visitor &v) override;

      friend std::ostream& operator<<(std::ostream &out, const demogData &DD);

   protected:
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