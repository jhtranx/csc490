#ifndef VCOMBOS_H
#define VCOMBOS_H


#include "visitorCombine.h"
#include <memory>
#include <cmath>


class visitorCombineState : public visitorCombine {
public:
   visitorCombineState() {}

   void visit(shared_ptr<demogData> obj) {

      map<string, shared_ptr<demogCombo>> all_demog_combo_data_ = GetDemogComboMap();

      string region_name_ = obj->GetRegionName();
      shared_ptr<demogCombo> curr_demog_combo_data = GetDemogComboData(region_name_);
      
      if (curr_demog_combo_data == NULL) {
         shared_ptr<demogCombo> new_demog_combo_data_ = make_shared<demogCombo>();
         all_demog_combo_data_.insert(
            pair<string, shared_ptr<demogCombo>>(region_name_, new_demog_combo_data_)
         );
      }
      //regionData fields
      vector<string> states_ = obj->GetStates();
      int tot_pop_ = obj->GetTotPop();
      //demogData fields
      double pop_over_65_percent_ = obj->GetPopOver65Percent();
      double pop_under_18_percent_ = obj->GetPopUnder18Percent();
      double pop_under_5_percent_ = obj->GetPopUnder5Percent();
      double female_percent_ = obj->GetFemalePercent();
      double home_own_percent_ = obj->GetHomeOwnPercent();
      double person_per_house_percent_ = obj->GetPersonPerHousePercent();
      double high_school_grad_percent_ = obj->GetHighSchoolGradPercent();
      double bachelors_deg_percent_ = obj->GetBachelorsDegPercent();
      double foreign_born_percent_ = obj->GetForeignBornPercent();
      int med_household_income_count_ = obj->GetMedHouseholdIncomeCount();
      int num_households_count_ = obj->GetNumHouseholdsCount();
      int veterans_count_ = obj->GetVeteransCount();

      raceAndEthnicity race_eth_ = obj->GetRaceAndEthnicity();
      int white_alone_ct_ = race_eth_.GetWhiteAloneCt();
      int black_alone_ct_ =race_eth_.GetBlackAloneCt();
      int am_ind_al_native_ct_ = race_eth_.GetAmIndianAlNativeCt();
      int asian_alone_ct_ = race_eth_.GetAsianAloneCt();
      int hyn_alone_ct_ = race_eth_.GetHawaiianPacIslandCt();
      int two_or_more_ct_ = race_eth_.GetTwoOrMoreCt();
      int hisp_lat_ct_ = race_eth_.GetHispLatCt();
      int white_nh_ct_ = race_eth_.GetWhiteNotHispLatCt();

      int pop_over_65_count_ = round(pop_over_65_percent_ * tot_pop_);
      int pop_under_18_count_ = round(pop_under_18_percent_ * tot_pop_);
      int pop_under_5_count_ = round(pop_under_5_percent_ * tot_pop_);
      int female_count_ = round(female_percent_ * tot_pop_);
      int high_school_grad_count_ = round(high_school_grad_percent_ * tot_pop_);
      int bachelors_deg_count_ = round(bachelors_deg_percent_ * tot_pop_);
      int foreign_born_count_ = round(foreign_born_percent_ * tot_pop_);

      all_demog_combo_data_[region_name_]->AddState(states_.at(0));
      all_demog_combo_data_[region_name_]->UpdateTotPop(tot_pop_);
      //demogCombo update
      all_demog_combo_data_[region_name_]->IncAggrCount();
      all_demog_combo_data_[region_name_]->UpdatePopOver65Ct(pop_over_65_count_);
      all_demog_combo_data_[region_name_]->UpdatePopUnder18Ct(pop_under_18_count_);
      all_demog_combo_data_[region_name_]->UpdatePopUnder5Ct(pop_under_5_count_);
      all_demog_combo_data_[region_name_]->UpdateFemaleCt(female_count_);
      all_demog_combo_data_[region_name_]->UpdateHomeOwnPc(home_own_percent_, num_households_count_);
      //for updatePersonPerHousePc, is housing units same as num_households_count?
      all_demog_combo_data_[region_name_]->UpdatePersonPerHousePc(person_per_house_percent_, num_households_count_);
      all_demog_combo_data_[region_name_]->UpdateHighSchoolGradCt(high_school_grad_count_);
      all_demog_combo_data_[region_name_]->UpdateBachelorsDegCt(bachelors_deg_count_);
      all_demog_combo_data_[region_name_]->UpdateForeignBornCt(foreign_born_count_);
      all_demog_combo_data_[region_name_]->UpdateMedIncomePc(med_household_income_count_);
      all_demog_combo_data_[region_name_]->UpdateNumHouseholdCt(num_households_count_);
      all_demog_combo_data_[region_name_]->UpdateVeteransCt(veterans_count_);
      all_demog_combo_data_[region_name_]->UpdateWhiteCt(white_alone_ct_);
      all_demog_combo_data_[region_name_]->UpdateBlackCt(black_alone_ct_);
      all_demog_combo_data_[region_name_]->UpdateIndAlCt(am_ind_al_native_ct_);
      all_demog_combo_data_[region_name_]->UpdateAsian(asian_alone_ct_);
      all_demog_combo_data_[region_name_]->UpdateHyn(hyn_alone_ct_);
      all_demog_combo_data_[region_name_]->UpdateTwoOrMore(two_or_more_ct_);
      all_demog_combo_data_[region_name_]->UpdateHispLat(hisp_lat_ct_);
      all_demog_combo_data_[region_name_]->UpdateWhiteNotHisLat(white_nh_ct_);

   }
    
   void visit(shared_ptr<psData> obj) {

      map<string, shared_ptr<psCombo>> all_ps_combo_data_ = GetPoliceComboMap();
      string region_name_ = obj->GetRegionName();
      shared_ptr<psCombo> curr_ps_combo_data_ = GetPoliceComboData(region_name_);
      
      if (curr_ps_combo_data_ == NULL) {
         //add to map new psCombo
         shared_ptr<psCombo> new_ps_combo_data_ = make_shared<psCombo>(region_name_);
         all_ps_combo_data_.insert(pair<string, shared_ptr<psCombo>>(region_name_, new_ps_combo_data_));
      }
      //regionData fields
      vector<string> states_ = obj->GetStates();

      all_demog_combo_data_[region_name_]->AddState(states_.at(0));
      all_demog_combo_data_[region_name_]->IncTotPop();

      //psData fields
      if (obj->HasSignsOfMentalIllness())
         all_ps_combo_data_[region_name_]->IncNumMentalIllness();
      if ((obj->GetArmedWith() == "") || (obj->GetArmedWith() == "unarmed"))
         all_ps_combo_data_[region_name_]->IncUnArmedCount();
      if (obj->GetArmedWith() == "toy weapon")
         all_ps_combo_data_[region_name_]->IncArmedToy();
      if (obj->HasBodyCam())
         all_ps_combo_data_[region_name_]->IncNumBodyCam();
      all_ps_combo_data_[region_name_]->IncNumberOfCases();
      
      if (obj->GetRaceAndEthnicityStr() == "W") 
         all_ps_combo_data_[region_name_]->IncRaceEth("W");
      else if (obj->GetRaceAndEthnicityStr() == "B")
         all_ps_combo_data_[region_name_]->IncRaceEth("B");
      else if (obj->GetRaceAndEthnicityStr() == "A")
         all_ps_combo_data_[region_name_]->IncRaceEth("A");
      else if (obj->GetRaceAndEthnicityStr() == "N")
         all_ps_combo_data_[region_name_]->IncRaceEth("N");
      else if (obj->GetRaceAndEthnicityStr() == "H")
         all_ps_combo_data_[region_name_]->IncRaceEth("H");
      else if (obj->GetRaceAndEthnicityStr() == "O")
         all_ps_combo_data_[region_name_]->IncRaceEth("O");
      else if (obj->GetRaceAndEthnicityStr() == "None")
         all_ps_combo_data_[region_name_]->IncRaceEth("None");
    }

   private:
       //inherited
};

#endif