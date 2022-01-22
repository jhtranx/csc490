#ifndef STATE_H
#define STATE_H

#include <memory>
#include <string>
#include <iostream>
#include "demogState.h"

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

    //functions to update demogState when aggregating counties
    void updatePopulation(int increase)  {totalPopulation2020 += increase;}
    void updateFemale(double increase)  {female += increase;}
    // void updateRaceAndEthnicity()  {return raceEth;}
    void updateMedIncome(int increase)  {medIncome += increase;}
    void updateHousingUnits(int increase)  {housingUnits += increase;}
    void updateHomeOwn(double increase)  {homeOwn += increase;}
    void updatePersonPerHouse(double increase)  {personPerHouse += increase;}
    void updateVeterans(int increase)  {veterans += increase;}
    void updateHighSchoolGrad(double increase)  {highSchoolGrad += increase;}
    void updateBachelorsDeg(double increase)  {bachelorsDeg += increase;}
    void updateForeignBorn(double increase)  {foreignBorn += increase;}

private:
    string state;
    double popOver65;
    double popUnder18;
    double popUnder5;
    int totalPopulation2020;
    double female;
    raceAndEthnicity raceEth;
    int medIncome;
    int housingUnits;
    double homeOwn;
    double personPerHouse;
    int veterans;
    double highSchoolGrad;
    double bachelorsDeg;
    double foreignBorn;
        

};
#endif
