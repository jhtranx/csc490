#ifndef RACE_ETHNIC_H
#define RACE_ETHNIC_H

#include <string>
#include<iostream>

using namespace std;

/*
  class to represent county demographic data
  from CORGIS - fill in with any data we agree as a class we want to include
*/
class raceAndEthnicity {
   public:
      raceAndEthnicity(double inWhite, double inBlack, double inIndAl, double inAsian,
         double inHyn, double inTwoOrMore, double inHispLat, double inWhiteNotHispLat) :
            whiteAlone(inWhite), blackAlone(inBlack), amIndianAlNative(inIndAl), asianAlone(inAsian),
            hawaiianPacIsland(inHyn), twoOrMore(inTwoOrMore), hispLat(inHispLat), whiteNotHispLat(inWhiteNotHispLat) {}
      raceAndEthnicity() :
            whiteAlone(0), blackAlone(0), amIndianAlNative(0), asianAlone(0),
            hawaiianPacIsland(0), twoOrMore(0), hispLat(0), whiteNotHispLat(0) {}

      // Getter
      double getWhiteAlone() const {return whiteAlone;}
      double getBlackAlone() const {return blackAlone;}
      double getAmIndianAlNative() const {return amIndianAlNative;}
      double getAsianAlone() const {return asianAlone;}
      double getHawaiianPacIsland() const {return hawaiianPacIsland;}
      double getTwoOrMore() const {return twoOrMore;}
      double getHispLat() const {return hispLat;}
      double getWhiteNotHispLat() const {return whiteNotHispLat;}
      
   friend std::ostream& operator<<(std::ostream &out, const raceAndEthnicity &DD);
   
   private:
      const double whiteAlone;
      const double blackAlone;
      const double amIndianAlNative;
      const double asianAlone;
      const double hawaiianPacIsland;
      const double twoOrMore;
      const double hispLat;
      const double whiteNotHispLat;
      
};
#endif
