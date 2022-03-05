#ifndef POLICE_H
#define POLICE_H

#include <string>
#include <iostream>
#include <utility>
#include "raceAndEthnicity.h"
#include "regionData.h"

using namespace std;

class psData : public regionData, public std::enable_shared_from_this<psData>  {
   public:
      psData (
         string in_name_, string in_race_eth_str_, string in_armed_, 
         bool in_body_cam_, bool in_signs_of_mental_illness_,
         string in_city_, string in_state_
      ) : 
         name_(in_name_), race_eth_str_(in_race_eth_str_),
         armed_with_(in_armed_), body_cam_(in_body_cam_), 
         signs_of_mental_illness_(in_signs_of_mental_illness_),
         regionData {in_city_, vector<string> {in_state_}, 1} 
         // region_name_ : city, states_ : one state, tot_pop_ : 1 person
      {}

      string GetName() const { return name_; }
      string GetRaceAndEthnicityStr() const { return race_eth_str_; }
      string GetArmedWith() const { return armed_with_; }
      bool HasBodyCam() const { return body_cam_; }
      bool HasSignsOfMentalIllness() const { return signs_of_mental_illness_; }

      void Accept(class Visitor &v) override;

      friend std::ostream& operator<<(std::ostream &out, const psData &PD);

   private:
      const string name_; 
      const string race_eth_str_;
      const string armed_with_;
      const bool body_cam_;
      const bool signs_of_mental_illness_;
};

#endif