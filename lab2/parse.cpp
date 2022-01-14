#include <algorithm>
#include <memory>
/* helper routines to read out csv data */
#include "parse.h"

/* starter - replace with your revised version! */

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
        //std::cout << colname << std::endl;
    }
}

/* Read one line from a CSV file for county demographic data specifically
   TODO: add fields here - think about type */
shared_ptr<demogData> readCSVLineDemog(std::string theLine) {
    std::stringstream ss(theLine);
    
    string name = getField(ss);
    string state = getField(ss);
    //skip population change
    getField(ss);
    int totalPop2020 = stoi(getField(ss));

    //skip population 2010
    getField(ss);
    double popUnder5 = stod(getField(ss)); 
    double popUnder18 = stod(getField(ss));  
    double popOver65 = stod(getField(ss));

    //skip race and ethnicities for now...
    getField(ss);
    getField(ss);
    getField(ss);
    getField(ss);
    getField(ss);
    getField(ss);
    getField(ss);
    getField(ss);
    getField(ss);
    //after race and ethnicities

    int veterans = stoi(getField(ss));
    double foreignBorn = stod(getField(ss));
    getField(ss);
    double homeOwn = stod(getField(ss));
    getField(ss);
    getField(ss);
    double personPerHouse = stod(getField(ss));
    getField(ss);
    getField(ss);
    double highSchool = stod(getField(ss));
    double bachelorsDeg = stod(getField(ss));
    getField(ss);
    getField(ss);
    getField(ss);
    getField(ss);
    int medIncome = stoi(getField(ss));
    getField(ss);
    getField(ss);
    getField(ss);
    getField(ss);
    getField(ss);
    getField(ss);
    getField(ss);
    getField(ss);
    getField(ss);
    getField(ss);
    getField(ss);

    //TODO when you grab more data modify below loop to make sure you grab 
    //the right field

    //now skip over some data
    for (int i=0; i < 33; i++)
        getField(ss);

    //TODO change to constructor for the data we want to aggregate
    // return make_shared<demogData>(name, state, popOver65, popUnder18,
    //         popUnder5, totalPop2020);
    return make_shared<demogData>(name, state, popOver65, popUnder18, popUnder5, totalPop2020, "na", "na", medIncome, homeOwn, personPerHouse, veterans, highSchool, bachelorsDeg, foreignBorn);
}


//read from a CSV file (for a given data type) return a vector of the data
// DO NOT modify for lab01
std::vector<shared_ptr<demogData> > read_csv(std::string filename, typeFlag fileType) {
    //the actual data
    std::vector<shared_ptr<demogData> > theData;

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    if(myFile.good()) {
        consumeColumnNames(myFile);

        // Helper vars
        std::string line;

        // Now read data, line by line and create demographic dataobject
        while(std::getline(myFile, line)) {
            if (fileType == DEMOG) {
                theData.push_back(readCSVLineDemog(line));
            } else {
                cout << "ERROR - unknown file type" << endl;
                exit(0);
            }
        }

        // Close file
        myFile.close();
    }

    return theData;
}
