#ifndef POLICE_H
#define POLICE_H

#include <string>
#include <iostream>
#include <utility>

using namespace std;

/*
  class to represent police shooting data
  from Washington Post
*/
class psData {
  public:
    //add appropriate function paramaters to constructor once you add data
    psData(string inState) : state(inState) {}


    string getState() const { return state; }
    //add getters

   friend std::ostream& operator<<(std::ostream &out, const psData &PD);

private:
    const string state;
    //add others

};

#endif
