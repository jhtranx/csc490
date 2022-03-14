#ifndef VCOMBOC_H
#define VCOMBOC_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitorCombine.h"
#include "parse.h"
#include "CountyMap.h"
#include <memory>
#include <fstream>
#include <cassert>
#include <cmath>

class visitorCombineCounty : public visitorCombine {
   public:
      visitorCombineCounty(std::string filename) {
         noMatch = 0;
         read_csvCityCounty(filename);
      }

      int GetNoMatch() const {
         return noMatch;
      }

      string stripCounty(string inWord) {
         string compareS = "County";
         /* some names include the word 'county' - strip */
         std::string::size_type i = inWord.find(compareS);
         if (i != std::string::npos) {
            inWord.erase(i-1, compareS.length()+1);
         }
         //apostrophe issue - strip will result in lack of rep - better solution?
         string symbol = "\'";
         i = inWord.find(symbol);
         if (i != std::string::npos) {
            inWord.erase(i-1, symbol.length()+1);
         }
         //strip Alaska designator
         string borough = "and Borough";
         i = inWord.find(borough);
         if (i != std::string::npos) {
            inWord.erase(i-1, borough.length()+1);
         }
         string borough1 = "Borough";
         i = inWord.find(borough1);
         if (i != std::string::npos) {
            inWord.erase(i-1, borough1.length()+1);
         }
         // string parish = "Parish";
         // i = inWord.find(parish);
         // if (i != std::string::npos) {
         //    inWord.erase(i-1, parish.length()+1);
         // }
         string ca = "Census Area";
         i = inWord.find(ca);
         if (i != std::string::npos) {
            inWord.erase(i-1, ca.length()+1);
         }

         return inWord;
      }

      //store demographic data by county name
      void visit(shared_ptr<demogData> obj) {
         // map <county (county + state), demogCombo >
         map<string, shared_ptr<demogCombo>>& all_demog_combo_data_ = GetDemogComboMap();

         // demogData region_name_ is a county
         string county_key_ = stripCounty(obj->GetRegionName()) + obj->GetStateName();
      
         if (all_demog_combo_data_.find(county_key_) == all_demog_combo_data_.end()) {
            shared_ptr<demogCombo> new_demog_combo_data_ = make_shared<demogCombo>();
            all_demog_combo_data_.insert(
               pair<string, shared_ptr<demogCombo>>(county_key_, new_demog_combo_data_)
            );
         }

         //regionData fields
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

         // adding current state to empty vector
         all_demog_combo_data_[county_key_]->SetRegionName(county_key_);
         all_demog_combo_data_[county_key_]->AddState(obj->GetStateName());
         all_demog_combo_data_[county_key_]->UpdateTotPop(tot_pop_);
         //demogCombo update
         all_demog_combo_data_[county_key_]->IncAggrCount();
         all_demog_combo_data_[county_key_]->UpdatePopOver65Ct(pop_over_65_count_);
         all_demog_combo_data_[county_key_]->UpdatePopUnder18Ct(pop_under_18_count_);
         all_demog_combo_data_[county_key_]->UpdatePopUnder5Ct(pop_under_5_count_);
         all_demog_combo_data_[county_key_]->UpdateFemaleCt(female_count_);
         all_demog_combo_data_[county_key_]->UpdateHomeOwnPc(home_own_percent_, num_households_count_);
         //for updatePersonPerHousePc, is housing units same as num_households_count?
         all_demog_combo_data_[county_key_]->UpdatePersonPerHousePc(person_per_house_percent_, num_households_count_);
         all_demog_combo_data_[county_key_]->UpdateHighSchoolGradCt(high_school_grad_count_);
         all_demog_combo_data_[county_key_]->UpdateBachelorsDegCt(bachelors_deg_count_);
         all_demog_combo_data_[county_key_]->UpdateForeignBornCt(foreign_born_count_);
         all_demog_combo_data_[county_key_]->UpdateMedIncomeCt(med_household_income_count_, tot_pop_);
         all_demog_combo_data_[county_key_]->UpdateNumHouseholdCt(num_households_count_);
         all_demog_combo_data_[county_key_]->UpdateVeteransCt(veterans_count_);
         all_demog_combo_data_[county_key_]->UpdateWhiteCt(white_alone_ct_);
         all_demog_combo_data_[county_key_]->UpdateBlackCt(black_alone_ct_);
         all_demog_combo_data_[county_key_]->UpdateIndAlCt(am_ind_al_native_ct_);
         all_demog_combo_data_[county_key_]->UpdateAsian(asian_alone_ct_);
         all_demog_combo_data_[county_key_]->UpdateHyn(hyn_alone_ct_);
         all_demog_combo_data_[county_key_]->UpdateTwoOrMore(two_or_more_ct_);
         all_demog_combo_data_[county_key_]->UpdateHispLat(hisp_lat_ct_);
         all_demog_combo_data_[county_key_]->UpdateWhiteNotHisLat(white_nh_ct_);

         // cout << "County Key: " << county_key_ << endl;
         // cout << "County Count: " << all_demog_combo_data_[county_key_]->GetAggrCount() << endl;
   
      }
      
      //aggregate police shooting data by county
      void visit(shared_ptr<psData> obj) {
         // map <county (county + state), psCombo>
         map<string, shared_ptr<psCombo>>& all_ps_combo_data_ = GetPoliceComboMap();

         string state_ = obj->GetStates().at(0);
         // psData region_name_ is a city

         string city_ = obj->GetRegionName();
         string compareS = "County";
         string county_;
         /* some names include the word 'county' - strip */
         std::string::size_type i = city_.find(compareS);
         if (i != std::string::npos) {
            // "County" is within;
            county_ = stripCounty(city_);
         }
         else {
            // "County" is NOT within;
            string city_key_ = stripCounty(city_) + state_;
            county_ = cityToCounty[city_key_].countyName;
         }

         if (county_ == "") {
            noMatch += 1;
            // cout << "NOMATCH : " << noMatch << endl;
            return;
         }
         string county_key_ = county_ + state_;
      
         if (all_ps_combo_data_.find(county_key_) == all_ps_combo_data_.end()) {
            //add to map new psCombo
            shared_ptr<psCombo> new_ps_combo_data_ = make_shared<psCombo>(county_key_);
            all_ps_combo_data_.insert(pair<string, shared_ptr<psCombo>>(county_key_, new_ps_combo_data_));
         }
         //regionData fields
         all_ps_combo_data_[county_key_]->SetRegionName(county_key_);
         all_ps_combo_data_[county_key_]->AddState(state_);
         all_ps_combo_data_[county_key_]->IncTotPop();

         //psData fields
         if (obj->HasSignsOfMentalIllness())
            all_ps_combo_data_[county_key_]->IncNumMentalIllness();
         if ((obj->GetArmedWith() == "") || (obj->GetArmedWith() == "unarmed"))
            all_ps_combo_data_[county_key_]->IncUnArmedCount();
         if (obj->GetArmedWith() == "toy weapon")
            all_ps_combo_data_[county_key_]->IncArmedToy();
         if (obj->HasBodyCam())
            all_ps_combo_data_[county_key_]->IncNumBodyCam();
         all_ps_combo_data_[county_key_]->IncNumberOfCases();
         
         if (obj->GetRaceAndEthnicityStr() == "W") 
            all_ps_combo_data_[county_key_]->IncRaceEth("W");
         else if (obj->GetRaceAndEthnicityStr() == "B")
            all_ps_combo_data_[county_key_]->IncRaceEth("B");
         else if (obj->GetRaceAndEthnicityStr() == "A")
            all_ps_combo_data_[county_key_]->IncRaceEth("A");
         else if (obj->GetRaceAndEthnicityStr() == "N")
            all_ps_combo_data_[county_key_]->IncRaceEth("N");
         else if (obj->GetRaceAndEthnicityStr() == "H")
            all_ps_combo_data_[county_key_]->IncRaceEth("H");
         else if (obj->GetRaceAndEthnicityStr() == "O")
            all_ps_combo_data_[county_key_]->IncRaceEth("O");
         else if (obj->GetRaceAndEthnicityStr() == "None")
            all_ps_combo_data_[county_key_]->IncRaceEth("None");

         // PsCombo's Aggr count can be derived from its totPop (incremented everytime)
         // cout << "County Key: " << county_key_ << endl;
         // cout << "City: " << city_ << endl;
         // cout << "Cities Count: " << all_ps_combo_data_[county_key_]->GetTotPop() << endl;
      }

      //helper to create map from city to county
      void read_csvCityCounty(std::string filename) {
         // Create an input filestream
         std::ifstream myFile(filename);

         // Make sure the file is open
         if(!myFile.is_open()) {
            throw std::runtime_error("Could not open file");
         }

         if(myFile.good()) {
            consumeColumnNames(myFile);

            // Helper vars
            std::string line;

            // Now read data, line by line and enter into the map
            while(std::getline(myFile, line)) {

               std::stringstream ss(line);

               string city = getField(ss);
               string junk1 = getField(ss);  //"city_ascii","city_alt"
               string junk0 = getField(ss);
               string state = getField(ss);
               string junk2 = getField(ss);  //"county_key_name"
               string countyfips = getField(ss);
               string county = getField(ss);

               string cityKey = city+state;

               cityToCounty[cityKey] = countyID{county, std::stoi(countyfips)};

               //cout << "line: " << line << endl;
               //cout << "pair (city, county): " << city << ", " << county << " state " << state << " fip" << countyfips <<  endl;
            }

            // Close file
            myFile.close();
         }
      }


   private:
      //only inherited data at this point
      //helper map to create aggregates from city -> county
      std::map<string, countyID> cityToCounty;
      int noMatch;
};

#endif
