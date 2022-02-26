#include <sstream>
#include "psData.h"

void psData::Accept(class Visitor &v) { v.visit(shared_from_this()); }

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
