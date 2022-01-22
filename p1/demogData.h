#ifndef DEMOG_H
#define DEMOG_H

#include <string>
#include<iostream>
#include "raceAndEthnicity.h"

using namespace std;

/*
  class to represent county demographic data
  from CORGIS - fill in with any data we agree as a class we want to include
*/
class demogData {
  public:
    demogData(string inN, string inS, double in65, double in18,
        double in5, int totPop20, double f, raceAndEthnicity re, 
        float mi, int hu, double ho, 
        double pph, int vets, double hsg, double bd, 
        double fb) :
            county(inN), state(inS), popOver65(in65), popUnder18(in18),
            popUnder5(in5), totalPopulation2020(totPop20), female(f), raceEth(re), medIncome(mi), housingUnits(hu), homeOwn(ho), 
            personPerHouse(pph), veterans(vets), highSchoolGrad(hsg), bachelorsDeg(bd), 
            foreignBorn(fb) {}

    // Getter
    string getCounty() const {return county;}
    string getState() const {return state;}
    double getPopOver65() const {return popOver65;}
    double getPopUnder18() const {return popUnder18;}
    double getPopUnder5() const {return popUnder5;}
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

   friend std::ostream& operator<<(std::ostream &out, const demogData &DD);

private:
    const string county;
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
