#ifndef DEMOG_H
#define DEMOG_H

#include <string>
#include<iostream>

using namespace std;

/*
  class to represent county demographic data
  from CORGIS - fill in with any data we agree as a class we want to include
*/
class demogData {
  public:
    demogData(string inN, string inS, double in65, double in18,
        double in5, int totPop20,
        string r, string eth, float mi, int ho, int pph, int vets, 
        int hsg, int bd, double fb) :
            county(inN), state(inS), popOver65(in65), popUnder18(in18),
            popUnder5(in5), totalPopulation2020(totPop20), race(r),
            ethnicity(eth), medIncome(mi), homeOwn(ho), personPerHouse(pph), veterans(vets), highSchoolGrad(hsg),
            bachelorsDeg(bd), foreignBorn(fb) {}

    // Getter
    string getCounty() const {return county;}
    string getState() const {return state;}
    int getPopulation() const {return totalPopulation2020;}
    string getRace() const {return race;}
    string getEthnicity() const {return ethnicity;}
    float getMedIncome() const {return medIncome;}
    int getHomeOwn() const {return homeOwn;}
    int getPersonPerHouse() const {return personPerHouse ;}
    int getVeterans() const {return veterans;}
    int getHighSchoolGrad() const {return highSchoolGrad;}
    int getBachelorsDeg() const {return bachelorsDeg;}
    double getForeignBorn() const {return foreignBorn;}

   friend std::ostream& operator<<(std::ostream &out, const demogData &DD);

private:
    const string county;
    const string state;
    const double popOver65;
    const double popUnder18;
    const double popUnder5;
    const int totalPopulation2020;
    string race;
    string ethnicity;
    int medIncome;
    double homeOwn; //check if right
    double personPerHouse;
    int veterans;
    double highSchoolGrad;
    double bachelorsDeg;
    double foreignBorn;
        

};
#endif
