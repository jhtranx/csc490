#ifndef STATE_H
#define STATE_H

#include <memory>
#include <string>
#include <iostream>
#include "demogState.h"
#include "raceAndEthnicity.h"

using namespace std;
/*
   class to represent state data - fairly redundent at this point but will use
   inheritence later - FILL IN
*/
class demogState {
   public:
      friend std::ostream& operator<<(std::ostream &out, const demogState &SD);

      demogState(string inS, int tc, int in65, int in18,
         int in5, int totPop20, int f,
         int mi, int hu, double ho, 
         double pph, int vets, int hsg, int bd, 
         int fb, raceAndEthnicity re) :
               state(inS), totCounties(tc), popOver65(in65), popUnder18(in18),
               popUnder5(in5), totalPopulation2020(totPop20), female(f), medIncome(mi), numHousehold(hu), homeOwn(ho), 
               personPerHouse(pph), veterans(vets), highSchoolGrad(hsg), bachelorsDeg(bd), 
               foreignBorn(fb), raceEth(re) {}

      // Getter
      string getState() const {return state;}
      int getTotCounties() const {return totCounties;}
      int getPopOver65() const {return popOver65;}
      int getPopUnder18() const {return popUnder18;}
      int getPopUnder5() const {return popUnder5;}
      int getPopulation() const {return totalPopulation2020;}
      int getFemale() const {return female;}
      raceAndEthnicity getRaceAndEthnicity() const {return raceEth;}
      int getMedIncome() const {return medIncome;}
      int getNumHousehold() const {return numHousehold;}
      double getHomeOwn() const {return homeOwn;}
      double getPersonPerHouse() const {return personPerHouse ;}
      int getVeterans() const {return veterans;}
      int getHighSchoolGrad() const {return highSchoolGrad;}
      int getBachelorsDeg() const {return bachelorsDeg;}
      int getForeignBorn() const {return foreignBorn;}

      //functions to update demogState when aggregating counties
      void updateTotCounties()  {totCounties += 1;}
      void updateRaceAndEthnicity() {}
      void updateWhite(int whiteCt, int incPop) {
         int oldWhiteTot = raceEth.getWhiteAlone() * totalPopulation2020;
         double newWhitePerc = 
            (double) (whiteCt + oldWhiteTot) / (double) (totalPopulation2020 + incPop);
         raceEth.setWhiteAlone(newWhitePerc);
      }
      void updateBlack (int blackCt, int incPop) {
         int oldBlackTot = raceEth.getBlackAlone() * totalPopulation2020;
         double newBlackPerc = 
            (double) (blackCt + oldBlackTot) / (double) (totalPopulation2020 + incPop);
         raceEth.setBlackAlone(newBlackPerc);
      }
      void updateIndAl (int indAlCt, int incPop) {
         int oldIndAlTot = raceEth.getAmIndianAlNative() * totalPopulation2020;
         double newIndAlPerc = 
            (double) (indAlCt + oldIndAlTot) / (double) (totalPopulation2020 + incPop);
         raceEth.setAmIndianAlNative(newIndAlPerc);
      }
      void updateAsian (int asianCt, int incPop) {
         int oldAsianTot = raceEth.getAsianAlone() * totalPopulation2020;
         double newAsianPerc = 
            (double) (asianCt + oldAsianTot) / (double) (totalPopulation2020 + incPop);
         raceEth.setAsianAlone(newAsianPerc);
      }
      void updateHyn (int hynCt, int incPop) {
         int oldHynTot = raceEth.getHawaiianPacIsland() * totalPopulation2020;
         double newHynPerc = 
            (double) (hynCt + oldHynTot) / (double) (totalPopulation2020 + incPop);
         raceEth.setHawaiianPacIsland(newHynPerc);
      }
      void updateTwoOrMore (int twoOrMoreCt, int incPop) {
         int oldTwoOrMoreTot = raceEth.getTwoOrMore() * totalPopulation2020;
         double newTwoOrMorePerc = 
            (double) (twoOrMoreCt + oldTwoOrMoreTot) / (double) (totalPopulation2020 + incPop);
         raceEth.setTwoOrMore(newTwoOrMorePerc);
      }
      void updateHispLat (int hispLatCt, int incPop) {
         int oldHispLatTot = raceEth.getHispLat() * totalPopulation2020;
         double newHispLatPerc = 
            (double) (hispLatCt + oldHispLatTot) / (double) (totalPopulation2020 + incPop);
         raceEth.setHispLat(newHispLatPerc);
      }
      void updateWhiteNotHisLat (int whiteNotHispLatCt, int incPop) {
         int oldWhiteNotHispLatTot = raceEth.getWhiteNotHispLat() * totalPopulation2020;
         double newWhiteNotHispLatPerc = 
            (double) (whiteNotHispLatCt + oldWhiteNotHispLatTot) / (double) (totalPopulation2020 + incPop);
         raceEth.setWhiteNotHispLat(newWhiteNotHispLatPerc);
      }

      void updatePopulation(int increase)  {totalPopulation2020 += increase;}
      void updatePopOver65(int increase)  {popOver65 += increase;}
      void updatePopUnder18(int increase)  {popUnder18 += increase;}
      void updatePopUnder5(int increase)  {popUnder5 += increase;}
      void updateFemale(int increase)  {female += increase;}

      void updateMedIncome(double increase)  {
         double oldMediumIncome = (double) medIncome;
         double oldTotalCounties = (double) totCounties - 1;
         double newTotalCounties = (double) totCounties;
         
         double oldTotalMediumIncome = oldMediumIncome * oldTotalCounties;
         double newMedIncome = (increase + oldTotalMediumIncome) / newTotalCounties;
         medIncome = newMedIncome;
      } 
      void updateNumHousehold(int increase)  {numHousehold += increase;}
      //percent-sum(homeownership*households)/sum(households)
      void updateHomeOwn(double incHomeOwn, int incNumHousehold) {
         double oldTotHomeOwners = (double)numHousehold*homeOwn;
         double newTotHomeOwners = (double)incNumHousehold*incHomeOwn;

         double newHomeOwnPerc = (double)(oldTotHomeOwners + newTotHomeOwners) / 
            (numHousehold + incNumHousehold);
         
         homeOwn = newHomeOwnPerc;
      }

      void updatePersonPerHouse(double incPph, int incHu)  {
         double oldPphTot = (double) personPerHouse * numHousehold;
         double newPphTot = incPph * incHu;
         double newHu = incHu + numHousehold;

         double newPersonPerHouse = (oldPphTot + newPphTot) / newHu;
         personPerHouse = newPersonPerHouse;
      } 

      void updateVeterans(int increase)  {veterans += increase;}
      void updateHighSchoolGrad(int increase)  {highSchoolGrad += increase;}
      void updateBachelorsDeg(int increase)  {bachelorsDeg += increase;}
      void updateForeignBorn(int increase)  {foreignBorn += increase;}

   private:
      string state;
      int totCounties;
      int popOver65;
      int popUnder18;
      int popUnder5;
      int totalPopulation2020;
      int female;
      raceAndEthnicity raceEth;
      double medIncome;
      int numHousehold;
      double homeOwn;
      double personPerHouse;
      int veterans;
      int highSchoolGrad;
      int bachelorsDeg;
      int foreignBorn;
        
};
#endif
