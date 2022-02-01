
#include "dataAQ.h"
#include "parse.h"
#include <iostream>
#include "tddFuncs.h"
using namespace std;

int main() {
  cout << "Testing state data aggregation query..." << endl;

	dataAQ theAnswers;

    //read in a csv file and create a vector of objects representing each counties data
  std::vector<shared_ptr<demogData>> theData = read_csv(
            "county_demographics_2014_EDIT2.csv", DEMOG);

    theAnswers.createStateData(theData);

    string youngestPop = theAnswers.youngestPop();
  	ASSERT_EQUALS("UT",youngestPop);

  	string bachelors = theAnswers.collegeGrads();
  	ASSERT_EQUALS("DC",bachelors);

    string lowMI = theAnswers.lowestMedIncome();
    ASSERT_EQUALS("MS",lowMI);

    string mostFB = theAnswers.mostForBorn();
    ASSERT_EQUALS("CA",mostFB);

    string mostPPH = theAnswers.mostPerPerHouse();
    ASSERT_EQUALS("UT",mostPPH);

    string mostVeterans = theAnswers.mostVeterans();
    ASSERT_EQUALS("AK",mostVeterans);

  return 0;
}
