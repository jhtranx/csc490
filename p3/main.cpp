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

   //New Queries
   cout << "*** the state with lowest medium income**" << endl;
   query = theAnswers.lowestMedInc();
   cout << "Name of state: " << query << endl;
   if (theAnswers.getStateData(query) != nullptr){
      cout << *(theAnswers.getStateData(query)) << endl;
   } else{
      cout << "Did you read the lab instructions?" << endl;
   }

   cout << "*** the state with highest medium income**" << endl;
   query = theAnswers.highestMedInc();
   cout << "Name of state: " << query << endl;
   if (theAnswers.getStateData(query) != nullptr){
      cout << *(theAnswers.getStateData(query)) << endl;
   } else{
      cout << "Did you read the lab instructions?" << endl;
   }

   cout << "*** the state with largest percentage of the population who are foreign born**" << endl;
   query = theAnswers.mostForBorn();
   cout << "Name of state: " << query << endl;
   if (theAnswers.getStateData(query) != nullptr){
      cout << *(theAnswers.getStateData(query)) << endl;
   } else{
      cout << "Did you read the lab instructions?" << endl;
   }
   
   cout << "*** the state with largest number of people per household**" << endl;
   query = theAnswers.mostPerPerHouse();
   cout << "Name of state: " << query << endl;
   if (theAnswers.getStateData(query) != nullptr){
      cout << *(theAnswers.getStateData(query)) << endl;
   } else{
      cout << "Did you read the lab instructions?" << endl;
   }

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

