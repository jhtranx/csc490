#ifndef RACEDEMOG_H
#define RACEDEMOG_H

#include <iostream>

class raceDemogData {
  public:
  		//default constructor
  	    raceDemogData()  {}

    /* TO DO replace with your race/ethnicity data represenatation */

    friend std::ostream& operator<<(std::ostream &out, const raceDemogData &SD);

  private:
  	

};

#endif