
#include "dataAQ.h"
#include "parse.h"
#include <iostream>
#include "tddFuncs.h"
using namespace std;

int main() {
  cout << "Testing one state data..." << endl;

	dataAQ theAnswers;

    //read in a csv file and create a vector of objects representing each counties data
    std::vector<shared_ptr<demogData>> theData = read_csv(
            "county_demographics.csv", DEMOG);

    theAnswers.createStateData(theData);

    string noHS = theAnswers.underServeHS();
    ASSERT_EQUALS("CA", noHS);

    cout << *(theAnswers.getStateData(noHS)) << endl;


  return 0;
}
