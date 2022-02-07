#include <iomanip>
#include <cmath>
#include "psCombo.h"
#include "dataAQ.h"

/* print state data - as aggregate of all incidents in this state */
std::ostream& operator<<(std::ostream &out, const psCombo& PD) {
    raceAndEthnicity currRace = PD.getRaceEthnicity();
    int totKnownRaceCases = int(currRace.getWhiteAlone() + currRace.getBlackAlone() + currRace.getAmIndianAlNative()
        + currRace.getAsianAlone() + currRace.getHawaiianPacIsland() + currRace.getTwoOrMore()
        + currRace.getHispLat());

    out << "State Info: " << PD.state;
    out << "\nNumber of incidents: ";
    out << std::setprecision(2) << std::fixed;
    out << "\nIncidents involving unarmed or armed with toy weapons: " 
        << PD.unarmedCt + PD.armedToyCt << ", " << (PD.unarmedCt + PD.armedToyCt)/(double)PD.caseCt * 100 <<"%";
    out << "\nIncidents involving mental illness: " << PD.mentalIllnessCt << ", " 
        << PD.mentalIllnessCt/(double)PD.caseCt * 100 <<"%";
    out << "\nIncidents with body camera on: " << PD.bodyCamCt << ", " << PD.bodyCamCt/(double)PD.caseCt *100 <<"%";
    out << "\nRacial demographics of state incidents: " << "Racial Demographics Info:";
    out << "\n\% American Indian and Alaska Native percent: " 
        << PD.getRaceEthnicity().getAmIndianAlNative()/(double)PD.caseCt * 100;
    out <<  " count: " << (int)PD.getRaceEthnicity().getAmIndianAlNative();
    out << "\n\% Asian American percent: " << PD.getRaceEthnicity().getAsianAlone()/(double)PD.caseCt * 100;
    out <<  " count: " << (int)PD.getRaceEthnicity().getAsianAlone();
    out << "\n\% Black/African American percent: " << PD.getRaceEthnicity().getBlackAlone()/(double)PD.caseCt * 100;
    out <<  " count: " << (int)PD.getRaceEthnicity().getBlackAlone(); 
    out << "\n\% Hispanic or Latinx percent: " << PD.getRaceEthnicity().getHispLat()/(double)PD.caseCt * 100;
    out <<  " count: " << (int)PD.getRaceEthnicity().getHispLat();
    out << "\n\% Native Hawaiian and Other Pacific Islander: " 
        << PD.getRaceEthnicity().getHawaiianPacIsland()/(double)PD.caseCt * 100;
    out <<  " count: " << (int)PD.getRaceEthnicity().getHawaiianPacIsland();
    out << "\n\% Two or More Races percent: " << PD.getRaceEthnicity().getTwoOrMore()/(double)PD.caseCt * 100;
    out <<  " count: " << (int)PD.getRaceEthnicity().getTwoOrMore();
    out << "\n\% White (inclusive) percent: " << PD.getRaceEthnicity().getWhiteAlone()/(double)PD.caseCt * 100;
    out <<  " count: " << (int)PD.getRaceEthnicity().getWhiteAlone(); 
    out << "\n\% White (nonHispanic) percent: " << PD.getRaceEthnicity().getWhiteNotHispLat()/(double)PD.caseCt * 100;
    out <<  " count: " << (int)PD.getRaceEthnicity().getWhiteNotHispLat();
    out << "\n\% Unspecified percent: " << (PD.caseCt - totKnownRaceCases)/(double)PD.caseCt * 100;
    out <<  " count: " <<PD.caseCt - totKnownRaceCases;
    out << "\ntotal Racial Demographic Count: " << PD.caseCt  << endl;
    return out;
}