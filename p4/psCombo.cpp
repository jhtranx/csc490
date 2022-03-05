#include <iomanip>
#include <cmath>
#include "psCombo.h"

void psCombo::Accept(class Visitor &v) { }

double CalcPercentPC (int count_, int tot_case_ct_) {
   return ((double)count_ / (double)tot_case_ct_) * 100.0;
}

/* print state data - as aggregate of all incidents in this state */
std::ostream& operator<<(std::ostream &out, const psCombo& PD) {
    raceAndEthnicity curr_race_eth_ = PD.GetRaceEthnicityAggr();

    int tot_race_eth_count_ = 
        int(curr_race_eth_.GetWhiteAloneCt() + curr_race_eth_.GetBlackAloneCt() + curr_race_eth_.GetAmIndianAlNativeCt()
        + curr_race_eth_.GetAsianAloneCt() + curr_race_eth_.GetHawaiianPacIslandCt() + curr_race_eth_.GetTwoOrMoreCt()
        + curr_race_eth_.GetHispLatCt());

    out << "State Info: " << PD.GetStates().at(0);
    out << "\nNumber of incidents: " << PD.GetCasesCount();

    out << "\nIncidents involving unarmed or armed with toy weapons: " 
        << PD.GetUnArmedCount() + PD.GetArmedToyCount() << ", " 
        << CalcPercentPC(PD.GetUnArmedCount() + PD.GetArmedToyCount(), PD.GetCasesCount()) << "%";

    out << "\nIncidents involving mental illness: " << PD.GetNumMentalIllness() << ", " 
        << CalcPercentPC(PD.GetNumMentalIllness(), PD.GetCasesCount()) << "%";

    out << "\nIncidents with body camera on: " << PD.GetBodyCamCount() << ", " 
        << CalcPercentPC(PD.GetBodyCamCount(), PD.GetCasesCount()) << "%";


    out << "\nRacial demographics of state incidents: " << "Racial Demographics Info:";

    out << "\n\% American Indian and Alaska Native percent: " 
        << CalcPercentPC(curr_race_eth_.GetAmIndianAlNativeCt(), PD.GetCasesCount()) << "%";
    out <<  " count: " << curr_race_eth_.GetAmIndianAlNativeCt();

    out << "\n\% Asian American percent: " 
        << CalcPercentPC(curr_race_eth_.GetAsianAloneCt(), PD.GetCasesCount()) << "%";
    out <<  " count: " << curr_race_eth_.GetAsianAloneCt();

    out << "\n\% Black/African American percent: " 
        << CalcPercentPC(curr_race_eth_.GetBlackAloneCt(), PD.GetCasesCount()) << "%";
    out <<  " count: " << curr_race_eth_.GetBlackAloneCt(); 

    out << "\n\% Hispanic or Latinx percent: " 
        << CalcPercentPC(curr_race_eth_.GetHispLatCt(), PD.GetCasesCount()) << "%";
    out <<  " count: " << curr_race_eth_.GetHispLatCt();

    out << "\n\% Native Hawaiian and Other Pacific Islander: " 
        << CalcPercentPC(curr_race_eth_.GetHawaiianPacIslandCt(), PD.GetCasesCount()) << "%";
    out <<  " count: " << curr_race_eth_.GetHawaiianPacIslandCt();

    out << "\n\% Two or More Races percent: " 
        << CalcPercentPC(curr_race_eth_.GetTwoOrMoreCt(), PD.GetCasesCount()) << "%";
    out <<  " count: " << curr_race_eth_.GetTwoOrMoreCt();

    out << "\n\% White (inclusive) percent: " 
        << CalcPercentPC(curr_race_eth_.GetWhiteAloneCt(), PD.GetCasesCount()) << "%";
    out <<  " count: " << curr_race_eth_.GetWhiteAloneCt(); 

    out << "\n\% White (nonHispanic) percent: " 
        << CalcPercentPC(curr_race_eth_.GetWhiteNotHispLatCt(), PD.GetCasesCount()) << "%";
    out <<  " count: " << curr_race_eth_.GetWhiteNotHispLatCt();

    out << "\n\% Unspecified percent: " 
        << CalcPercentPC(curr_race_eth_.GetUnspecifiedCt(), PD.GetCasesCount()) << "%";
    out <<  " count: " << curr_race_eth_.GetUnspecifiedCt();
    
    // is this how u calc this?
    // out <<  " count: " << PD.caseCt - tot_race_eth_count_;

    out << "\ntotal Racial Demographic Count: " << PD.GetCasesCount()  << endl;
    return out;
}