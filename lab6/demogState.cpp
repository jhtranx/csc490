#include "demogState.h"
#include "demogData.h"
#include <sstream>
#include <string>
#include <assert.h>
#include <iomanip>
#include <cmath>

//aSD member functions here

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
   out <<  " and total: " << SD.getPersonPerHouse()*SD.getNumHousehold() << endl;
   out << "(% home ownership): " << (double)SD.getHomeOwn()/SD.getPopulation() * 100;
   out <<  " and total: " << SD.getHomeOwn() << endl;
   out << "(number housing units): " << SD.getNumHousehold() << endl;
   out << "(medIncome): " << SD.getMedIncome() << endl;
   out << "Total population: " << SD.getPopulation() << endl;
   
   out << "\nRacial Demographics Info: \n\% American Indian and Alaska Native percent: " << SD.getRaceAndEthnicity().getAmIndianAlNative();
   out <<  " count: " << round((SD.getRaceAndEthnicity().getAmIndianAlNative()) * SD.totalPopulation2020);
   out << "\n\% Asian American percent: " << SD.getRaceAndEthnicity().getAsianAlone();
   out <<  " count: " << round((SD.getRaceAndEthnicity().getAsianAlone()) * SD.totalPopulation2020);
   out << "\n\% Black/African American percent: " << SD.getRaceAndEthnicity().getBlackAlone();
   out <<  " count: " << round((SD.getRaceAndEthnicity().getBlackAlone()) * SD.totalPopulation2020); 
   out << "\n\% Hispanic or Latinx percent: " << SD.getRaceAndEthnicity().getHispLat();
   out <<  " count: " << round((SD.getRaceAndEthnicity().getHispLat()) * SD.totalPopulation2020);
   out << "\n\% Native Hawaiian and Other Pacific Islander: " << SD.getRaceAndEthnicity().getHawaiianPacIsland();
   out <<  " count: " << round((SD.getRaceAndEthnicity().getHawaiianPacIsland()) * SD.totalPopulation2020);
   out << "\n\% Two or More Races percent: " << SD.getRaceAndEthnicity().getTwoOrMore();
   out <<  " count: " << round((SD.getRaceAndEthnicity().getTwoOrMore()) * SD.totalPopulation2020);
   out << "\n\% White (inclusive) percent: " << SD.getRaceAndEthnicity().getWhiteAlone();
   out <<  " count: " << round((SD.getRaceAndEthnicity().getWhiteAlone()) * SD.totalPopulation2020); 
   out << "\n\% White (nonHispanic) percent: " << SD.getRaceAndEthnicity().getWhiteNotHispLat();
   out <<  " count: " << round((SD.getRaceAndEthnicity().getWhiteNotHispLat()) * SD.totalPopulation2020);
   out << "\ntotal Racial Demographic Count: " <<  SD.totalPopulation2020;

   return out; 
}