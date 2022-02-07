
#include "dataAQ.h"
#include "parse.h"
#include <iostream>
#include "tddFuncs.h"
using namespace std;

int main() {
  cout << "Testing PS sort..." << endl;

    dataAQ theAnswers;

    //read in a csv file and create a vector of objects representing each counties data
    std::vector<shared_ptr<demogData>> theDemogData = read_csv(
            "county_demographics.csv", DEMOG);

    std::vector<shared_ptr<psData>> thePoliceData = read_csvPolice(
            "police_shootings_cleaned.csv", POLICE);

    theAnswers.createStateData(theDemogData);
    theAnswers.createStatePoliceData(thePoliceData);

    theAnswers.reportTopTenStatesPS();

  return 0;
}
