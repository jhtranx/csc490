#ifndef STATE_H
#define STATE_H

#include <memory>
#include <string>
#include <iostream>
#include "demogData.h"

/*
  class to represent state data - fairly redundent at this point but will use
  inheritence later - FILL IN
*/
class demogState {
  public:
    friend std::ostream& operator<<(std::ostream &out, const demogState &SD);
   //FILL IN
    public:
    demogState(string inS, double in65, double in18,
        double in5, int totPop20, double f, raceAndEthnicity re, 
        float mi, int hu, double ho, 
        double pph, int vets, double hsg, double bd, 
        double fb) :
            state(inS), popOver65(in65), popUnder18(in18),
            popUnder5(in5), totalPopulation2020(totPop20), female(f), raceEth(re), medIncome(mi), housingUnits(hu), homeOwn(ho), 
            personPerHouse(pph), veterans(vets), highSchoolGrad(hsg), bachelorsDeg(bd), 
            foreignBorn(fb) {}

    // Getter
    // string getCounty() const {return county;}
    string getState() const {return state;}
    int getPopulation() const {return totalPopulation2020;}
    double getFemale() const {return female;}
    raceAndEthnicity getRaceAndEthnicity() const {return raceEth;}
    float getMedIncome() const {return medIncome;}
    int getHousingUnits() const {return housingUnits;}
    double getHomeOwn() const {return homeOwn;}
    double getPersonPerHouse() const {return personPerHouse ;}
    int getVeterans() const {return veterans;}
    double getHighSchoolGrad() const {return highSchoolGrad;}
    double getBachelorsDeg() const {return bachelorsDeg;}
    double getForeignBorn() const {return foreignBorn;}

  //  friend std::ostream& operator<<(std::ostream &out, const demogData &DD);

private:
    // const string county;
    const string state;
    const double popOver65;
    const double popUnder18;
    const double popUnder5;
    const int totalPopulation2020;
    const double female;
    raceAndEthnicity raceEth;
    int medIncome;
    int housingUnits;
    double homeOwn; //check if right
    double personPerHouse;
    int veterans;
    double highSchoolGrad;
    double bachelorsDeg;
    double foreignBorn;
        

};
#endif
