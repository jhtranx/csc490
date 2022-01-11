#include "demogData.h"
#include <sstream>

/* print county demographic data */
/* fill in any other data to make printing easy  */
std::ostream& operator<<(std::ostream &out, const demogData &DD) {
    out << "County Demographics Info: " << DD.getName() << ", " << DD.state;
    out << " total population: " << DD.totalPopulation2020;
    //consider re-writing with getters....
    out << "\nPopulation info: \n(\% over 65): " << DD.popOver65;
    out <<  " Count: " << "fix";
    out << "\n(\% under 18): " << DD.popUnder18;
    out <<  " Count: " << "fix";
    out << "\n(\% under 5): " << DD.popUnder5;
    out <<  " Count: " << "fix";
    out << "\nEducation info: " << "fix this for lab01\n";
    return out;
}
