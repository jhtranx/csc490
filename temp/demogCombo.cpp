#include <sstream>
#include <cmath>
#include <sstream>
#include "raceAndEthnicity.h"
#include "demogCombo.h"

double CalcPercentDC (int count_, int tot_pop_) {
   return ((double)count_ / (double)tot_pop_)*100;
}
int CalcTotalDC (double percent_, int tot_pop_) {
   return round(percent_ * (double)tot_pop_);
}

std::ostream& operator<<(std::ostream &out, const demogCombo &DC) {
   int tot_pop_ = DC.GetTotPop();
   raceAndEthnicity race_eth_ = DC.GetRaceAndEthnicity();

   out << "County Demographics Info: " << DC.GetRegionName() << ", " << DC.GetStateName();
   out << "\nTotal population: " << tot_pop_;

   out << "\nRacial Demographics Info: \n";
   
   out << "\% American Indian and Alaska Native percent: " << 
      CalcPercentDC(race_eth_.GetAmIndianAlNativeCt(), tot_pop_);
   out <<  " count: " << race_eth_.GetAmIndianAlNativeCt();

   out << "\n\% Asian American percent: " << 
      CalcPercentDC(race_eth_.GetAsianAloneCt(), tot_pop_);
   out <<  " count: " << race_eth_.GetAsianAloneCt();

   out << "\n\% Black/African American percent: " << 
      CalcPercentDC(race_eth_.GetBlackAloneCt(), tot_pop_);
   out <<  " count: " << race_eth_.GetBlackAloneCt(); 

   out << "\n\% Hispanic or Latinx percent: " << 
      CalcPercentDC(race_eth_.GetHispLatCt(), tot_pop_);
   out <<  " count: " << race_eth_.GetHispLatCt();

   out << "\n\% Native Hawaiian and Other Pacific Islander percent: " << 
      CalcPercentDC(race_eth_.GetHawaiianPacIslandCt(), tot_pop_);
   out <<  " count: " << race_eth_.GetHawaiianPacIslandCt();

   out << "\n\% Two or More Races percent: " << 
      CalcPercentDC(race_eth_.GetTwoOrMoreCt(), tot_pop_);
   out <<  " count: " << race_eth_.GetTwoOrMoreCt();

   out << "\n\% White (inclusive) percent: " << 
      CalcPercentDC(race_eth_.GetWhiteAloneCt(), tot_pop_);
   out <<  " count: " << race_eth_.GetWhiteAloneCt();

   out << "\n\% White (nonHispanic) percent: " << 
      CalcPercentDC(race_eth_.GetWhiteNotHispLatCt(), tot_pop_);
   out <<  " count: " << race_eth_.GetWhiteNotHispLatCt();
   out << "\ntotal Racial Demographic Count: " <<  tot_pop_;

   out << "\n--Population Age info: \n(\% under 5): " << CalcPercentDC(DC.GetPopUnder5Count(), tot_pop_);
   out <<  " and total: " << DC.GetPopUnder5Count();
   out << "\n(\% under 18): " << CalcPercentDC(DC.GetPopUnder18Count(), tot_pop_);
   out <<  " and total: " << DC.GetPopUnder18Count();
   out << "\n(\% over 65): " << CalcPercentDC(DC.GetPopOver65Count(), tot_pop_);
   out <<  " and total: " << DC.GetPopOver65Count();

   out << "\n--Population other demographics: \n(\% female): " 
      << CalcPercentDC(DC.GetFemaleCount(), tot_pop_);
   out <<  " and total: " << DC.GetFemaleCount();
   out << "\n(\% foreign born): " << CalcPercentDC(DC.GetForeignBornCount(), tot_pop_);
   out <<  " and total: " << DC.GetForeignBornCount();
   out << "\n(veterans): " << DC.GetVeteransCount();

   out << "\n--County housing/economy info: \n(avg. persons per house): " << DC.GetPersonPerHousePercent();
   out <<  " and total: " << CalcTotalDC(DC.GetPersonPerHousePercent(), tot_pop_);
   out << "\n(\% home ownership): " << DC.GetHomeOwnPercent();
   out <<  " and total: " << CalcTotalDC(DC.GetHomeOwnPercent(), tot_pop_);
   out << "\n(number housingholds): " << DC.GetNumHouseholdsCount();
   out << "\n(medium income in $): " << DC.GetMedHouseholdIncomeCount();

   out << "\n--County education: \n(\% Bachelor or more): " << CalcTotalDC(DC.GetBachelorsDegCount(), tot_pop_);
   out <<  " and total: " << DC.GetBachelorsDegCount();
   out << "\n(\% high school or more): " << CalcTotalDC(DC.GetHighSchoolGradCount(), tot_pop_);
   out <<  " and total: " << DC.GetHighSchoolGradCount();

   out << "\n";

   return out;
}