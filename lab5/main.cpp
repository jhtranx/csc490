/* ZJW simple C++ code to write out a PPM file representing an ellipse(s) */

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "ppmR.h"
#include "shape.h"
#include "color.h"
#include "rect.h"
#include "ellipse.h"
#include "polygon.h"
#include "util.h"

using namespace std;


/*write out PPM data, using the defined implicit equation 
  interior points write a differnt color then exterior points */
void writeOut(ostream& out, ppmR& theWriter, 
				vector<shared_ptr<shape>> IEs, vector<shared_ptr<Rect>> Rs,
				vector<shared_ptr<Polygon>> Ps) {

	float res;
	color inC;
	color drawC;
	color background(12, 34, 56);
	bool inTrue = false;
	double curDepth = -1.0;

	//for every point in the 2D space
	for (int y=0; y < theWriter.height; y++) {
		for (int x =0; x < theWriter.width; x++) {

			inTrue = false;
			curDepth = -1;
			//iterate through all possible equations
			for (shared_ptr<shape> eq : IEs) {
				shared_ptr<ellipse> ellip = std::static_pointer_cast<ellipse>(eq);
				res = ellip->eval(x, y);
				if (res < 0 && eq->getDepth() > curDepth) {
					inC = eq->getInC();
					inTrue = true;
					curDepth = eq->getDepth();
				}
			}
			/* compare my ret.h with yours */
			for (auto rect: Rs) {
				if (rect->evalIn(x, y) && rect->getDepth() > curDepth){
					inC = rect->getInC();
					inTrue = true;
					curDepth = rect->getDepth();
				}
			}

			//loop through any polygons
			for (auto poly: Ps) {
				if (poly->eval(x, y) && poly->getDepth() > curDepth){
					inC = poly->getInC();
					inTrue = true;
					curDepth = poly->getDepth();
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

/* make slightly random triangle takes offfSet to help spread */
void createTriangle(vector<shared_ptr<Polygon>>& thePolygons, vec2 offSet) {

	//create a vector of vertices for the triangle 
	//vertices specified counter clockwise!
	vector<vec2> triVerts;
	triVerts.push_back(vec2(offSet.x() + nicerRand(-10, 10), offSet.y()+50+nicerRand(-10, 20)));
	triVerts.push_back(vec2(offSet.x() + 50+nicerRand(-10, 10), offSet.y()+10+nicerRand(-20, 10)));
	triVerts.push_back(vec2(offSet.x() + 100+nicerRand(-10, 10), offSet.y()+50+nicerRand(-10, 20)));

	thePolygons.push_back(make_shared<Polygon>(triVerts, nicerRand(4,10), color(nicerRand(0, 25), nicerRand(0, 55), nicerRand(0, 255) ) ) );

}

/*read command line arguments and write out new ascii file of given size */
int main(int argc, char *argv[]) {

	ofstream outFile;
	int sizeX, sizeY;

	string outFilename;
	if (argc < 4) {
		cerr << "Error format: a.out sizeX sizeY outfileName" << endl;
		exit(0);
	} 

	sizeX = stoi(argv[1]);
	sizeY = stoi(argv[2]);
	ppmR theWriter(sizeX, sizeY);
	outFile.open(argv[3]);

	// layer values larger is closer - ie on top
	vector<shared_ptr<shape>> theEllipses;
	color ellipseColor = color(61, 101, 110);
	theEllipses.push_back(make_shared<ellipse>(50, 100, 11*6, 11*5, 11, ellipseColor));	

	//collection of rectangles
	vector<shared_ptr<Rect>> theRects;
	theRects.push_back(make_shared<Rect>(vec2(200, 200), 60, 60, color(120), 14));

	//the convex polygons
	vector<shared_ptr<Polygon>> thePolygons;

	//make a nice matrix of triangles (rows of blue mountains)
	for (int x=0; x < 4; x++)
		for (int y=0; y < 4; y++)
		createTriangle(thePolygons, vec2(x*(sizeX/4.0), y*(sizeY/4.0)));


	if (outFile) {
		cout << "writing an image of size: " << sizeX << " " << sizeY << " to: " << argv[3] << endl;
		theWriter.writeHeader(outFile);
		writeOut(outFile, theWriter, theEllipses, theRects, thePolygons);
	} else {
		cout << "Error cannot open outfile" << endl;
		exit(0);
	}

}
