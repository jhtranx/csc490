#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include "demogData.h"
#include "parse.h"
#include "dataAQ.h"

using namespace std;

int main() {

    dataAQ theAnswers;

    //read in a csv file and create a vector of objects representing each counties data
    std::vector<shared_ptr<demogData>> theData = read_csv(
            "county_demographics.csv", DEMOG);

     //debug print out - uncomment if you want to double check your data

    map <string, demogState> stateMap;

    for (const auto &obj : theData) {
        string stateStr = obj->getState();

        string inS = obj->getState();
        int in65 = round((obj->getPopOver65() / 100) * obj->getPopulation());
        int in18 = round((obj->getPopUnder18() / 100) * obj->getPopulation());
        int in5 = round((obj->getPopUnder5() / 100) * obj->getPopulation());
        int totPop20 = obj->getPopulation();

        int f = round((obj->getFemale() / 100) * obj->getPopulation());
        int mi = obj->getMedIncome();
        int hu = obj->getHousingUnits();
        int ho = round((obj->getHomeOwn() / 100) * obj->getPopulation());
        int pph = round((obj->getPersonPerHouse() / 100) * obj->getHousingUnits());
        int v = obj->getVeterans();
        int hsg = round((obj->getHighSchoolGrad() / 100) * obj->getPopulation());
        int bd = round((obj->getBachelorsDeg() / 100) * obj->getPopulation());
        int fb = round((obj->getForeignBorn() / 100) * obj->getPopulation());

        if (stateMap.find(stateStr) != stateMap.end()) {
            stateMap.at(stateStr).updatePopOver65(in65);
            stateMap.at(stateStr).updatePopUnder18(in18);
            stateMap.at(stateStr).updatePopUnder5(in5);
            stateMap.at(stateStr).updatePopulation(totPop20);
            stateMap.at(stateStr).updateFemale(f);
            stateMap.at(stateStr).updateMedIncome(mi);
            stateMap.at(stateStr).updateHousingUnits(hu);
            stateMap.at(stateStr).updateHomeOwn(ho);
            stateMap.at(stateStr).updatePersonPerHouse(pph);
            stateMap.at(stateStr).updateVeterans(v);
            stateMap.at(stateStr).updateHighSchoolGrad(hsg);
            stateMap.at(stateStr).updateBachelorsDeg(bd);
            stateMap.at(stateStr).updateForeignBorn(fb);
        }
        else {
            

            demogState newState = demogState(inS, in65, in18, in5, totPop20, f, mi, hu, ho, pph, v, hsg, bd, fb);
        }

        std::cout << *obj << std::endl;

        
        

    }

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

