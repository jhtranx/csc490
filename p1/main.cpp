#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include "demogData.h"
#include "demogState.h"
#include "parse.h"
#include "dataAQ.h"

using namespace std;

int main() {

   dataAQ theAnswers;

   //read in a csv file and create a vector of objects representing each counties data
   std::vector<shared_ptr<demogData>> theData = read_csv(
         "county_demographics2014.csv", DEMOG);

   //debug print out - uncomment if you want to double check your data
   theAnswers.createStateData(theData);
   cout << "MAPSIZE: " << theAnswers.getMap().size() << endl;
   cout << "AK TOT POP: " << theAnswers.getMap().at("AK").getPopulation() << endl; 
   cout << "STATE UNDER 5: " << theAnswers.youngestPop() << endl; 
   cout << "TOT COUNTIES IN AK: " << theAnswers.getMap().at("AK").getTotCounties() << endl;
   cout << "TOT COUNTIES IN CA: " << theAnswers.getMap().at("CA").getTotCounties() << endl;
   cout << "AK MED INCOME: " << theAnswers.getMap().at("AK").getMedIncome() << " EXPECTED: 62611.34483" << endl;
   cout << "CA MED INCOME: " << theAnswers.getMap().at("CA").getMedIncome() << " EXPECTED: 55558.01724" << endl;
   cout << "AK PPH: " << theAnswers.getMap().at("AK").getPersonPerHouse() << " EXPECTED: 2.796" << endl;
   cout << endl;

   //one example of how to print required - ADD OTHERS
   cout << "*** the state that needs the most pre-schools**" << endl;
   string query = theAnswers.youngestPop();
   cout << "Name of state: " << query << endl;
   if (theAnswers.getStateData(query) != nullptr){
      cout << *(theAnswers.getStateData(query)) << endl;
   } else{
      cout << "Did you read the lab instructions?" << endl;
   }

   //NOW fill in these too
   cout << "*** the state that needs the most high schools**" << endl;
   query = theAnswers.teenPop();
   cout << "Name of state: " << query << endl;
   if (theAnswers.getStateData(query) != nullptr){
      cout << *(theAnswers.getStateData(query)) << endl;
   } else{
      cout << "Did you read the lab instructions?" << endl;
   } 

   cout << "*** the state that needs the most vaccines**" << endl;
   query = theAnswers.wisePop();
   cout << "Name of state: " << query << endl;
   if (theAnswers.getStateData(query) != nullptr){
      cout << *(theAnswers.getStateData(query)) << endl;
   } else{
      cout << "Did you read the lab instructions?" << endl;
   }

   cout << "*** the state that needs the most help with education**" << endl;
   query = theAnswers.underServeHS();
   cout << "Name of state: " << query << endl;
   if (theAnswers.getStateData(query) != nullptr){
      cout << *(theAnswers.getStateData(query)) << endl;
   } else{
      cout << "Did you read the lab instructions?" << endl;
   }

   cout << "*** the state with most college grads**" << endl;
   query = theAnswers.collegeGrads();
   cout << "Name of state: " << query << endl;
   if (theAnswers.getStateData(query) != nullptr){
      cout << *(theAnswers.getStateData(query)) << endl;
   } else{
      cout << "Did you read the lab instructions?" << endl;
   }

   // cout << "*** the state with largest percent of the population below the poverty line**" << endl;
   // query = theAnswers.belowPoverty();
   // cout << "Name of state: " << query << endl;
   // if (theAnswers.getStateData(query) != nullptr){
   //    cout << *(theAnswers.getStateData(query)) << endl;
   // } else{
   //    cout << "Did you read the lab instructions?" << endl;
   // }

   //New Queries
   cout << "*** the state with lowest medium income**" << endl;
   query = theAnswers.lowestMedInc();
   cout << "Name of state: " << query << endl;
   if (theAnswers.getStateData(query) != nullptr){
      cout << *(theAnswers.getStateData(query)) << endl;
   } else{
      cout << "Did you read the lab instructions?" << endl;
   }
   return 0;

   cout << "*** the state with highest medium income**" << endl;
   query = theAnswers.highestMedInc();
   cout << "Name of state: " << query << endl;
   if (theAnswers.getStateData(query) != nullptr){
      cout << *(theAnswers.getStateData(query)) << endl;
   } else{
      cout << "Did you read the lab instructions?" << endl;
   }
   return 0;

   cout << "*** the state with largest percentage of the population who are foreign born**" << endl;
   query = theAnswers.mostForBorn();
   cout << "Name of state: " << query << endl;
   if (theAnswers.getStateData(query) != nullptr){
      cout << *(theAnswers.getStateData(query)) << endl;
   } else{
      cout << "Did you read the lab instructions?" << endl;
   }
   return 0;

   cout << "*** the state with largest number of people per household**" << endl;
   query = theAnswers.mostPerPerHouse();
   cout << "Name of state: " << query << endl;
   if (theAnswers.getStateData(query) != nullptr){
      cout << *(theAnswers.getStateData(query)) << endl;
   } else{
      cout << "Did you read the lab instructions?" << endl;
   }
   return 0;

   cout << "*** the state with largest percentage of veterans**" << endl;
   query = theAnswers.mostVeterans();
   cout << "Name of state: " << query << endl;
   if (theAnswers.getStateData(query) != nullptr){
      cout << *(theAnswers.getStateData(query)) << endl;
   } else{
      cout << "Did you read the lab instructions?" << endl;
   }
   return 0;
}

