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
        double in5, int totPop20, string ct, string st, int pop, 
        string r, string eth, float mi, int ho, int pph, int vets, 
        int hsg, int bd, double fb) :
            name(inN), state(inS), popOver65(in65), popUnder18(in18),
            popUnder5(in5), totalPopulation2020(totPop20), county(ct), state(st), population(pop), race(r),
            ethnicity(eth), medIncome(mi), homeOwn(ho), personPerHouse(pph), veterans(vets), highSchoolGrad(hsg),
            bachelorsDeg(bd), foreignBorn(fb) {}

    string getName() const { return name; }

   friend std::ostream& operator<<(std::ostream &out, const demogData &DD);

private:
    const string name;
    const string state;
    const double popOver65;
    const double popUnder18;
    const double popUnder5;
    const int totalPopulation2020;

    demogState(string ct, string st, int pop, string r, string eth, float mi, int ho, int pph, int vets, int hsg, int bd, double fb) {
        county = ct;
        state = st;
        population = pop;
        race = r;
        ethnicity = eth;
        medIncome = mi;
        homeOwn = ho; //check if right
        personPerHouse = pph;
        veterans = vets;
        highSchoolGrad = hsg;
        bachelorsDeg = bd;
        foreignBorn = fb;
    }

   // Setter
    void setCounty(string ct) {county = ct;}
    void setState(string st) {state = st;}
    void setPopulation(int p) {population = p;}
    void setRace(string r) {race = r;}
    void setEthnicity(string e) {ethnicity = e;}
    void setMedIncome(int m) {medIncome = m;}
    void setHomeOwn(double h) {homeOwn = h;}
    void setPersonPerHouse(double pph) {personPerHouse = pph;}
    void setVeterans(int v) {veterans = v;}
    void setHighSchoolGrad(double hsg) {highSchoolGrad = hsg;}
    void setBachelorsDeg(double bd) {bachelorsDeg = bd;}
    void setForeignBorn(double fb) {foreignBorn = fb;}

    // Getter
    string getCounty() {return county;}
    string getState() {return state;}
    int getPopulation() {return population;}
    string getRace() {return race;}
    string getEthnicity() {return ethnicity;}
    float getMedIncome() {return medIncome;}
    int getHomeOwn() {return homeOwn;}
    int getPersonPerHouse() {return personPerHouse ;}
    int getVeterans() {return veterans;}
    int getHighSchoolGrad() {return highSchoolGrad;}
    int getBachelorsDeg() {return bachelorsDeg;}
    double getForeignBorn() {return foreignBorn;}

	private:
        string county;
        string state;
        int population;
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
