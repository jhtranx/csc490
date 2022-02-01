
#include "dataAQ.h"
#include "psData.h"
#include "parse.h"
#include <iostream>
#include "tddFuncs.h"
using namespace std;

int main() {
  cout << "Testing state data police shooting..." << endl;

	dataAQ theAnswers;

    //read in a csv file and create a vector of objects representing each counties data
    std::vector<shared_ptr<psData>> thePoliceData = read_csvPolice(
            "police_shootings_cleaned.csv", POLICE);

    theAnswers.createStatePoliceData(thePoliceData);

    shared_ptr<psCombo> CA_PSData = theAnswers.getStatePoliceData("CA");
    
    /* expect these to be tested */
    /*
  	ASSERT_EQUALS(xxx, CA_PSData->getNumMentalI() );
    ASSERT_EQUALS(xxx, CA_PSData->getUnArmedCount() );
    ASSERT_EQUALS(xxx, CA_PSData->getArmedToy() );
    ASSERT_EQUALS(xxx, CA_PSData->getNumBodyCam() );
    ASSERT_EQUALS(xxx, CA_PSData->getNumberOfCases() );
    */



  return 0;
}
