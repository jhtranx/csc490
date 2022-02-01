#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "demogData.h"
#include "parse.h"
#include "dataAQ.h"

using namespace std;

int main() {

    dataAQ theAnswers;

    //read in a csv file and create a vector of objects representing each counties data
    std::vector<shared_ptr<demogData>> theData = read_csv(
            "county_demographics.csv", DEMOG);


    std::vector<shared_ptr<psData>> thePoliceData = read_csvPolice(
            "fatal-police-shootings-data.csv", POLICE);

     //debug print out if needed left for your use in testing
    /*
    int i = 0;
    for (const auto &obj : thePoliceData) {
        std::cout << *obj << std::endl;
        i++;
        if (i > 15)
            break;
    }

    i = 0;
    for (const auto &obj : theData) {
        std::cout << *obj << std::endl;
        i++;
        if (i > 15)
            break;
    }
     */
    
    theAnswers.createStateData(theData);
    theAnswers.createStatePoliceData(thePoliceData);

    theAnswers.reportTopTenStatesPS();
    theAnswers.reportBottomTenStatesHomeOwn();
    
    return 0;
}

