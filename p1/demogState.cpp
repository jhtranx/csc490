#include "demogState.h"
#include "demogData.h"
#include <sstream>
#include <string>
#include <assert.h>
#include <iomanip>

//add member functions here

/* print state data - as aggregate of all the county data */
std::ostream& operator<<(std::ostream &out, const demogState&SD) {
   out << "State Info: " << SD.getState() << endl;
   return out;
}

// *** the state that needs the most pre-schools**
// State Info: AK
// Number of Counties: 20
// Population info:
// (over 65): 12.86% and total: 33792
// (under 18): 24.71% and total: 64926
// (under 5): 7.21% and total: 18947
// (female): 46.26% and total: 121580
// Education info:
// (Bachelor or more): 25.03% and total: 65772
// (high school or more): 91.26% and total: 239834
// medIncome: $68659
// Total population: 262802