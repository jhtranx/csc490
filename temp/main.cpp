//new main to work with data structure redesign
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include "demogData.h"
#include "demogCombo.h"
#include "psData.h"
#include "psCombo.h"
#include "parse.h"
#include "visitorReport.h"

using namespace std;

int main() {
	std::vector<shared_ptr<regionData>> pileOfData;
	
	//note, we may want to pass in the pileOfData instead of create it within
	//read_csv because now we will have two different piles from each read_csv call
	//instead of a single pile ...
	read_csv(pileOfData, "county_demographics.csv", DEMOG);
	read_csv(pileOfData, "fatal-police-shootings-data-Q.csv", POLICE);

	visitorReport report;
	for (const auto &obj : pileOfData) {
		obj->Accept(report);
	}
	// report.display();

	return 0;
}