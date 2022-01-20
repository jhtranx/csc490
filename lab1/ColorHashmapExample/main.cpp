/* ZJW simple C++ code to write out a PPM file representing an ellipse(s) */

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "ppmR.h"
#include "color.h"
#include "rect.h"
#include "ellipse.h"
#include <map>

using namespace std;


/*write out PPM data, using the defined implicit equation 
  interior points write a differnt color then exterior points */

void writeOut(ostream& out, ppmR& theWriter, 
				vector<shared_ptr<ellipse>> IEs, vector<shared_ptr<Rect>> Rs) {

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
			/*
			//uncomment this section when you've written rect.h
			for (auto rect: Rs) {
				if (rect->evalIn(x, y) && rect->getDepth() > curDepth){
					inC = rect->getInC();
					inTrue = true;
					curDepth = rect->getDepth();
				}
			}
			*/
			if (inTrue) {			
				theWriter.writePixel(out, x, y, inC);
			}
			else
				theWriter.writePixel(out, x, y, background);
		}
		theWriter.writeNewLine(out);
	}
}


/*read command line arguments and write out new ascii file of given size */
int main(int argc, char *argv[]) {

	ofstream outFile;
	int sizeX, sizeY;

	map<string, color> colorMap;
	colorMap["purple"] = color(91, 49, 245);
	colorMap["aqua"] = color(91, 212,199);
	colorMap["green"] = color(182, 235, 113);
	colorMap["orange"] = color(212, 169,91);
	colorMap["pink"] = color(247, 106, 120);

	// create all the equations for a simple asci face
	// layer values larger is closer - ie on top
	vector<shared_ptr<ellipse>> theEllipses;
	theEllipses.push_back(make_shared<ellipse>(150, 180, 60, 80, 2, colorMap["orange"]));
	theEllipses.push_back(make_shared<ellipse>(130, 140, 10, 23, 3, colorMap["pink"]));
	theEllipses.push_back(make_shared<ellipse>(130, 145, 4, 4, 4, colorMap["aqua"]));
	theEllipses.push_back(make_shared<ellipse>(160, 140, 10, 23, 3, colorMap["orange"]));
	theEllipses.push_back(make_shared<ellipse>(160, 145,4, 4, 4, colorMap["aqua"]));
	theEllipses.push_back(make_shared<ellipse>(150, 210, 40, 20, 3, colorMap["orange"]));

	//collection of rectangles (empty in base)
	vector<shared_ptr<Rect>> theRects;

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

}
