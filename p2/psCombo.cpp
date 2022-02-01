#include <iomanip>
#include "psCombo.h"

/* print state data - as aggregate of all incidents in this state */
std::ostream& operator<<(std::ostream &out, const psCombo& PD) {
    out << "State Info: " << PD.state;
    out << "\nNumber of incidents: ";
    out << std::setprecision(2) << std::fixed;
    out << "\nIncidents involving unarmed or armed with toy weapons: " << "fix"<< ", " << "fix" <<"%";
    out << "\nIncidents involving mental illness: " << "fix" << ", " << "fix"<<"%";
    out << "\nIncidents with body camera on: " << "fix" << ", " << "fix"<<"%";
    out << "\nRacial demographics of state incidents: " << "fix";
    return out;
}