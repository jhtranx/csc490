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
#include "stats.h"
#include "statTool.h"
#include "visitorReport.h"
#include "visitorCombineState.h"
#include "visitorCombineCounty.h"

using namespace std;

int main() {
	vector<shared_ptr<regionData>> pileOfData;

	read_csv(pileOfData, "county_demographics.csv", DEMOG);
	read_csv(pileOfData, "fatal-police-shootings-data-Q.csv", POLICE);

	visitorReport report;
	visitorCombineState state_report_;
	visitorCombineCounty county_report_ = visitorCombineCounty("uscities.csv");

	for (const auto &obj : pileOfData) {
		obj->Accept(county_report_);
	}
	// for (const auto &state : county_report_.GetDemogComboMap()) {
	// 	std::cout << *state.second << std::endl;
	// }

	//create a visitor to combine the state data
	visitorCombineState theStates;
	statTool::createStateData(pileOfData, theStates);
	//theStates.printAllCombo();

	//create a visitor to combine the county data
	visitorCombineCounty theCounties("uscities.csv");
	statTool::createCountyData(pileOfData, theCounties);
	cout << "number of unmatched incidents: " << theCounties.GetNoMatch() << endl;
	//305 at this moment

	//DEBUG only printing top ten for testing
	theCounties.PrintNCombo(20);
	cout << "stats work:" << endl;
	cout << "state home ownership and BA: " << endl;
	statTool::computeStatsDemogRegionData(&theStates, &demogData::GetHomeOwnPercent, &demogData::GetBachelorsDegPercent,
		&demogData::GetHomeOwnCount, &demogData::GetBachelorsDegCount);

	cout << "county home ownership and BA: " << endl;
	statTool::computeStatsDemogRegionData(&theCounties, &demogData::GetHomeOwnPercent, &demogData::GetBachelorsDegPercent,
		&demogData::GetHomeOwnCount, &demogData::GetBachelorsDegCount);

	cout << "county PS mental illness to African American " << endl;
	statTool::computeStatsPSData(&theCounties, &psCombo::GetNumMentalIllness, 
		&psCombo::GetBlackCt);

	cout << "county PS mental illness to White " << endl;
	statTool::computeStatsPSData(&theCounties, &psCombo::GetNumMentalIllness, 
		&psCombo::GetWhiteCt);

	cout << "State data Pop veterans and high school and up: " << endl;
	statTool::computeStatsDemogRegionData(&theStates, 
	&demogData::GetVeteransPercent, &demogData::GetHighSchoolGradPercent,
		&demogData::GetVeteransCount, &demogData::GetHighSchoolGradCount);
	
	// report.display();

	return 0;
}