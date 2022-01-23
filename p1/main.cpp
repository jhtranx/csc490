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
         "county_demographics.csv", DEMOG);

   //debug print out - uncomment if you want to double check your data
   theAnswers.createStateData(theData);
   cout << "MAPSIZE: " << theAnswers.getMap().size() << endl;
   cout << "AK TOT POP: " << theAnswers.getMap().at("AK").getPopulation() << endl; 

   //one example of how to print required - ADD OTHERS
   cout << "*** the state that needs the most pre-schools**" << endl;
   string needPK = theAnswers.youngestPop();
   cout << "Name of state: " << needPK << endl;
   if (theAnswers.getStateData(needPK) != nullptr){
      cout << *(theAnswers.getStateData(needPK)) << endl;
   } else{
      cout << "Did you read the lab instructions?" << endl;
   }

   //NOW fill in these too
   cout << "*** the state that needs the most high schools**" << endl;
   //FILL IN 

   cout << "*** the state that needs the most vaccines**" << endl;
   //FILL IN 

   cout << "*** the state that needs the most help with education**" << endl;
   //FILL IN 

   cout << "*** the state with most college grads**" << endl;
   //FILL IN 

   cout << "*** the state with largest percent of the population below the poverty line**" << endl;
   //FILL IN

   return 0;
}

