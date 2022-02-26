#include <sstream>
#include "demogCombo.h"

std::ostream& operator<<(std::ostream &out, const demogCombo &DC) {
   out << "Aggr Count: " << DC.GetAggrCount();
   return out;
}