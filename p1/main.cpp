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
   cout << "State Under 5: " << theAnswers.youngestPop() << endl; 

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

   cout << "*** the state with largest percent of the population below the poverty line**" << endl;
   query = theAnswers.belowPoverty();
   cout << "Name of state: " << query << endl;
   if (theAnswers.getStateData(query) != nullptr){
      cout << *(theAnswers.getStateData(query)) << endl;
   } else{
      cout << "Did you read the lab instructions?" << endl;
   }
   return 0;
}

