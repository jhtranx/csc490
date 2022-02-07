#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <memory>
#include "demogData.h"
#include "parse.h"
#include "dataAQ.h"
#include "color.h"
#include "ellipse.h"
#include "ppmR.h"
#include <array>


using namespace std;

void writeOut(ostream& out, ppmR& theWriter, 
			    vector<ellipse> Es) {

	float res;
	color inC;
	color background(0, 0, 0);
	bool inTrue = false;
	double curDepth = -1.0;

	//for every point in the 2D space
	for (int y=0; y < theWriter.height; y++) {
		for (int x =0; x < theWriter.width; x++) {

			inTrue = false;
			curDepth = -1;
			
			for (auto ellipse: Es) {
				if (ellipse.eval(x, y) && ellipse.getDepth() > curDepth){
					inC = ellipse.getInC();
					inTrue = true;
					curDepth = ellipse.getDepth();
				}
			}
			if (inTrue) {			
				theWriter.writePixel(out, x, y, inC);
			}
			else
				theWriter.writePixel(out, x, y, background);
		}
		theWriter.writeNewLine(out);
	}
}

void createGrid(vector<double> numArr1, vector<double> numArr2, 
                vector<ellipse> &theEllipses,
                int sizeX, int sizeY) {

    int approxSize = sqrt(numArr1.size()) + 1;
    int offSetX = round(sizeX / (double)approxSize);
    int offSetY = round(sizeY / (double)approxSize);

    double topVal1 = (*max_element(numArr1.begin(), numArr1.end()));
    double topVal2 = (*max_element(numArr2.begin(), numArr2.end()));

    double mag1 = 0;
    double mag2 = 0;
    int i = 0;
    int j = 0;

    for (int w = 0; w < numArr1.size(); w++) {
        

        color cool = color(91, 80, 235); //num1 
        color warm = color(235, 91, 101); // num2  
        color back = color(0, 0, 0); // num2  

        double rad1;
        double rad2;

        rad1 = (double)numArr1[w] * (1.0 / (topVal1));
        rad2 = (double)numArr2[w] * (1.0 / (topVal2));
        

        if (rad1 > rad2) {
            theEllipses.push_back(ellipse(vec2(i * offSetX + 0.5*offSetX, j * offSetY + 0.5*offSetY), 
                                rad1*20, 5, cool));

			theEllipses.push_back(ellipse(vec2(i * offSetX + 0.5*offSetX, j * offSetY + 0.5*offSetY), 
                                rad2*20, 6, back));

        }
        else {
            theEllipses.push_back(ellipse(vec2(i * offSetX + 0.5*offSetX, j * offSetY + 0.5*offSetY), 
                                rad2*20, 5, warm));

            theEllipses.push_back(ellipse(vec2(i * offSetX + 0.5*offSetX, j * offSetY + 0.5*offSetY), 
                                rad1*20, 6, back));
        }

        cout << "num1: " << numArr1[w] << endl;
        cout << "num2: " << numArr2[w] << endl;
        cout << "r1: " << rad1 << endl;
        cout << "r2: " << rad2 << endl;
        
        i++;
        if (i > approxSize-1) {
            i = 0;
            j++;
        }
    }
}

int main(int argc, char *argv[]) {

    ofstream outFile;
	int sizeX, sizeY;

    //read in a csv file and create a vector of objects representing each counties data
    std::vector<shared_ptr<psData>> thePoliceData = read_csvPolice(
            "fatal-police-shootings-data-Q.csv", POLICE);
    std::vector<shared_ptr<demogData>> theStateData = read_csv(
			"county_demographics.csv", DEMOG);

    dataAQ theAnswers;
    theAnswers.createStateData(theStateData);
    theAnswers.createStatePoliceData(thePoliceData);
    
    // int i = 0;
	// for (const auto &obj : theStateData) {
	// 	std::cout << *obj << std::endl;
	// 	i++;
	// 	if (i > 15)
	// 		break;
	// }

    std::vector<double> numArr1 = {};
    std::vector<double> numArr2 = {};
    std::vector<int> totWALonePerc = {};
    
    numArr1 = theAnswers.getWCasesList(); 
    numArr2 = theAnswers.getWhiteAlonePercentList();   

    if (argc < 4) {
		cerr << "Error format: a.out sizeX sizeY outfileName" << endl;
	} else {
		sizeX = stoi(argv[1]);
		sizeY = stoi(argv[2]);
		ppmR theWriter(sizeX, sizeY);
		outFile.open(argv[3]);

        vector<ellipse> theEllispes;
        createGrid(numArr1, numArr2, theEllispes, sizeX, sizeY);

		if (outFile) {
			cout << "writing an image of size: " << sizeX << " " << sizeY << " to: " << argv[3] << endl;
			theWriter.writeHeader(outFile);
			writeOut(outFile, theWriter, theEllispes);

            theAnswers.reportTopTenStatesPS();
	        theAnswers.reportBottomTenStatesHomeOwn();

		} else {
			cout << "Error cannot open outfile" << endl;
			exit(0);
		}
	}


    return 0;
}



