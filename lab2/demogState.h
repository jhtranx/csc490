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
	//DATA here
  //  public:
    

};
#endif
