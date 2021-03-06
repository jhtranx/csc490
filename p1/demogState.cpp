#include "demogState.h"
#include "demogData.h"
#include <sstream>
#include <string>
#include <assert.h>
#include <iomanip>
#include <cmath>

//add member functions here

/* print state data - as aggregate of all the county data */
std::ostream& operator<<(std::ostream &out, const demogState&SD) {
   out << "State Info: " << SD.getState() << endl;
   out << "Number of Counties: " << SD.getTotCounties() << endl;
   out << "Population info:" << endl;
   out << "(% over 65): " << (double)SD.getPopOver65()/SD.getPopulation() * 100;
   out <<  " and total: " << SD.getPopOver65() << endl;
   out << "(% under 18): " << (double)SD.getPopUnder18()/SD.getPopulation() * 100;
   out <<  " and total: " << SD.getPopUnder18() << endl;
   out << "(% under 5): " << (double)SD.getPopUnder5()/SD.getPopulation() * 100;
   out <<  " and total: " << SD.getPopUnder5() << endl;
   out << "(% female): " << (double)SD.getFemale()/SD.getPopulation() * 100;
   out <<  " and total: " << SD.getFemale() << endl;
   out << "(% foreign born): " << (double)SD.getForeignBorn()/SD.getPopulation() * 100;
   out <<  " and total: " << SD.getForeignBorn() << endl;
   out << "(% veterans): " << (double)SD.getVeterans()/SD.getPopulation() * 100;
   out <<  " and total: " << SD.getVeterans() << endl;
   out << "Education info:" << endl;
   out << "(% Bachelor or more): " << (double)SD.getBachelorsDeg()/SD.getPopulation() * 100;
   out <<  " and total: " << SD.getBachelorsDeg() << endl;
   out << "(% high school or more): " << (double)SD.getHighSchoolGrad()/SD.getPopulation() * 100;
   out <<  " and total: " << SD.getHighSchoolGrad() << endl;
   out << "County housing/economy info:" << endl;
   out << "(avg. persons per house): " << SD.getPersonPerHouse();
   out <<  " and total: " << SD.getPersonPerHouse()*SD.getHousingUnits() << endl;
   out << "(% home ownership): " << (double)SD.getHomeOwn()/SD.getPopulation() * 100;
   out <<  " and total: " << SD.getHomeOwn() << endl;
   out << "(number housing units): " << SD.getHousingUnits() << endl;
   out << "(medIncome): " << SD.getMedIncome() << endl;
   out << "Total population: " << SD.getPopulation() << endl;
   return out; 
}