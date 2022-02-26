#include <sstream>
#include "demogCombo.h"

std::ostream& operator<<(std::ostream &out, demogCombo &DC) {
   out << "Aggr Count: " << DC.GetAggrCount();
   return out;
}