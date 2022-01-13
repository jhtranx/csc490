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
   //FILL IN
   demogState(){}
  friend std::ostream& operator<<(std::ostream &out, const demogState &SD);
	private:
        const string county;
        const string state;
        const int population;
        const string race;
        const string ethnicity;
        const float medIncome;
        const int homeOwn; //check if right
        const int personPerHouse;
        const int veterans;
        const int highSchoolGrad;
        const int bachelorsDeg;
        const int foreignBorn;
	//DATA here
   public:
    // Setter
    void setCounty(String ct) {county = ct;}
    void setState(String st) {salary = st;}
    void setPopulation(int p) {population = p;}
    void setRace(String r) {race = r;}
    void setEthnicity(String e) {ethnicity = e;}
    void setMedIncome(float m) {medIncome = m;}
    void setHomeOwn(int h) {homeOwn = h;}
    void setPersonPerHouse(int pph) {personPerHouse = pph;}
    void setVeterans(int v) {veterans = v;}
    void setHighSchoolGrad(int hsg) {highSchoolGrad = hsg;}
    void setBachelorsDeg(int bd) {bachelorsDeg = bd;}
    void setForeignBorn(int fb) {foreignBorn = fb;}

    // Getter
    int getSalary() {return salary;}
    void getCounty() {return county;}
    void getState() {return salary;}
    void getPopulation() {return population;}
    void getRace() {return race;}
    void getEthnicity() {return ethnicity;}
    void getMedIncome() {return medIncome;}
    void getHomeOwn() {return homeOwn;}
    void getPersonPerHouse() {return personPerHouse ;}
    void getVeterans() {return veterans;}
    void getHighSchoolGrad() {return highSchoolGrad;}
    void getBachelorsDeg() {return bachelorsDeg;}
    void getForeignBorn() {return foreignBorn;}

};
#endif
