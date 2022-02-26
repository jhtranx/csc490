/* helper routines to read out csv data */
#include "parse.h"
#include <algorithm>
#include <cmath>

#include <typeinfo>

/* helper to strip out quotes from a string */
string stripQuotes(std::string temp) {
    temp.erase(
        remove(temp.begin(), temp.end(), '\"' ),
        temp.end());
    return temp;
}

/* helper: get field from string stream */
/* assume field has quotes for CORGIS */
string getField(std::stringstream &ss) {
    string data, junk;
    //ignore the first quotes
    std::getline(ss, junk, '\"');
    //read the data (not to comma as some data includes comma (Hospital names))
    std::getline(ss, data, '\"');
    //read to comma final comma (to consume and prep for next)
    std::getline(ss, junk, ',');
    //data includes final quote (see note line 18)
    return stripQuotes(data);
}

string getFieldNQ(std::stringstream &ss)
{
    string temp;
    std::getline(ss, temp, ',');
    //std::cout << temp << std:: endl;
    return temp;
}

/* helper: read out column names for CSV file */
void consumeColumnNames(std::ifstream &myFile) {
    std::string line;
    std::string colname;

    // Extract the first line in the file
    std::getline(myFile, line);

    // Create a stringstream from line
    std::stringstream ss(line);

    // Read the column names (for debugging)
    // Extract each column name for debugging
    while(std::getline(ss, colname, ',')) {
    //    std::cout << colname << std::endl;
    }
}

//NEW CODE HERE!!

//note, in Zoe's video, she had 3 params in read_csv but the spec only has two
std::vector<shared_ptr<regionData>> 
   read_csv (std::string filename, typeFlag fileType) {
	//if we have as a parameter "filename" does this mean we call this function twice?
	// for each individual function? 
	
}

/* Read one line from a CSV file for county demographic data specifically */
shared_ptr<demogData> readCSVLineDemog(std::string theLine) {
   std::stringstream ss (theLine);

   string county_ = getField(ss);
   string state_ = getField(ss);
   double pop_over_65_pc_ = stod(getField(ss)) / 100.0;
   double pop_under_18_pc_ = stod(getField(ss)) / 100.0;
   double pop_under_5_pc_ = stod(getField(ss)) / 100.0; 
   double bachelors_deg_pc_ = stod(getField(ss)) / 100.0;
   double hs_grad_pc_ = stod(getField(ss)) / 100.0;

   getField(ss);
   
   double am_indian_al_native_pc_ = stod(getField(ss)) / 100.0;
   double asian_pc_ = stod(getField(ss)) / 100.0;
   double black_pc_ = stod(getField(ss)) / 100.0;
   double latinx_pc_ = stod(getField(ss)) / 100.0;
   double hi_pacific_isle_pc_ = stod(getField(ss)) / 100.0;
   double multi_race_pc_ = stod(getField(ss)) / 100.0;
   double white_pc_ = stod(getField(ss)) / 100.0;
   double white_nh_pc_ = stod(getField(ss)) / 100.0;

   double home_own_pc_ = stod(getField(ss)) / 100.0;
   int num_households_ct_ = stoi(getField(ss));

   getField(ss);
   getField(ss);

   double person_per_house_pc_ = stod(getField(ss));
   int med_household_income_ct_ = stoi(getField(ss));

   getField(ss);

   double foreign_born_pc_ = stod(getField(ss))/100.0;

   for (int i=0; i < 5; i++)
      getField(ss);

   double female_pc_ = stod(getField(ss)) / 100.0;
   int veterans_ct_ = stoi(getField(ss));
   int tot_population_ct_ = stoi(getField(ss));


   for (int i=0; i < 33; i++)
      getField(ss);

   // create counts for raceAndEth

   int white_ct_ = white_pc_ * tot_population_ct_;
   int black_ct_ = black_pc_ * tot_population_ct_;
   int am_indian_al_native_ct_ = am_indian_al_native_pc_ * tot_population_ct_;
   int asian_ct_ = asian_pc_ * tot_population_ct_;
   int hi_pacific_isle_ct_ = hi_pacific_isle_pc_ * tot_population_ct_;
   int multi_race_ct_ = multi_race_pc_ * tot_population_ct_;
   int latinx_ct_ = latinx_pc_ * tot_population_ct_;
   int white_nh_ct_ = white_nh_pc_ * tot_population_ct_;


   raceAndEthnicity race_eth_ = raceAndEthnicity (
      white_ct_, black_ct_, am_indian_al_native_ct_, asian_ct_,
      hi_pacific_isle_ct_, multi_race_ct_, latinx_ct_, white_nh_ct_
   );

   return make_shared<demogData> (
      county_, pop_over_65_pc_, 
      pop_under_18_pc_, pop_under_5_pc_, 
      female_pc_, home_own_pc_, 
      person_per_house_pc_, hs_grad_pc_, 
      bachelors_deg_pc_, foreign_born_pc_, 
      tot_population_ct_, med_household_income_ct_, 
      num_households_ct_, veterans_ct_, 
      race_eth_, state_
   );
}


//read one line of police data
shared_ptr<psData> readCSVLinePolice(std::string theLine) {
    std::stringstream ss(theLine);
    
    //TO DO read in the fields - use getFieldNQ as no quotes!!
    getField(ss); //ignore id
    string name = getField(ss);
    //skip 2
    getField(ss);
    getField(ss);
    //fill in
    string armed = getField(ss);
    getField(ss);
    getField(ss);
    string raceEth = getField(ss);
    string city = getField(ss);
    string state = getField(ss);

    bool signsOfMentalIllness;
    string somiSomiStr = getField(ss);
    transform(somiSomiStr.begin(), somiSomiStr.end(), somiSomiStr.begin(), :: tolower);
    istringstream(somiSomiStr) >> boolalpha >> signsOfMentalIllness;

    getField(ss);
    getField(ss);

    bool bodyCam;
    string bodyCamStr = getField(ss);
    transform(bodyCamStr.begin(), bodyCamStr.end(), bodyCamStr.begin(), :: tolower);
    istringstream(bodyCamStr) >> boolalpha >> bodyCam;

    getField(ss);
    getField(ss);
    getField(ss);

    /* TO DO fix */
    return make_shared<psData>(state, name, city, raceEth, 
        signsOfMentalIllness, armed, bodyCam);
}

//read from a CSV file (for a given data type) return a vector of the data
// DO modify 
void read_csv(std::vector<shared_ptr<regionData>> pileOfData,
    std::string filename, typeFlag fileType) {
    // std::vector<shared_ptr<regionData>> pileOfData;

    std::ifstream myFile(filename);

    if(!myFile.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    if(myFile.good()) {
        consumeColumnNames(myFile);
        std::string line;

        while(std::getline(myFile, line)) {
            if (fileType == DEMOG) {
                pileOfData.push_back(readCSVLineDemog(line));
						else if (fileType == POLICE) {
                pileOfData.push_back(readCSVLinePolice(line));
            }
            else {
                cout << "ERROR - unknown file type" << endl;
                exit(0);
            }
        }
        myFile.close();
    }
}