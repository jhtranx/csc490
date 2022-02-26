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
	vector<shared_ptr<regionData>> pileOfData;

	read_csv(pileOfData, "county_demographics.csv", DEMOG);
	read_csv(pileOfData, "fatal-police-shootings-data-Q.csv", POLICE);

	visitorReport report;
	for (const auto &obj : pileOfData) {
		obj->Accept(report);
	}
	// report.display();

	return 0;
}