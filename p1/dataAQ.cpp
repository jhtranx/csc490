/* aggregate data */
#include <cmath>
#include <iostream>
#include <algorithm>
#include "dataAQ.h"
#include "demogData.h"
#include "demogState.h"


dataAQ::dataAQ() {}

/* necessary function to aggregate the data - this CAN and SHOULD vary per
   student - depends on how they map, etc. */
void dataAQ::createStateData(std::vector<shared_ptr<demogData>> theData) {
//FILL in
   for (const auto &obj : theData) {
      string stateStr = obj->getState();

      int in65 = round((obj->getPopOver65() / 100) * obj->getPopulation());
      int in18 = round((obj->getPopUnder18() / 100) * obj->getPopulation());
      int in5 = round((obj->getPopUnder5() / 100) * obj->getPopulation());
      int totPop20 = obj->getPopulation();

      int f = round((obj->getFemale() / 100) * obj->getPopulation());
      int mi = obj->getMedIncome();
      int hu = obj->getHousingUnits();
      int ho = round((obj->getHomeOwn() / 100) * obj->getPopulation());
      double pph = obj->getPersonPerHouse();
      int v = obj->getVeterans();
      int hsg = round((obj->getHighSchoolGrad() / 100) * obj->getPopulation());
      int bd = round((obj->getBachelorsDeg() / 100) * obj->getPopulation());
      int fb = round((obj->getForeignBorn() / 100) * obj->getPopulation());

      if (stateMap.find(stateStr) != stateMap.end()) {
         stateMap.at(stateStr).updateTotCounties(); //updated totCounties
         stateMap.at(stateStr).updatePopOver65(in65);
         stateMap.at(stateStr).updatePopUnder18(in18);
         stateMap.at(stateStr).updatePopUnder5(in5);
         stateMap.at(stateStr).updatePopulation(totPop20);
         stateMap.at(stateStr).updateFemale(f);
         stateMap.at(stateStr).updateMedIncome(mi);
         stateMap.at(stateStr).updateHousingUnits(hu);
         stateMap.at(stateStr).updateHomeOwn(ho);
         stateMap.at(stateStr).updatePersonPerHouse(pph);
         stateMap.at(stateStr).updateVeterans(v);
         stateMap.at(stateStr).updateHighSchoolGrad(hsg);
         stateMap.at(stateStr).updateBachelorsDeg(bd);
         stateMap.at(stateStr).updateForeignBorn(fb);
      }
      else {
         demogState newState = demogState(stateStr, 1, in65, in18, in5, 
                                          totPop20, f, mi, hu, ho, 
                                          pph, v, hsg, bd, fb);
         stateMap.insert(pair<string, demogState>(stateStr, newState));
      }
      std::cout << *obj << std::endl;
   }
}

//return the name of the state with the largest population under age 5
string dataAQ::youngestPop() {
   double maxPop = 0;
   string maxState;

   for (auto& statePair: stateMap) {
      demogState currState = statePair.second;
      double currUnder5 = currState.getPopUnder5() / (double)currState.getPopulation();
      if (currUnder5 > maxPop) {
         maxPop = currUnder5;
         maxState = statePair.first;   
      }     
   }
   return maxState; 
} 

//return the name of the state with the largest population under age 18
string dataAQ::teenPop()  {
  double maxPop = 0;
   string maxState;

   for (auto& statePair: stateMap) {
      demogState currState = statePair.second;
      double currUnder18 = currState.getPopUnder18() / (double)currState.getPopulation();
      if (currUnder18 > maxPop) {
         maxPop = currUnder18;
         maxState = statePair.first;   
      }     
   }
   return maxState; 
}

//return the name of the state with the largest population over age 65
string dataAQ::wisePop()  {
   double maxPop = 0;
      string maxState;

      for (auto& statePair: stateMap) {
         demogState currState = statePair.second;
         double currOver65 = currState.getPopOver65() / (double)currState.getPopulation();
         if (currOver65 > maxPop) {
            maxPop = currOver65;
            maxState = statePair.first;   
         }     
      }
      return maxState; 
}

//return the name of the state with the largest population who did not receive high school diploma
string dataAQ::underServeHS() {
   double minPop = (stateMap.at("UT")).getHighSchoolGrad() / 
                     (double)(stateMap.at("UT")).getPopulation();
   string maxState = "UT";

   for (auto& statePair: stateMap) {
      demogState currState = statePair.second;
      double currHs = currState.getHighSchoolGrad() / (double)currState.getPopulation();
      if (currHs < minPop) {
         minPop = currHs;
         maxState = statePair.first;   
      }     
   }
   return maxState; 
} 

//return the name of the state with the largest population who did receive bachelors degree and up
string dataAQ::collegeGrads() {
   double maxPop = 0;
   string maxState;

   for (auto& statePair: stateMap) {
      demogState currState = statePair.second;
      double currCollege = currState.getBachelorsDeg() / (double)currState.getPopulation();
      if (currCollege > maxPop) {
         maxPop = currCollege;
         maxState = statePair.first;   
      }     
   }
   return maxState; 
}

//FIX!
//return the name of the state with the largest population below the poverty line
string dataAQ::belowPoverty() {
   double maxPop = 0;
   string maxState;

   for (auto& statePair: stateMap) {
      demogState currState = statePair.second;
      double currHs = currState.getHighSchoolGrad() / (double)currState.getPopulation();
      if (currHs > maxPop) {
         maxPop = currHs;
         maxState = statePair.first;   
      }     
   }
   return maxState; 
} 

//New Queries

//return the name of the state with the lowest medium income
string dataAQ::lowestMedInc() {
   double minMedInc = (stateMap.at("CA")).getMedIncome();
   string minState;

   for (auto& statePair: stateMap) {
      demogState currState = statePair.second;
      double currMedInc = currState.getMedIncome();
      if (currMedInc < minMedInc) {
         minMedInc = currMedInc;
         minState = statePair.first;   
      }     
   }
   return minState; 
}

//return the name of the state with the largest percentage of the population who are foreign born
string dataAQ::mostForBorn() {
   double maxPop = 0;
   string maxState;

   for (auto& statePair: stateMap) {
      demogState currState = statePair.second;
      double currForBorn = currState.getForeignBorn() / (double)currState.getPopulation();
      if (currForBorn > maxPop) {
         maxPop = currForBorn;
         maxState = statePair.first;   
      }     
   }
   return maxState; 
}

//FIX!
//return the name of the state with the largest number of people per household
string dataAQ::mostPerPerHouse() {
   return "FIX ME";
}

//return the name of the state with the largest percentage of veterans
string dataAQ::mostVeterans() {
   double maxPop = 0;
   string maxState;

   for (auto& statePair: stateMap) {
      demogState currState = statePair.second;
      double currVets = currState.getVeterans() / (double)currState.getPopulation();
      if (currVets > maxPop) {
         maxPop = currVets;
         maxState = statePair.first;   
      }     
   }
   return maxState; 
}