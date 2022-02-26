#include <sstream>
#include "psData.h"

/* print police data - fill in*/
std::ostream& operator<<(std::ostream &out, const psData &PD) {
   out << "Police Shotting Info: " << PD.GetStates().at(0);
   out << "\nPerson name: " << PD.GetName();
   out << "\nRace:" << PD.GetRaceAndEthnicityStr();
   out << "\nArmed: " << PD.GetArmedWith();
   out << "\nMental Illness: " << PD.HasSignsOfMentalIllness();  // True or False
   out << "\nBody Camera On: " << PD.HasBodyCam() ;              // True or False
   return out;
}
