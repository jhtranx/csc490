/* ZJW simple C++ code to write out a PPM file representing an ellipse(s) */
// Emily Truong and Justin Tran
// The changes we made from the alum's suggestion were:
// 	1. Made eval const because we don't expect eval to modify underlying objects.
// 	2. Changed "radi1" to "radii1" for readability.
// 	3. Modified eval for readability.

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "ppmR.h"
#include "color.h"
#include "rect.h"
#include "ellipse.h"

using namespace std;


/*write out PPM data, using the defined implicit equation 
  interior points write a differnt color then exterior points */

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


/*read command line arguments and write out new ascii file of given size */
int main(int argc, char *argv[]) {

	ofstream outFile;
	int sizeX, sizeY;

	vector<color> niceC;
	niceC.push_back(color(91, 49, 245));
	niceC.push_back(color(91, 212,199));
	niceC.push_back(color(182, 235, 113));
	niceC.push_back(color(212, 169,91));
	niceC.push_back(color(247, 106, 120));

	// create all the equations for a simple asci face
	// layer values larger is closer - ie on top
	vector<shared_ptr<ellipse>> theEllipses;
	theEllipses.push_back(make_shared<ellipse>(vec2(150, 180), 60, 80, niceC[1], 2));	
	theEllipses.push_back(make_shared<ellipse>(vec2(130, 140), 10, 23, niceC[2], 3));
	theEllipses.push_back(make_shared<ellipse>(vec2(130, 145), 4, 4, color(128), 4));
	theEllipses.push_back(make_shared<ellipse>(vec2(160, 140), 10, 23, niceC[2], 3));
	theEllipses.push_back(make_shared<ellipse>(vec2(160, 145), 4, 4, color(128), 4));
	theEllipses.push_back(make_shared<ellipse>(vec2(150, 210), 40, 20, color(0), 3));

	//collection of rectangles (empty in base)
	vector<shared_ptr<rect>> theRects;
	theRects.push_back(make_shared<rect>(vec2(100, 100), vec2(300, 300), color(255, 255, 0)));
	theRects.push_back(make_shared<rect>(vec2(50, 50), vec2(100, 100), color(255, 255, 0)));
	theRects.push_back(make_shared<rect>(vec2(300, 300), vec2(400, 400), color(255, 255, 0)));

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
