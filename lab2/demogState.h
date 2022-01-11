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
	//DATA here
};
#endif
