#ifndef POLICECOMBODATA_H
#define POLICECOMBODATA_H

#include "raceDemogData.h"
#include "psData.h"
#include "raceAndEthnicity.h"

using namespace std;

class psCombo : public regionData {
   public:
      psCombo (
         int in_mental_illness_ct_, int in_unarmed_ct_, 
         int in_armed_toy_ct_, int body_cam_ct_, int in_case_ct_
      ) : 
         mental_illness_count_(in_mental_illness_ct_), unarmed_count_(in_unarmed_ct_), 
         armed_toy_count_(in_armed_toy_ct_), body_cam_count_(body_cam_ct_), 
         case_count_(in_case_ct_), race_eth_aggr_(raceAndEthnicity()) 
      {}
      psCombo () : 
         mental_illness_count_(0), unarmed_count_(0), 
         armed_toy_count_(0), body_cam_count_(0), 
         case_count_(0), race_eth_aggr_(raceAndEthnicity()) 
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