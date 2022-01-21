#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "demogData.h"
#include "parse.h"
#include "dataAQ.h"
#include "color.h"
#include "rect.h"

using namespace std;

void writeOut(ostream& out, ppmR& theWriter, 
				vector<shared_ptr<ellipse>> IEs, vector<shared_ptr<rect>> Rs) {

	float res;
	color inC;
	color background(12, 34, 56);
	bool inTrue = false;
	double curDepth = -1.0;

	//for every point in the 2D space
	for (int y=0; y < theWriter.height; y++) {
		for (int x =0; x < theWriter.width; x++) {

			inTrue = false;
			curDepth = -1;
			//iterate through all possible equations (note 'front' determined by order in vector)
			for (auto eq : IEs) {
				res = eq->eval(x, y);
				if (res < 0 && eq->getDepth() > curDepth) {
					inC = eq->getInC();
					inTrue = true;
					curDepth = eq->getDepth();
				}
			}
			
			//uncomment this section when you've written rect.h
			for (auto rect: Rs) {
				if (rect->eval(x, y) && rect->getDepth() > curDepth){
					inC = rect->getInC();
					inTrue = true;
					curDepth = rect->getDepth();
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

void createGrid(vector<float> theNumbers, vector<Rect> &theRects, int sizeX, int sizeY) {
    //cool to warm color map 
    std::array<color, 10> colorMap; 
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

    int approxSize = sqrt(theNumbers.size());
    int offSetX = round(sizeX / approxSize);
    int offSetY = round(sizeY / approxSize);

    double topVal = round(*max_element(theNumbers.begin(), theNumbers.end()));

    double mag = 0;
    int i;
    int j;
    for (auto entry : theNumbers) {
        mag = round((colorMap.size() - 1) * (entry / topVal));
        theRects.push_back(Rect(vec2(0 + i * offSetX, sizeY - j * offSetY), 
                                offSetX, offSetY, 5, colorMap[mag]));
        i++;
        if (i > approxSize) {
            i = 0;
            j++;
        }
    }
}

int main() {

    int sizeX, sizeY;
    //read in a csv file and create a vector of objects representing each counties data
    std::vector<shared_ptr<demogData>> theData = read_csv(
            "county_demographics2014.csv", DEMOG);

    std::vector<int> foreignBorn;
    std::vector<int> hsAndUp;
    std::vector<int> baAndUp;

     //debug print out - uncomment if you want to double check your data

    for (const auto &obj : theData) {
        std::cout << *obj << std::endl;

        foreignBorn.push_back(round((obj->getForeignBorn() / 100) * obj->getPopulation()));
        hsAndUp.push_back(round((obj->getHighSchoolGrad() / 100) * obj->getPopulation()));
        baAndUp.push_back(round((obj->getBachelorsDeg() / 100) * obj->getPopulation()));
    }

    int maxFb = 0;
    int maxHs = 0;
    int maxBa = 0;

    for (int i = 0; i < foreignBorn.size(); i++) {
        if (foreignBorn.at(i) > maxFb)
            maxFb = foreignBorn.at(i);
        if (hsAndUp.at(i) > maxHs)
            maxHs = hsAndUp.at(i);
        if (baAndUp.at(i) > maxBa)
            maxBa = baAndUp.at(i);
    }

    cout << "MaxFb" << maxFb << endl;
    cout << "MaxHs" << maxHs << endl;
    cout << "MaxBa" << maxBa << endl;


    if (argc < 4) {
		cerr << "Error format: a.out sizeX sizeY outfileName" << endl;
	} else {
		sizeX = stoi(argv[1]);
		sizeY = stoi(argv[2]);
		ppmR theWriter(sizeX, sizeY);
		outFile.open(argv[3]);
		if (outFile) {
			cout << "writing an image of size: " << sizeX << " " << sizeY << " to: " << argv[3] << endl;
			theWriter.writeHeader(outFile);
			writeOut(outFile, theWriter, theEllipses, theRects);
		} else {
			cout << "Error cannot open outfile" << endl;
			exit(0);
		}
	}


    return 0;
}

