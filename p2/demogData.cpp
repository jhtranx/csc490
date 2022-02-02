#include "demogData.h"
#include <cmath>
#include <sstream>
#include "raceAndEthnicity.h"

/* print county demographic data */
/* fill in any other data to make printing easy  */
std::ostream& operator<<(std::ostream &out, const demogData &DD) {
   out << "County Demographics Info: " << DD.getCounty() << ", " << DD.state;
   out << "\nTotal population: " << DD.totalPopulation2020;

   out << "\nRacial Demographics Info: \n\% American Indian and Alaska Native percent: " << DD.getRaceAndEthnicity().getAmIndianAlNative();
   out <<  " count: " << round((DD.getRaceAndEthnicity().getAmIndianAlNative()) * DD.totalPopulation2020);
   out << "\n\% Asian American percent: " << DD.getRaceAndEthnicity().getAsianAlone();
   out <<  " count: " << round((DD.getRaceAndEthnicity().getAsianAlone()) * DD.totalPopulation2020);
   out << "\n\% Black/African American percent: " << DD.getRaceAndEthnicity().getBlackAlone();
   out <<  " count: " << round((DD.getRaceAndEthnicity().getBlackAlone()) * DD.totalPopulation2020); 
   out << "\n\% Hispanic or Latinx percent: " << DD.getRaceAndEthnicity().getHispLat();
   out <<  " count: " << round((DD.getRaceAndEthnicity().getHispLat()) * DD.totalPopulation2020);
   out << "\n\% Native Hawaiian and Other Pacific Islander: " << DD.getRaceAndEthnicity().getHawaiianPacIsland();
   out <<  " count: " << round((DD.getRaceAndEthnicity().getHawaiianPacIsland()) * DD.totalPopulation2020);
   out << "\n\% Two or More Races percent: " << DD.getRaceAndEthnicity().getTwoOrMore();
   out <<  " count: " << round((DD.getRaceAndEthnicity().getTwoOrMore()) * DD.totalPopulation2020);
   out << "\n\% White (inclusive) percent: " << DD.getRaceAndEthnicity().getWhiteAlone();
   out <<  " count: " << round((DD.getRaceAndEthnicity().getWhiteAlone()) * DD.totalPopulation2020); 
   out << "\n\% White (nonHispanic) percent: " << DD.getRaceAndEthnicity().getWhiteNotHispLat();
   out <<  " count: " << round((DD.getRaceAndEthnicity().getWhiteNotHispLat()) * DD.totalPopulation2020);
   out << "\ntotal Racial Demographic Count: " <<  DD.totalPopulation2020;

   out << "\n--Population Age info: \n(\% under 5): " << DD.popUnder5;
   out <<  " and total: " << round((DD.popUnder5) * DD.totalPopulation2020);
   out << "\n(\% under 18): " << DD.popUnder18;
   out <<  " and total: " << round((DD.popUnder18) * DD.totalPopulation2020);
   out << "\n(\% over 65): " << DD.popOver65;
   out <<  " and total: " << round((DD.popOver65) * DD.totalPopulation2020);

   out << "\n--Population other demographics: \n(\% female): " << DD.getFemale();
   out <<  " and total: " << round((DD.getFemale()) * DD.totalPopulation2020);
   out << "\n(\% foreign born): " << DD.getForeignBorn();
   out <<  " and total: " << round((DD.getForeignBorn()) * DD.totalPopulation2020);
   out << "\n(veterans): " << DD.getVeterans();

   out << "\n--County housing/economy info: \n(avg. persons per house): " << DD.getPersonPerHouse();
   out <<  " and total: " << round(DD.getPersonPerHouse() * DD.getNumHouseholds());
   out << "\n(\% home ownership): " << DD.getHomeOwn();
   out <<  " and total: " << round((DD.getHomeOwn()) * DD.totalPopulation2020);
   out << "\n(number housingholds): " << DD.getNumHouseholds();
   out << "\n(medium income in $): " << DD.getMedIncome();

   out << "\n--County education: \n(\% Bachelor or more): " << DD.getBachelorsDeg();
   out <<  " and total: " << round((DD.getBachelorsDeg()) * DD.totalPopulation2020);
   out << "\n(\% high school or more): " << DD.getHighSchoolGrad();
   out <<  " and total: " << round((DD.getHighSchoolGrad()) * DD.totalPopulation2020);

   out << "\n";
   return out;
}
