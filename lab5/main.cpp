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
				vector<shared_ptr<shape>> Shapes) {

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

			/* compare my ret.h with yours */
			for (auto shape: Shapes) {
				if (shape->eval(x, y) && shape->getDepth() > curDepth){
					inC = shape->getInC();
					inTrue = true;
					curDepth = shape->getDepth();
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
void createTriangle(vector<shared_ptr<shape>>& shapes, vec2 offSet) {

	//create a vector of vertices for the triangle 
	//vertices specified counter clockwise!
	vector<vec2> triVerts;
	triVerts.push_back(vec2(offSet.x() + nicerRand(-10, 10), offSet.y()+50+nicerRand(-10, 20)));
	triVerts.push_back(vec2(offSet.x() + 50+nicerRand(-10, 10), offSet.y()+10+nicerRand(-20, 10)));
	triVerts.push_back(vec2(offSet.x() + 100+nicerRand(-10, 10), offSet.y()+50+nicerRand(-10, 20)));

	shapes.push_back(make_shared<Polygon>(triVerts, nicerRand(4,10), color(nicerRand(0, 25), nicerRand(0, 55), nicerRand(0, 255) ) ) );

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
	vector<shared_ptr<shape>> Shapes;
	color ellipseColor = color(61, 101, 110);
	Shapes.push_back(make_shared<ellipse>(50, 100, 11*6, 11*5, 11, ellipseColor));	
	Shapes.push_back(make_shared<Rect>(vec2(200, 200), 60, 60, color(120), 14));

	//make a nice matrix of triangles (rows of blue mountains)
	for (int x=0; x < 4; x++)
		for (int y=0; y < 4; y++)
		createTriangle(Shapes, vec2(x*(sizeX/4.0), y*(sizeY/4.0)));

	if (outFile) {
		cout << "writing an image of size: " << sizeX << " " << sizeY << " to: " << argv[3] << endl;
		theWriter.writeHeader(outFile);
		writeOut(outFile, theWriter, Shapes);
	} else {
		cout << "Error cannot open outfile" << endl;
		exit(0);
	}

}
