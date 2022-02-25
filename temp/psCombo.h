#ifndef POLICECOMBODATA_H
#define POLICECOMBODATA_H

#include "psData.h"
#include "raceAndEthnicity.h"
#include "regionData.h"

using namespace std;

class psCombo : public regionData {
   public:
      psCombo (string in_region_name_) : 
         mental_illness_count_(0), unarmed_count_(0), 
         armed_toy_count_(0), body_cam_count_(0), 
         case_count_(0), race_eth_aggr_(raceAndEthnicity()),
         regionData {in_region_name_, vector<string> {}, 0}
         // states_ and tot_pop_ are set to zero values for incrementing
      {}

      // Getters
      int GetNumMentalIllness() const { return mental_illness_count_; }    // total count “TRUE”
      int GetUnArmedCount() const { return unarmed_count_; }               // total count blank, ‘unarmed’
      int GetArmedToyCount() const { return armed_toy_count_; }            // total count ’toy weapon’
      int GetBodyCamCount() const { return body_cam_count_; }              // total count “TRUE”
      int GetCasesCount() const { return case_count_; }                    // total number for a region
      raceAndEthnicity GetRaceEthnicityAggr() const { return race_eth_aggr_; }

      // Setters
      void IncNumMentalIllness() { mental_illness_count_ += 1; }
      void IncUnArmedCount() { unarmed_count_ += 1; }                    
      void IncArmedToy() { armed_toy_count_ += 1; }             
      void IncNumBodyCam() { body_cam_count_ += 1; }                       
      void IncNumberOfCases() { case_count_ += 1; }                        

      void IncRaceEth (string race_) {
         cout << "RACE: " << race_ << endl;
         if (race_ == "W") { race_eth_aggr_.incWhiteAlone(); race_eth_aggr_.incWhiteNotHispLat(); }
         else if (race_ == "B") { race_eth_aggr_.incBlackAlone(); }
         else if (race_ == "A") { race_eth_aggr_.incAsianAlone(); }
         else if (race_ == "N") { race_eth_aggr_.incAmIndianAlNative(); }
         else if (race_ == "H") { race_eth_aggr_.incHispLat(); }
         else race_eth_aggr_.incUnspecified();
      }

      friend std::ostream& operator<<(std::ostream &out, const psCombo& PD);

	private:
     int mental_illness_count_;
     int unarmed_count_;
     int armed_toy_count_;
     int body_cam_count_;
     int case_count_;
     raceAndEthnicity race_eth_aggr_;
};

#endif