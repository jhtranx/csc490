/* aggregate data */
#include "dataAQ.h"
#include "demogData.h"
#include "demogState.h"
#include "psData.h"
#include <iostream>
#include <algorithm>
#include <cmath>


dataAQ::dataAQ() {}

void dataAQ::createStatePoliceData(std::vector<shared_ptr<psData>> theData){
   for (const auto &obj : theData) {
      string stateStr = obj->getState();

      if (allStatePoliceData.find(stateStr) == allStatePoliceData.end()) { 
         shared_ptr<psCombo> newCombo = make_shared<psCombo>(stateStr);
         auto result = allStatePoliceData.insert(pair<string, shared_ptr<psCombo>>(stateStr, newCombo));
      }

      if (obj->hasSignsOfMentalIllness())
         allStatePoliceData[stateStr]->incNumMentalIllness();
      if ((obj->getArmed() == "") || (obj->getArmed() == "unarmed"))
         allStatePoliceData[stateStr]->incUnArmedCount();
      if (obj->getArmed() == "toy weapon")
         allStatePoliceData[stateStr]->incArmedToy();
      if (obj->hasBodyCam())
         allStatePoliceData[stateStr]->incNumBodyCam();
      allStatePoliceData[stateStr]->incNumberOfCases();
      if (obj->getRaceEthnicity() == "W") 
         allStatePoliceData[stateStr]->incRaceEth("W");
      else if (obj->getRaceEthnicity() == "B")
         allStatePoliceData[stateStr]->incRaceEth("B");
      else if (obj->getRaceEthnicity() == "A")
         allStatePoliceData[stateStr]->incRaceEth("A");
      else if (obj->getRaceEthnicity() == "N")
         allStatePoliceData[stateStr]->incRaceEth("N");
      else if (obj->getRaceEthnicity() == "H")
         allStatePoliceData[stateStr]->incRaceEth("H");
      else if (obj->getRaceEthnicity() == "O")
         allStatePoliceData[stateStr]->incRaceEth("O");
      else if (obj->getRaceEthnicity() == "None")
         allStatePoliceData[stateStr]->incRaceEth("None");
   }
}
void dataAQ::printPSReportInfo(string stateStr) {
   shared_ptr<demogState> SD = getStateData(stateStr);
   shared_ptr<psCombo> PS = getStatePoliceData(stateStr);

   double caseCt = (double)PS->getNumberOfCases();
   double popCt = (double)SD->getPopulation();
   cout << stateStr << endl;
   cout << "Total population: " << SD->getPopulation();
   cout << " Percentage home ownership: " << 
      (double)SD->getHomeOwn()*100 << "%" << endl;
   cout << "Police shooting incidents: " << PS->getNumberOfCases();
   cout << " Percent of population: " << 
      (caseCt/popCt)*100 << "%" << endl;
}

string dataAQ::stripCounty(string inWord) {
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
    string ca = "Census Area";
    i = inWord.find(ca);
    if (i != std::string::npos) {
        inWord.erase(i-1, ca.length()+1);
    }
    return inWord;
}

//sort and report the top ten states in terms of number of police shootings 
void dataAQ::reportTopTenStatesPS() {

   vector<pair<string, shared_ptr<psCombo>>> mapVector;

   for (const auto &obj : allStatePoliceData) {
      mapVector.push_back(pair<string, shared_ptr<psCombo>>(obj.first, obj.second));
   }

   sort(mapVector.begin(), mapVector.end(), [](pair<string, shared_ptr<psCombo>> lhs, 
      pair<string, shared_ptr<psCombo>> rhs) {
         return lhs.second->getNumberOfCases() > rhs.second->getNumberOfCases(); 
   });

   for (int i = 0; i < 10; i++) {printPSReportInfo(mapVector.at(i).first);}

   cout << "\n**Full listings for top 3 police shootings & the associated census data:" << endl;
   for (int j = 0; j < 3; j++) {
      if (getStatePoliceData(mapVector.at(j).first) != nullptr) {
		   cout << *(getStatePoliceData(mapVector.at(j).first)) << endl;
         cout << "**US census data: ";
         cout << *(getStateData(mapVector.at(j).first)) << endl;
      }
   }
}

void dataAQ::reportBottomTenStatesHomeOwn() {

   vector<pair<string, shared_ptr<demogState>>> mapVector;

   for (const auto &obj : stateMap) {
      mapVector.push_back(pair<string, shared_ptr<demogState>>(obj.first, obj.second));
   }

   sort(mapVector.begin(), mapVector.end(), [](pair<string, shared_ptr<demogState>> lhs, pair<string, shared_ptr<demogState>> rhs) {
      return (lhs.second->getHomeOwn()) < (rhs.second->getHomeOwn()); 
   });

   for (int i = 0; i < 10; i++) {
      printPSReportInfo(mapVector.at(i).first);
   }

   cout << "\n**Full listings for bottom 3 home own rates & the associated census data:" << endl;
   for (int j = 0; j < 3; j++) {
      if (getStatePoliceData(mapVector.at(j).first) != nullptr) {
		   cout << *(getStatePoliceData(mapVector.at(j).first)) << endl;
         cout << "**US census data: ";
         cout << *(getStateData(mapVector.at(j).first)) << endl;
      }
   }
}

/* aggregate data */


/* necessary function to aggregate the data - this CAN and SHOULD vary per
   student - depends on how they map, etc. */
void dataAQ::createStateData(std::vector<shared_ptr<demogData>> theData) {
//FILL in
   for (const auto &obj : theData) {
      string stateStr = obj->getState();

      int totPop20 = obj->getPopulation();
      int in65 = round(obj->getPopOver65() * totPop20);
      int in18 = round(obj->getPopUnder18() * totPop20);
      int in5 = round(obj->getPopUnder5() * totPop20);
      
      int f = round(obj->getFemale() * totPop20);
      int mi = obj->getMedIncome();
      int hu = obj->getNumHouseholds();
      double ho = obj->getHomeOwn();
      double pph = obj->getPersonPerHouse();
      int v = obj->getVeterans();
      int hsg = round(obj->getHighSchoolGrad() * totPop20);
      int bd = round(obj->getBachelorsDeg() * totPop20);
      int fb = round(obj->getForeignBorn() * totPop20);

      raceAndEthnicity re = obj->getRaceAndEthnicity();
      int whiteCt = re.getWhiteAlone() * totPop20;
      int blackCt = re.getBlackAlone() * totPop20;
      int inIndAlCt = re.getAmIndianAlNative() * totPop20;
      int asianCt = re.getAsianAlone() * totPop20;
      int hynCt = re.getHawaiianPacIsland() * totPop20;
      int twoOrMoreCt = re.getAsianAlone() * totPop20;
      int hispLatCt = re.getHispLat() * totPop20;
      int whiteNotHispLatCt = re.getWhiteNotHispLat() * totPop20;

      if (stateMap.find(stateStr) != stateMap.end()) {
         stateMap[stateStr]->updateTotCounties(); //updated totCounties
         stateMap[stateStr]->updatePopOver65(in65);
         stateMap[stateStr]->updatePopUnder18(in18);
         stateMap[stateStr]->updatePopUnder5(in5);
         stateMap[stateStr]->updatePopulation(totPop20);
         stateMap[stateStr]->updateFemale(f);
         stateMap[stateStr]->updateMedIncome(mi);
         stateMap[stateStr]->updateHomeOwn(ho, hu);
         stateMap[stateStr]->updatePersonPerHouse(pph, hu);
         stateMap[stateStr]->updateNumHousehold(hu);
         stateMap[stateStr]->updateVeterans(v);
         stateMap[stateStr]->updateHighSchoolGrad(hsg);
         stateMap[stateStr]->updateBachelorsDeg(bd);
         stateMap[stateStr]->updateForeignBorn(fb);

         stateMap[stateStr]->updateWhite(whiteCt, totPop20);
         stateMap[stateStr]->updateBlack(blackCt, totPop20);
         stateMap[stateStr]->updateIndAl(inIndAlCt, totPop20);
         stateMap[stateStr]->updateAsian(asianCt, totPop20);
         stateMap[stateStr]->updateHyn(hynCt, totPop20);
         stateMap[stateStr]->updateTwoOrMore(twoOrMoreCt, totPop20);
         stateMap[stateStr]->updateHispLat(hispLatCt, totPop20);
         stateMap[stateStr]->updateWhiteNotHisLat(whiteNotHispLatCt, totPop20);
      }
      else {
         shared_ptr<demogState> newState = make_shared<demogState>(
                                          stateStr, 1, in65, in18, in5, 
                                          totPop20, f, mi, hu, ho, 
                                          pph, v, hsg, bd, fb, re);
         auto result = stateMap.insert(pair<string, shared_ptr<demogState>>(stateStr, newState));
      }
      // std::cout << *obj << std::endl;
   }
}

//return the name of the state with the largest population under age 5
string dataAQ::youngestPop() {
   double maxPop = 0;
   string maxState;

   for (auto& statePair: stateMap) {
      shared_ptr<demogState> currState = statePair.second;
      double currUnder5 = currState->getPopUnder5() / (double)currState->getPopulation();
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
      shared_ptr<demogState> currState = statePair.second;
      double currUnder18 = currState->getPopUnder18() / (double)currState->getPopulation();
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
         shared_ptr<demogState> currState = statePair.second;
         double currOver65 = currState->getPopOver65() / (double)currState->getPopulation();
         if (currOver65 > maxPop) {
            maxPop = currOver65;
            maxState = statePair.first;   
         }     
      }
      return maxState; 
}

//return the name of the state with the largest population who did not receive high school diploma
string dataAQ::underServeHS() {
   double minPop = (stateMap.at("UT"))->getHighSchoolGrad() / 
                     (double)(stateMap.at("UT"))->getPopulation();
   string maxState = "UT";

   for (auto& statePair: stateMap) {
      shared_ptr<demogState> currState = statePair.second;
      double currHs = currState->getHighSchoolGrad() / (double)currState->getPopulation();
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
      shared_ptr<demogState> currState = statePair.second;
      double currCollege = currState->getBachelorsDeg() / (double)currState->getPopulation();
      if (currCollege > maxPop) {
         maxPop = currCollege;
         maxState = statePair.first;   
      }     
   }
   return maxState; 
}

//New Queries

//return the name of the state with the lowest medium income
string dataAQ::lowestMedInc() {
   double minMedInc = (stateMap["CA"])->getMedIncome();
   string minState;

   for (auto& statePair: stateMap) {
      shared_ptr<demogState> currState = statePair.second;
      double currMedInc = currState->getMedIncome();
      if (currMedInc < minMedInc) {
         minMedInc = currMedInc;
         minState = statePair.first;   
      }     
   }
   return minState; 
}

//return the name of the state with the highest medium income
string dataAQ::highestMedInc() {
   double maxMedInc = (stateMap["AK"])->getMedIncome();
   string maxState;

   for (auto& statePair: stateMap) {
      shared_ptr<demogState> currState = statePair.second;
      double currMedInc = currState->getMedIncome();
      if (currMedInc > maxMedInc) {
         maxMedInc = currMedInc;
         maxState = statePair.first;   
      }     
   }
   return maxState; 
}

//return the name of the state with the largest percentage of the population who are foreign born
string dataAQ::mostForBorn() {
   double maxPop = 0;
   string maxState;

   for (auto& statePair: stateMap) {
      shared_ptr<demogState> currState = statePair.second;
      double currForBorn = currState->getForeignBorn() / (double)currState->getPopulation();
      if (currForBorn > maxPop) {
         maxPop = currForBorn;
         maxState = statePair.first;   
      }     
   }
   return maxState; 
}

//return the name of the state with the largest number of people per household
string dataAQ::mostPerPerHouse() {
   double maxPop = 0;
   string maxState;

   for (auto& statePair: stateMap) {
      shared_ptr<demogState> currState = statePair.second;
      double currPPH = currState->getPersonPerHouse() / (double)currState->getPopulation();
      if (currPPH > maxPop) {
         maxPop = currPPH;
         maxState = statePair.first;   
      }     
   }
   return maxState; 
}

//return the name of the state with the largest percentage of veterans
string dataAQ::mostVeterans() {
   double maxPop = 0;
   string maxState;

   for (auto& statePair: stateMap) {
      shared_ptr<demogState> currState = statePair.second;
      double currVets = currState->getVeterans() / (double)currState->getPopulation();
      if (currVets > maxPop) {
         maxPop = currVets;
         maxState = statePair.first;   
      }     
   }
   return maxState; 
}

vector<double> dataAQ::getAACasesList() {
   vector<double> retList = {};
   for (auto& policePair : allStatePoliceData) {
      shared_ptr<psCombo> currState = policePair.second;
      retList.push_back((currState->getRaceEthnicity().getBlackAlone()/currState->getNumberOfCases()));
   }
   return retList;
}

vector<double> dataAQ::getACasesList() {
   vector<double> retList = {};
   for (auto& policePair : allStatePoliceData) {
      shared_ptr<psCombo> currState = policePair.second;
      retList.push_back((currState->getRaceEthnicity().getAsianAlone()/currState->getNumberOfCases()));
   }
   return retList;
}

vector<double> dataAQ::getLCasesList() {
   vector<double> retList = {};
   for (auto& policePair : allStatePoliceData) {
      shared_ptr<psCombo> currState = policePair.second;
      retList.push_back((currState->getRaceEthnicity().getHispLat()/currState->getNumberOfCases())*100);
   }
   return retList;
}

vector<double> dataAQ::getNACasesList() {
   vector<double> retList = {};
   for (auto& policePair : allStatePoliceData) {
      shared_ptr<psCombo> currState = policePair.second;
      retList.push_back((currState->getRaceEthnicity().getAmIndianAlNative()/currState->getNumberOfCases())*100);
   }
   return retList;
}

vector<double> dataAQ::getWCasesList() {
   vector<double> retList = {};
   for (auto& policePair : allStatePoliceData) {
      shared_ptr<psCombo> currState = policePair.second;
      retList.push_back((currState->getRaceEthnicity().getWhiteAlone() / currState->getNumberOfCases())*100);
   }
   return retList;
}

vector<double> dataAQ::getWhiteAlonePercentList() {
   vector<double> retList = {};
   for (auto& pair : stateMap) {
      shared_ptr<demogState> currState = pair.second;
      retList.push_back((currState->getRaceAndEthnicity().getWhiteAlone() + 
                        currState->getRaceAndEthnicity().getWhiteNotHispLat()));
   }
   return retList;
}

vector<double> dataAQ::getLatinPercentList() {
   vector<double> retList = {};
   for (auto& pair : stateMap) {
      shared_ptr<demogState> currState = pair.second;
      retList.push_back(currState->getRaceAndEthnicity().getHispLat());
   }
   return retList;
}

vector<double> dataAQ::getAfrAmerPercentList() {
   vector<double> retList = {};
   for (auto& pair : stateMap) {
      shared_ptr<demogState> currState = pair.second;
      retList.push_back(currState->getRaceAndEthnicity().getBlackAlone());
   }
   return retList;
}

vector<double> dataAQ::getAsianPercentList() {
   vector<double> retList = {};
   for (auto& pair : stateMap) {
      shared_ptr<demogState> currState = pair.second;
      retList.push_back(currState->getRaceAndEthnicity().getAsianAlone());
   }
   return retList;
}

vector<double> dataAQ::getNativePercentList() {
   vector<double> retList = {};
   for (auto& pair : stateMap) {
      shared_ptr<demogState> currState = pair.second;
      retList.push_back(currState->getRaceAndEthnicity().getAmIndianAlNative());
   }
   return retList;
}

vector<double> dataAQ::getCaseCtList() {
   vector<double> retList = {};
   for (auto& policePair : allStatePoliceData) {
      shared_ptr<psCombo> currState = policePair.second;
      retList.push_back(currState->getNumberOfCases());
      
   }
   return retList;
}
