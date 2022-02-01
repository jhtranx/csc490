#ifndef POLICECOMBODATA_H
#define POLICECOMBODATA_H

#include "raceDemogData.h"
#include "psData.h"

using namespace std;

class psCombo {
public:
    psCombo(string inS) : state(inS) {} //add
    
    //complete these
    int getNumMentalI() ;//total count “TRUE”
    int getUnArmedCount(); //total count blank, ‘unarmed’
    int getArmedToy();  //total count ’toy weapon’
    int getNumBodyCam() ; //total count “TRUE”
    int getNumberOfCases() ;//total number for a region
    string getRegion() ; //return state for p2

    //add any others needed

    friend std::ostream& operator<<(std::ostream &out, const psCombo& PD);

protected:
    const string state;
    //add others
};

#endif