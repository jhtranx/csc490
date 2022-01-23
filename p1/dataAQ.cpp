/* aggregate data */
#include <cmath>
#include <iostream>
#include <algorithm>
#include "dataAQ.h"
#include "demogData.h"


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
      int pph = round((obj->getPersonPerHouse() / 100) * obj->getHousingUnits());
      int v = obj->getVeterans();
      int hsg = round((obj->getHighSchoolGrad() / 100) * obj->getPopulation());
      int bd = round((obj->getBachelorsDeg() / 100) * obj->getPopulation());
      int fb = round((obj->getForeignBorn() / 100) * obj->getPopulation());

      if (stateMap.find(stateStr) != stateMap.end()) {
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
         demogState newState = demogState(stateStr, in65, in18, in5, 
                                          totPop20, f, mi, hu, ho, 
                                          pph, v, hsg, bd, fb);
         stateMap.insert(pair<string, demogState>(stateStr, newState));
      }
      std::cout << *obj << std::endl;
   }
}

//return the name of the state with the largest population under age 5
string dataAQ::youngestPop() {
  //FILL in
  return "fix me"; 
} 

//return the name of the state with the largest population under age 18
string dataAQ::teenPop()  {
  //FILL in
  return "fix me"; 
}

//return the name of the state with the largest population over age 65
string dataAQ::wisePop()  {
  //FILL in
  return "fix me"; 
}

//return the name of the state with the largest population who did not receive high school diploma
string dataAQ::underServeHS() {
  //FILL in
  return "fix me"; 
} 

//return the name of the state with the largest population who did receive bachelors degree and up
string dataAQ::collegeGrads() {
  //FILL in
  return "fix me"; 
}

//return the name of the state with the largest population below the poverty line
string dataAQ::belowPoverty() {
  //FILL in
  return "fix me"; 
} 
