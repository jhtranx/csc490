#ifndef POLICECOMBODATA_H
#define POLICECOMBODATA_H

#include "raceDemogData.h"
#include "psData.h"
#include "raceAndEthnicity.h"

using namespace std;

class psCombo {
public:
    psCombo(string inState, int inMentalI, int inUnarmed, 
            int inArmedToy, int inBodyCam, int inCase) : 
            state(inState), mentalIllnessCt(inMentalI), unarmedCt(inUnarmed), 
            armedToyCt(0), bodyCamCt(0), caseCt(0) {}
    psCombo(string inState) : 
            state(inState), mentalIllnessCt(0), unarmedCt(0), 
            armedToyCt(0), bodyCamCt(0), caseCt(0), raceEth(raceAndEthnicity()) {}
    
    
    int getNumMentalI() {return mentalIllnessCt;} //total count “TRUE”
    int getUnArmedCount() {return unarmedCt;} //total count blank, ‘unarmed’
    int getArmedToy() {return armedToyCt;}  //total count ’toy weapon’
    int getNumBodyCam() {return bodyCamCt;} //total count “TRUE”
    int getNumberOfCases() {return caseCt;}//total number for a region
    string getRegion() {return state;} //return state for p2
    raceAndEthnicity getRaceEthnicity() {return raceEth;}

    void incRaceEth(string race) {
        if (race == "W") {raceEth.incWhiteAlone();}
        else if (race == "B") {raceEth.incBlackAlone();}
        else if (race == "A") {raceEth.incAsianAlone();}
        else if (race == "N") {raceEth.incHawaiianPacIsland();}
        else if (race == "H") {raceEth.incHispLat();}
        else if (race == "O") {raceEth.incOther();}
        else if (race == "None") {raceEth.incUnknown();}
    }
    void incNumMentalIllness() {mentalIllnessCt += 1;}//total count “TRUE”
    void incUnArmedCount() {unarmedCt += 1;} //total count blank, ‘unarmed’
    void incArmedToy() {armedToyCt += 1;}  //total count ’toy weapon’
    void incNumBodyCam() {bodyCamCt += 1;} //total count “TRUE”
    void incNumberOfCases() {caseCt += 1;}//total number for a region

    friend std::ostream& operator<<(std::ostream &out, const psCombo& PD);

private:
    const string state;
    int mentalIllnessCt;
    int unarmedCt;
    int armedToyCt;
    int bodyCamCt;
    int caseCt;
    raceAndEthnicity raceEth;
};

#endif