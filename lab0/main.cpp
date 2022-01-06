/* ZJW simple C++ code to write out a PPM file representing an ellipse(s) */
/* Example run: ./a.out 400 400 out.ppm */

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "ppmR.h"
#include "color.h"
#include "ellipse.h"

using namespace std;


/*write out PPM data, using the defined implicit equation 
  interior points write a differnt color then exterior points 
  TODO change to work on a collection of ellipses*/
void writeOut(ostream& out, ppmR& theWriter, ellipse face[]) {

	float res;
	color inC;
	color background(12, 34, 56);
	bool inTrue = false;

	//for every point in the 2D space
	for (int y=0; y < theWriter.height; y++) {
		for (int x =0; x < theWriter.width; x++) {

			inTrue = false;
			//TODO, change to iterate through all possible equations (note 'front' determined by order in vector)
			for (int i = 0; i < 6; i++)
			{
				res = face[i].eval(x, y);
				if (res < 0) {
					inC = face[i].getInC();
					inTrue = true;
					break;
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


/*read command line arguments and write out new ppm file of given size */
int main(int argc, char *argv[]) {

	ofstream outFile;
	int sizeX, sizeY;
	
	// TODO change to work on a collection of ellipses
	// specifically create all the equations for a simple asci face
	// including modifying code as needed to support many ellipses
	// note order in collection may matter for drawing (what shape is on top?)
	ellipse head(200, 200, 120, 160, color(0, 0, 0));
	ellipse lPupil(100, 100, 30, 30, color(255, 255, 255));
	ellipse rPupil(300, 100, 30, 30, color(255, 255, 255));
	ellipse lSclera(100, 100, 40, 40, color(255, 0, 0));
	ellipse rSclera(300, 100, 40, 40, color(255, 0, 0));
	ellipse mouth(200, 300, 120, 40, color(0, 255, 0));

	ellipse face[6] {lPupil, rPupil, lSclera, rSclera, mouth, head};

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
			writeOut(outFile, theWriter, face);
		} else {
			cout << "Error cannot open outfile" << endl;
			exit(0);
		}
	}

}
