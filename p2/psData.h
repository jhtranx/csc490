#ifndef POLICE_H
#define POLICE_H

#include <string>
#include <iostream>
#include <utility>

using namespace std;

/*
   class to represent police shooting data
   from Washington Post
*/
class psData {
   public:

   psData(string inState, string inName, string inCity, raceEthnicity inRaceEth, 
         bool inSignsOfMentalIllness, string inArmed, bool inBodyCam) : 
         state(inState), name(inName), city(inCity), raceEth(inRaceEth),
         signsOfMentalIllness(inSignsOfMentalIllness), armed(inArmed), bodyCam(inBodyCam) {}

   string getState() const { return state; }
   string getName() const { return name; }
   string getCity() const { return city; }
   string getRaceEthnicity() const { return raceEth; }
   bool hasSignsOfMentalIllness() const { return signsOfMentalIllness; }
   string getArmed() const { return armed; }
   bool hasBodyCam() const { return bodyCam; }

   friend std::ostream& operator<<(std::ostream &out, const psData &PD);

private:
   const string state;
   const string name; 
   const string city;
   const string raceEth;
   const bool signsOfMentalIllness;
   const string armed;
   const bool bodyCam;
};

#endif
