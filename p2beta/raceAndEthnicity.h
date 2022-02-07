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
         double inHyn, double woOrMore, double inHispLat, double inWhiteNotHispLat) :
            whiteAlone(inWhite), blackAlone(inBlack), amIndianAlNative(inIndAl), 
            asianAlone(inAsian), hawaiianPacIsland(inHyn), twoOrMore(woOrMore), 
            hispLat(inHispLat), whiteNotHispLat(inWhiteNotHispLat), none(0), other(0) {}
      raceAndEthnicity() :
            whiteAlone(0), blackAlone(0), amIndianAlNative(0), 
            asianAlone(0), hawaiianPacIsland(0), twoOrMore(0), 
            hispLat(0), whiteNotHispLat(0), none(0), other(0) {}

      // Getter
      double getWhiteAlone() {return whiteAlone;}
      double getBlackAlone() {return blackAlone;}
      double getAmIndianAlNative() {return amIndianAlNative;}
      double getAsianAlone() {return asianAlone;}
      double getHawaiianPacIsland() {return hawaiianPacIsland;}
      double getTwoOrMore() {return twoOrMore;}
      double getHispLat() {return hispLat;}
      double getWhiteNotHispLat() {return whiteNotHispLat;}

      void setWhiteAlone(double newVal) {whiteAlone = newVal;}
      void setBlackAlone(double newVal) {blackAlone = newVal;}
      void setAmIndianAlNative(double newVal) {amIndianAlNative = newVal;}
      void setAsianAlone(double newVal) {asianAlone = newVal;}
      void setHawaiianPacIsland(double newVal) {hawaiianPacIsland = newVal;}
      void setTwoOrMore(double newVal) {twoOrMore = newVal;}
      void setHispLat(double newVal) {hispLat = newVal;}
      void setWhiteNotHispLat(double newVal) {whiteNotHispLat = newVal;}

      void incWhiteAlone() {whiteAlone++;}
      void incBlackAlone() {blackAlone++;}
      void incAmIndianAlNative() {amIndianAlNative++;}
      void incAsianAlone() {asianAlone++;}
      void incHawaiianPacIsland() {hawaiianPacIsland++;}
      void incTwoOrMore() {twoOrMore++;}
      void incHispLat() {hispLat++;}
      void incWhiteNotHispLat() {whiteNotHispLat++;}
      void incUnknown() {none++;}
      void incOther() {other++;}
      
   friend std::ostream& operator<<(std::ostream &out,  raceAndEthnicity &DD);
   
   private:
      double whiteAlone;
      double blackAlone;
      double amIndianAlNative;
      double asianAlone;
      double hawaiianPacIsland;
      double twoOrMore;
      double hispLat;
      double whiteNotHispLat;

      int none;
      int other;
      
};
#endif
