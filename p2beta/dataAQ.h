#ifndef DATAAQ_H
#define DATAAQ_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "demogState.h"
#include "demogData.h"
#include "psCombo.h"

/*
  data aggregator and query for testing
*/
class dataAQ {
   public:
      dataAQ();

      void createStateData(std::vector<shared_ptr<demogData>> theData);
      void createStatePoliceData(std::vector<shared_ptr<psData>> theData);

      /* necessary function to aggregate the data - this CAN and SHOULD vary per
         student - depends on how they map, etc. */

      //return the name of the state with the largest population under age 5
      string youngestPop(); 
      //return the name of the state with the largest population under age 18
      string teenPop(); 
      //return the name of the state with the largest population over age 65
      string wisePop(); 
      //return the name of the state with the largest population who did not finish high school
      string underServeHS(); 
      //return the name of the state with the largest population who completed college
      string collegeGrads(); 
      //return the name of the state with the largest population below the poverty line
      string belowPoverty(); 

      //New Queries

      //return the name of the state with the lowest medium income
      string lowestMedInc();
      //return the name of the state with the highest medium income
      string highestMedInc();
      //return the name of the state with the largest percentage of the population who are foreign born
      string mostForBorn();
      //return the name of the state with the largest number of people per household
      string mostPerPerHouse();
      //return the name of the state with the largest percentage of veterans
      string mostVeterans();

      //sort and report the top ten states in terms of number of police shootings 
      void reportTopTenStatesPS();
      void reportBottomTenStatesHomeOwn();

      vector<double> getAACasesList();
      vector<double> getNACasesList();
      vector<double> getACasesList();
      vector<double> getWCasesList();
      vector<double> getLCasesList();
      vector<double> getCaseCtList();

      vector<double> getWhiteAlonePercentList();
      vector<double> getNativePercentList();
      vector<double> getAsianPercentList();
      vector<double> getLatinPercentList();
      vector<double> getAfrAmerPercentList();


      shared_ptr<demogState> getStateData(string stateName) { return stateMap[stateName]; }
      shared_ptr<psCombo> getStatePoliceData(string stateName) { return allStatePoliceData[stateName]; }
      
      friend std::ostream& operator<<(std::ostream &out, const dataAQ &stateMap);

   //this quarter restriction
   private:
      std::map<string, shared_ptr<psCombo>> allStatePoliceData;    
      std::map<string, shared_ptr<demogState>> stateMap;
      

};
#endif
