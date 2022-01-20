#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "demogData.h"
#include "parse.h"
#include "dataAQ.h"

using namespace std;

int main() {

    //cool to warm color map 
    std::array<color, 10> colorMap; 
    colorMap[0] = color(91, 80, 235); //cool 
    colorMap[1] = color(95, 166, 245); 
    colorMap[2] = color(99, 223, 220); 
    colorMap[3] = color(95, 245, 155); 
    colorMap[4] = color(128, 235, 96); //midway 
    colorMap[5] = color(235, 235, 75); 
    colorMap[6] = color(245, 213, 91); 
    colorMap[7] = color(223, 170, 94); 
    colorMap[8] = color(245, 134, 91); 
    colorMap[9] = color(235, 91, 101); //warm  

    dataAQ theAnswers;

    //read in a csv file and create a vector of objects representing each counties data
    std::vector<shared_ptr<demogData>> theData = read_csv(
            "county_demographics.csv", DEMOG);

    std::vector<int> foreignBorn;
    std::vector<int> hsAndUp;
    std::vector<int> baAndUp;

     //debug print out - uncomment if you want to double check your data

    for (const auto &obj : theData) {
        std::cout << *obj << std::endl;

        foreignBorn.push_back(obj->getForeignBorn());
        hsAndUp.push_back(obj->getHighSchoolGrad());
        baAndUp.push_back(obj->getBachelorsDeg());
    }

    int maxFb = 0;
    int maxHs = 0;
    int maxBa = 0;
    for (int i : foreignBorn) {
        if (i > maxFb)
            maxFb = i;
    }

    cout << maxFb;

    theAnswers.createStateData(theData);

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

