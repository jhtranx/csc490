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
      raceAndEthnicity(
         int in_white_ct_, int in_black_ct_, int in_al_am_ct_, 
         int in_asian_ct_, int in_hyn_ct_, int in_two_or_more_ct_, 
         int in_hisp_lat_ct_, int in_white_nh_
      ) :
         white_alone_ct_(in_white_ct_), black_alone_ct_(in_black_ct_), am_ind_al_native_ct_(in_al_am_ct_), 
         asian_alone_ct_(in_asian_ct_), hyn_alone_ct_(in_hyn_ct_), two_or_more_ct_(in_two_or_more_ct_), 
         hisp_lat_ct_(in_hisp_lat_ct_), white_nh_ct_(in_white_nh_), unspecified_ct_(0) 
      {}

      raceAndEthnicity() :
         white_alone_ct_(0), black_alone_ct_(0), am_ind_al_native_ct_(0), 
         asian_alone_ct_(0), hyn_alone_ct_(0), two_or_more_ct_(0), 
         hisp_lat_ct_(0), white_nh_ct_(0), unspecified_ct_(0) 
      {}

      // Getters
      int GetWhiteAloneCt() const { return white_alone_ct_; }
      int GetBlackAloneCt() const { return black_alone_ct_; }
      int GetAmIndianAlNativeCt() const { return am_ind_al_native_ct_; }
      int GetAsianAloneCt() const { return asian_alone_ct_; }
      int GetHawaiianPacIslandCt() { return hyn_alone_ct_; }
      int GetTwoOrMoreCt() { return two_or_more_ct_; }
      int GetHispLatCt() const { return hisp_lat_ct_; }
      int GetWhiteNotHispLatCt() { return white_nh_ct_; }
      int GetUnspecifiedCt() { return unspecified_ct_; }

      // Setters
      void SetWhiteAloneCt(int new_val_) { white_alone_ct_ = new_val_; }
      void SetBlackAloneCt(int new_val_) { black_alone_ct_ = new_val_; }
      void SetAmIndianAlNativeCt(int new_val_) { am_ind_al_native_ct_ = new_val_; }
      void SetAsianAloneCt(int new_val_) { asian_alone_ct_ = new_val_; }
      void SetHawaiianPacIslandCt(int new_val_) { hyn_alone_ct_ = new_val_; }
      void SetTwoOrMoreCt(int new_val_) { two_or_more_ct_ = new_val_; }
      void SetHispLatCt(int new_val_) { hisp_lat_ct_ = new_val_; }
      void SetWhiteNotHispLatCt(int new_val_) { white_nh_ct_ = new_val_; }

      void IncWhiteAloneCt() { white_alone_ct_ += 1; }
      void IncBlackAloneCt() { black_alone_ct_ += 1; }
      void IncAmIndianAlNativeCt() { am_ind_al_native_ct_ += 1; }
      void IncAsianAloneCt() { asian_alone_ct_ += 1; }
      void IncHawaiianPacIslandCt() { hyn_alone_ct_ += 1; }
      void IncTwoOrMoreCt() { two_or_more_ct_ += 1; }
      void IncHispLatCt() { hisp_lat_ct_ += 1; }
      void IncWhiteNotHispLatCt() { white_nh_ct_ += 1; }
      void IncUnspecifiedCt() { unspecified_ct_ += 1; }
      
   friend std::ostream& operator<<(std::ostream &out,  raceAndEthnicity &DD);
   
   private:
      int white_alone_ct_;
      int black_alone_ct_;
      int am_ind_al_native_ct_;
      int asian_alone_ct_;
      int hyn_alone_ct_;
      int two_or_more_ct_;
      int hisp_lat_ct_;
      int white_nh_ct_;
      int unspecified_ct_;
      
};
#endif
