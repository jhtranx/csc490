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
#include "visitorCombineState.h"
#include "visitorCombineCounty.h"

using namespace std;

int main() {
	vector<shared_ptr<regionData>> pileOfData;

	read_csv(pileOfData, "county_demographics.csv", DEMOG);
	read_csv(pileOfData, "fatal-police-shootings-data-Q.csv", POLICE);

	cout << "before uscities" << endl;

	visitorReport report;
	visitorCombineState state_report_;
	visitorCombineCounty county_report_ = visitorCombineCounty("uscities.csv");

	cout << "after uscities" << endl;

	for (const auto &obj : pileOfData) {
		obj->Accept(county_report_);
	}
	cout << "size of map: " << county_report_.GetDemogComboMap().size() << endl;
	for (const auto &state : county_report_.GetDemogComboMap()) {
		cout << "before print report" << endl;
		std::cout << *state.second << std::endl;
	}
	
	// report.display();

	return 0;
}