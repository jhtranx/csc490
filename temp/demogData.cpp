#include "demogData.h"
#include <cmath>
#include <sstream>
#include "raceAndEthnicity.h"

/* print county demographic data */
/* fill in any other data to make printing easy  */

double CalcPercentDD (int count_, int tot_pop_) {
   return round((double)count_ / (double)tot_pop_);
}
int CalcTotal (double percent_, int tot_pop_) {
   return round(percent_ * (double)tot_pop_);
}

void demogData::Accept(class Visitor &v) { v.visit(shared_from_this()); }

std::ostream& operator<<(std::ostream &out, const demogData &DD) {

   int tot_pop_ = DD.GetTotPop();
   raceAndEthnicity race_eth_ = DD.GetRaceAndEthnicity();

   out << "County Demographics Info: " << DD.GetRegionName() << ", " << DD.GetStateName();
   out << "\nTotal population: " << tot_pop_;

   out << "\nRacial Demographics Info: \n";
   
   out << "\% American Indian and Alaska Native percent: " << 
      CalcPercentDD(race_eth_.GetAmIndianAlNativeCt(), tot_pop_);
   out <<  " count: " << race_eth_.GetAmIndianAlNativeCt();

   out << "\n\% Asian American percent: " << 
      CalcPercentDD(race_eth_.GetAsianAloneCt(), tot_pop_);
   out <<  " count: " << race_eth_.GetAsianAloneCt();

   out << "\n\% Black/African American percent: " << 
      CalcPercentDD(race_eth_.GetBlackAloneCt(), tot_pop_);
   out <<  " count: " << race_eth_.GetBlackAloneCt(); 

   out << "\n\% Hispanic or Latinx percent: " << 
      CalcPercentDD(race_eth_.GetHispLatCt(), tot_pop_);
   out <<  " count: " << race_eth_.GetHispLatCt();

   out << "\n\% Native Hawaiian and Other Pacific Islander percent: " << 
      CalcPercentDD(race_eth_.GetHawaiianPacIslandCt(), tot_pop_);
   out <<  " count: " << race_eth_.GetHawaiianPacIslandCt();

   out << "\n\% Two or More Races percent: " << 
      CalcPercentDD(race_eth_.GetTwoOrMoreCt(), tot_pop_);
   out <<  " count: " << race_eth_.GetTwoOrMoreCt();

   out << "\n\% White (inclusive) percent: " << 
      CalcPercentDD(race_eth_.GetWhiteAloneCt(), tot_pop_);
   out <<  " count: " << race_eth_.GetWhiteAloneCt();

   out << "\n\% White (nonHispanic) percent: " << 
      CalcPercentDD(race_eth_.GetWhiteNotHispLatCt(), tot_pop_);
   out <<  " count: " << race_eth_.GetWhiteNotHispLatCt();
   out << "\ntotal Racial Demographic Count: " <<  tot_pop_;

   out << "\n--Population Age info: \n(\% under 5): " << DD.GetPopUnder5Percent();
   out <<  " and total: " << CalcTotal(DD.GetPopUnder5Percent(), tot_pop_);
   out << "\n(\% under 18): " << DD.GetPopUnder18Percent();
   out <<  " and total: " << CalcTotal(DD.GetPopUnder18Percent(), tot_pop_);
   out << "\n(\% over 65): " << DD.GetPopOver65Percent();
   out <<  " and total: " << CalcTotal(DD.GetPopOver65Percent(), tot_pop_);

   out << "\n--Population other demographics: \n(\% female): " << DD.GetFemalePercent();
   out <<  " and total: " << CalcTotal(DD.GetFemalePercent(), tot_pop_);
   out << "\n(\% foreign born): " << DD.GetForeignBornPercent();
   out <<  " and total: " << CalcTotal(DD.GetForeignBornPercent(), tot_pop_);
   out << "\n(veterans): " << DD.GetVeteransCount();

   out << "\n--County housing/economy info: \n(avg. persons per house): " << DD.GetPersonPerHousePercent();
   out <<  " and total: " << CalcTotal(DD.GetPersonPerHousePercent(), tot_pop_);
   out << "\n(\% home ownership): " << DD.GetHomeOwnPercent();
   out <<  " and total: " << CalcTotal(DD.GetHomeOwnPercent(), tot_pop_);
   out << "\n(number housingholds): " << DD.GetNumHouseholdsCount();
   out << "\n(medium income in $): " << DD.GetMedHouseholdIncomeCount();

   out << "\n--County education: \n(\% Bachelor or more): " << DD.GetBachelorsDegPercent();
   out <<  " and total: " << CalcTotal(DD.GetBachelorsDegPercent(), tot_pop_);
   out << "\n(\% high school or more): " << DD.GetHighSchoolGradPercent();
   out <<  " and total: " << CalcTotal(DD.GetHighSchoolGradPercent(), tot_pop_);

   out << "\n";
   return out;
}
