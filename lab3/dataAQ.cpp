/* aggregate data */
#include "dataAQ.h"
#include "demogData.h"
#include <iostream>
#include <algorithm>

dataAQ::dataAQ() {}

/* necessary function to aggregate the data - this CAN and SHOULD vary per
   student - depends on how they map, etc. */
void dataAQ::createStateData(std::vector<shared_ptr<demogData>> theData) {
//FILL in
}

//return the name of the state with the largest population under age 5
string dataAQ::youngestPop() {
	//FILL in
  return "fix me"; 
} 

//return the name of the state with the largest population under age 18
string dataAQ::teenPop()  {
	//FILL in
  return "fix me"; 
}

//return the name of the state with the largest population over age 65
string dataAQ::wisePop()  {
	//FILL in
  return "fix me"; 
}

//return the name of the state with the largest population who did not receive high school diploma
string dataAQ::underServeHS() {
	//FILL in
  return "fix me"; 
} 

//return the name of the state with the largest population who did receive bachelors degree and up
string dataAQ::collegeGrads() {
	//FILL in
  return "fix me"; 
}

//return the name of the state with the largest population below the poverty line
string dataAQ::belowPoverty() {
	//FILL in
  return "fix me"; 
} 
