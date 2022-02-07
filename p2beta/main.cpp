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
    //cool to warm color map 
    array<color, 10> colorMap; 
    colorMap[0] = color(91, 80, 235); //cool 
    colorMap[1] = color(95, 166, 245); 
    colorMap[2] = color(99, 223, 220); 
    colorMap[3] = color(95, 245, 155); 
    colorMap[4] = color(128, 235, 96); //midway 
    colorMap[5] = color(235, 235, 75); 
    colorMap[6] = color(245, 213, 91); 
    colorMap[7] = color(223, 170, 94); 
    colorMap[8] = color(245, 134, 91); 
    colorMap[9] = color(235, 91, 101); //warm  

    cout << "SIZE: " << numArr1.size() << endl;
    int approxSize = sqrt(numArr1.size()) + 1;
    int offSetX = round(sizeX / (double)approxSize);
    int offSetY = round(sizeY / (double)approxSize);

    double topVal1 = (*max_element(numArr1.begin(), numArr1.end()));
    double topVal2 = (*max_element(numArr2.begin(), numArr2.end()));

    cout << "topVAL1: " << topVal1 << endl;
    cout << "topVAL2: " << topVal2 << endl;


    double mag1 = 0;
    double mag2 = 0;
    int i = 0;
    int j = 0;

    for (int w = 0; w < numArr1.size(); w++) {
        

        color cool = color(91, 80, 235); //num1 
        color warm = color(235, 91, 101); // num2  
        color back = color(0, 0, 0); // num2  

        // mag1 = ((double)numArr1[w] / topVal1);
        // mag2 = ((double)numArr2[w] / topVal2);

        double rad1;
        double rad2;

        rad1 = (double)numArr1[w] * (1.0 / (topVal1));
        rad2 = (double)numArr2[w] * (1.0 / (topVal2));
        

        if (rad1 > rad2) {
            cout << "r1 > r2" <<endl;
    
            theEllipses.push_back(ellipse(vec2(i * offSetX + 0.5*offSetX, j * offSetY + 0.5*offSetY), 
                                rad1*20, 5, cool));

			theEllipses.push_back(ellipse(vec2(i * offSetX + 0.5*offSetX, j * offSetY + 0.5*offSetY), 
                                rad2*20, 6, back));

        }
        else {
            cout << "r2 > r1" <<endl;
            

            theEllipses.push_back(ellipse(vec2(i * offSetX + 0.5*offSetX, j * offSetY + 0.5*offSetY), 
                                rad2*20, 5, warm));

            theEllipses.push_back(ellipse(vec2(i * offSetX + 0.5*offSetX, j * offSetY + 0.5*offSetY), 
                                rad1*20, 6, back));
        }
        cout << "numArr1: " << numArr1[w] << endl;
        cout << "numArr2: " << numArr2[w] << endl;

        cout << "mag1: " << mag1 << endl;
        cout << "mag2: " << mag2 << endl;

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
    
    cout << "XXX" << endl;
    int i = 0;
	for (const auto &obj : theStateData) {
		std::cout << *obj << std::endl;
		i++;
		if (i > 15)
			break;
	}

    std::vector<double> numArr1 = {};
    std::vector<double> numArr2 = {};
    std::vector<int> totWALonePerc = {};
    
    numArr1 = theAnswers.getLCasesList(); 
    numArr2 = theAnswers.getLatinPercentList();   
    

    // totCaseCt = theAnswers.getCaseCtList();    
    // totAfricanAmericanCt = theAnswers.getAACasesList();

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
		} else {
			cout << "Error cannot open outfile" << endl;
			exit(0);
		}
	}


    return 0;
}



