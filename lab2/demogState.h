#ifndef STATE_H
#define STATE_H

#include <memory>
#include <string>
#include <iostream>
#include "demogData.h"

/*
  class to represent state data - fairly redundent at this point but will use
  inheritence later - FILL IN
*/
class demogState {
  public:
   //FILL IN
   demogState(){}
  friend std::ostream& operator<<(std::ostream &out, const demogState &SD);
	private:
        const string county;
        const string state;
        const int population;
        const string race
        const string ethnicity;
        const float medIncome;
        const int homeOwn; //check if right
        const int personPerHouse;
        const int veterans;
        const int highSchoolGrad;
        const int bachelorsDeg;
        const int foreignBorn;
	//DATA here
};
#endif
