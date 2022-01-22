#ifndef STATE_H
#define STATE_H

#include <memory>
#include <string>
#include <iostream>
#include "demogState.h"
#include "raceAndEthnicity.h"

using namespace std;
/*
  class to represent state data - fairly redundent at this point but will use
  inheritence later - FILL IN
*/
class demogState {
  public:
    friend std::ostream& operator<<(std::ostream &out, const demogState &SD);
   //FILL IN
    public:
    demogState(string inS, int in65, int in18,
        int in5, int totPop20, int f, raceAndEthnicity re, 
        int mi, int hu, int ho, 
        int pph, int vets, int hsg, int bd, 
        int fb) :
            state(inS), popOver65(in65), popUnder18(in18),
            popUnder5(in5), totalPopulation2020(totPop20), female(f), raceEth(re), medIncome(mi), housingUnits(hu), homeOwn(ho), 
            personPerHouse(pph), veterans(vets), highSchoolGrad(hsg), bachelorsDeg(bd), 
            foreignBorn(fb) {}

    // Getter
    // string getCounty() const {return county;}
    string getState() const {return state;}
    int getPopOver65() const {return popOver65;}
    int getPopUnder18() const {return popUnder18;}
    int getPopUnder5() const {return popUnder5;}
    int getPopulation() const {return totalPopulation2020;}
    int getFemale() const {return female;}
    raceAndEthnicity getRaceAndEthnicity() const {return raceEth;}
    int getMedIncome() const {return medIncome;}
    int getHousingUnits() const {return housingUnits;}
    int getHomeOwn() const {return homeOwn;}
    int getPersonPerHouse() const {return personPerHouse ;}
    int getVeterans() const {return veterans;}
    int getHighSchoolGrad() const {return highSchoolGrad;}
    int getBachelorsDeg() const {return bachelorsDeg;}
    int getForeignBorn() const {return foreignBorn;}

  //  friend std::ostream& operator<<(std::ostream &out, const demogData &DD);

    //functions to update demogState when aggregating counties
    void updatePopulation(int increase)  {totalPopulation2020 += increase;}
    void updatePopOver65(int increase)  {popOver65 += increase;}
    void updatePopUnder18(int increase)  {popUnder18 += increase;}
    void updatePopUnder5(int increase)  {popUnder5 += increase;}
    void updateFemale(int increase)  {female += increase;}
    // void updateRaceAndEthnicity()  {return raceEth;}
    void updateMedIncome(int increase)  {medIncome += increase;}
    void updateHousingUnits(int increase)  {housingUnits += increase;}
    void updateHomeOwn(int increase)  {homeOwn += increase;}
    void updatePersonPerHouse(int increase)  {personPerHouse += increase;}
    void updateVeterans(int increase)  {veterans += increase;}
    void updateHighSchoolGrad(int increase)  {highSchoolGrad += increase;}
    void updateBachelorsDeg(int increase)  {bachelorsDeg += increase;}
    void updateForeignBorn(int increase)  {foreignBorn += increase;}

private:
    string state;
    int popOver65;
    int popUnder18;
    int popUnder5;
    int totalPopulation2020;
    int female;
    raceAndEthnicity raceEth;
    int medIncome;
    int housingUnits;
    int homeOwn;
    int personPerHouse;
    int veterans;
    int highSchoolGrad;
    int bachelorsDeg;
    int foreignBorn;
        

};
#endif
