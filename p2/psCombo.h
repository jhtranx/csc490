#ifndef POLICECOMBODATA_H
#define POLICECOMBODATA_H

#include "raceDemogData.h"
#include "psData.h"

using namespace std;

class psCombo {
public:
    psCombo(string inState) : 
            state(inS), mentalIllnessCt(0), unarmedCt(0), 
            armedToyCt(0), bodyCamCt(0), caseCt(0), raceEth(raceEthnicity()){}
    
    int getNumMentalI() ;//total count “TRUE”
    int getUnArmedCount(); //total count blank, ‘unarmed’
    int getArmedToy();  //total count ’toy weapon’
    int getNumBodyCam() ; //total count “TRUE”
    int getNumberOfCases() ;//total number for a region
    string getRegion() ; //return state for p2

    friend std::ostream& operator<<(std::ostream &out, const psCombo& PD);

protected:
    const string state;
    int mentalIllnessCt;
    int unarmedCt;
    int armedToyCt;
    int bodyCamCt;
    int caseCt;
    raceEthnicity raceEth;
};

#endif