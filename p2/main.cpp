#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "demogData.h"
#include "parse.h"
#include "dataAQ.h"

using namespace std;

int main() {

	dataAQ theAnswers;

	//read in a csv file and create a vector of objects representing each counties data
	std::vector<shared_ptr<demogData>> theData = read_csv(
			"county_demographics.csv", DEMOG);


	std::vector<shared_ptr<psData>> thePoliceData = read_csvPolice(
			"fatal-police-shootings-data-Q.csv", POLICE);

	//debug print out if needed left for your use in testing
	/*
	int i = 0;
	for (const auto &obj : thePoliceData) {
		std::cout << *obj << std::endl;
		i++;
		if (i > 15)
			break;
	}

	i = 0;
	for (const auto &obj : theData) {
		std::cout << *obj << std::endl;
		i++;
		if (i > 15)
			break;
	}
	*/
	//one example of how to print required - ADD OTHERS
	
	
	theAnswers.createStateData(theData);
	theAnswers.createStatePoliceData(thePoliceData);

	cout << "*** the state that needs the most pre-schools**" << endl;
	string query = theAnswers.youngestPop();
	cout << "Name of state: " << query << endl;
	if (theAnswers.getStateData(query) != nullptr){
		cout << *(theAnswers.getStateData(query)) << endl;
	} else{
		cout << "Did you read the lab instructions?" << endl;
	}

	cout << "*** the state with largest number of people per household**" << endl;
	query = theAnswers.mostPerPerHouse();
	cout << "Name of state: " << query << endl;
	if (theAnswers.getStateData(query) != nullptr){
		cout << *(theAnswers.getStateData(query)) << endl;
	} else{
		cout << "Did you read the lab instructions?" << endl;
	}

	theAnswers.reportTopTenStatesPS();
	theAnswers.reportBottomTenStatesHomeOwn();
	
	return 0;
}

