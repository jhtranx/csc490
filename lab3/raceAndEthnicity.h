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

    // raceAndEthnicity(double w, double b, double indAl, double as, double hyn, double tom, double hl, double wnhl) {
    //     whiteAlone = w;
    //     blackAlone = b;
    //     amIndianAlNative = indAl;
    //     asianAlone = as;
    //     hawaiianPacIsland = hyn;
    //     twoOrMore = tom;
    //     hispLat = hl;
    //     whiteNotHispLat = wnhl;
    // }

   // Setter
    // void setWhiteAlone(double w) {whiteAlone = w;}
    // void setBlackAlone(double b) {blackAlone = b;}
    // void setAmIndianAlNative(double indAl) {amIndianAlNative = indAl;}
    // void setAsianAlone(double as) {asianAlone = as;}
    // void setHawaiianPacIsland(double hyn) {hawaiianPacIsland = hyn;}
    // void setTwoOrMore(double tom) {twoOrMore = tom;}
    // void setHispLat(double hl) {hispLat = hl;}
    // void setWhiteNotHispLat(double wnhl) {whiteNotHispLat = wnhl;}
};
#endif
