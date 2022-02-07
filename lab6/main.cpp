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

void createGrid(vector<int> theNumbers, vector<ellipse> &theEllipses, int sizeX, int sizeY) {
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

    cout << "SIZE: " << theNumbers.size() << endl;
    int approxSize = sqrt(theNumbers.size()) + 1;
    int offSetX = round(sizeX / (double)approxSize);
    int offSetY = round(sizeY / (double)approxSize);

    double topVal = round(*max_element(theNumbers.begin(), theNumbers.end()));

    double mag = 0;
    int i = 0;
    int j = 0;
    for (auto entry : theNumbers) {
        // cout << "wow: " << entry / topVal << endl;
        mag = round((colorMap.size() - 1) * (entry / topVal));
        // cout << "color: " << mag << endl;

        // cout << "vec2X: " << 0 + i * offSetX << endl;
        // cout << "vec2Y: " << sizeY - j * offSetY << endl;
        j * (offSetY - sizeY);
        // cout << "sizeY: " << sizeY<< endl;
        // cout << "j: " << j << endl;
        // cout << "i: " << i << endl;
        // cout << "offSetY: " << offSetY << endl;

        // cout << "offX: " << offSetX << endl;
        // cout << "offY: " << offSetY << endl;

        theEllipses.push_back(ellipse(vec2(i * offSetX + 0.5*offSetX, j * offSetY + 0.5*offSetY), 
                                mag*3, 5, colorMap[mag]));

        
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

    dataAQ theAnswers;
    theAnswers.createStatePoliceData(thePoliceData);

    std::vector<int> totCaseCt = {};
    std::vector<int> totAfricanAmericanCt = {};

    totCaseCt = theAnswers.getCaseCtList();    
    totAfricanAmericanCt = theAnswers.getAfricanAmericanCtList();

    int maxCase = 0;
    int maxAA = 0;

    for (int i = 0; i < totCaseCt.size(); i++) {
        if (totCaseCt.at(i) > maxCase)
            maxCase = totCaseCt.at(i);
        if (totAfricanAmericanCt.at(i) > maxAA)
            maxAA = totAfricanAmericanCt.at(i);
    }

    if (argc < 4) {
		cerr << "Error format: a.out sizeX sizeY outfileName" << endl;
	} else {
		sizeX = stoi(argv[1]);
		sizeY = stoi(argv[2]);
		ppmR theWriter(sizeX, sizeY);
		outFile.open(argv[3]);

        vector<ellipse> theEllispes;
        createGrid(totCaseCt, theEllispes, sizeX, sizeY);
        createGrid(totAfricanAmericanCt, theEllispes, sizeX, sizeY);

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



