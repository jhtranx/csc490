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
// HMC_CR: style: Generally, I've been counciled to avoid broad "using" directives, unless there is a very firm reason for it. This is somewhat different from the rationale for avoiding them in header files, however, and is somewhat more permissable if merited.
// HMC_CR:   see https://google.github.io/styleguide/cppguide.html#Namespaces


/*write out PPM data, using the defined implicit equation 
  interior points write a differnt color then exterior points */
// HMC_CR: style: Generally, prefer // comments to C /* block comments. The other comment style is perfectly functional, but has implications wrt comment things _out_ via /*.
// HMC_CR: This should probably also note the behavior of this code with respect to pixels which are inside multiple Ellipse regions.
// HMC_CR: "differnt" -> "different".
void writeOut(ostream& out, ppmR& theWriter, vector<shared_ptr<ellipse>>& IEs) {
// HMC_CR: It seems like IEs could be a const reference, since it is only read from.
// HMC_CR: style: Prefer placing "const" parameters (which it seems like IEs is) the beginning of the parameter list, with mutable arguments after.

	float res;
	color inC;
	color background(12, 34, 56);
	// HMC_CR: constexpr or const (if for some reason the compiler objects to constexpr)?
	bool inTrue = false;
	// HMC_CR: "inTrue" is a little difficult to interpret - would a more evocative name be "inside_any_shape"?
	//   Note in particular that the boolean nature is more-or-less implicit in the type; prefer description of the intention with the name.
	// HMC_CR: Generally, these variables should be defined at the most nested scope possible -- most importantly, this tends to allow us to define the variables as const, with a singular initializing expression -- which makes it harder for us to accidentally use "stale" loop carried variables.

	//for every point in the 2D space
	for (int y=0; y < theWriter.height; y++) {
		for (int x =0; x < theWriter.width; x++) {

			inTrue = false;
			//iterate through all possible equations (note 'front' determined by order in vector)
			for (auto eq : IEs) {
				// HMC_CR: Should should probably be `const auto& eq : IEs`? (ie, const ref for-each, rather than mutable value for-each?)
				res = eq->eval(x, y);
				// HMC_CR: Relative to the "center" of each pixel, should this test (x + 0.5), (y + 0.5) ? (ie, is this implicitly testing the upper-left corner?).
				if (res < 0) {
					inC = eq->getInC();
					inTrue = true;
				}
			}
			if (inTrue) {			
				theWriter.writePixel(out, x, y, inC);
			}
			else
			// HMC_CR: Avoid naked "else" branches on newlines, particularly when asymetric with the "if" branch (ie, enclose with {}).
				theWriter.writePixel(out, x, y, background);
			// HMC_CR: Consider that these two branches differ only in the color that they're writing. Rather than branching on inTrue, maybe just initialize a notional "color_to_write" to background, then updating if testing discovers that it is within an ellipse. That would eliminate the conditional branch and simplify the code somewhat (ie, no inC, no inTrue).
		}
		theWriter.writeNewLine(out);
		// HMC_CR: This is fine, but is a little weird -- internally, this function simply appends a newline. This function is very honest, given what it says on the tin...but `theWriter` is providing very little value here: the calling code is effectively responsible for knowing a considerable amount PPM formatting to know how to call this code correctly. Said differently: if the caller has to be smart enough to help format the associated .ppm file, why doesn't it just `out << std::endl` itself?
	}
}


/*read command line arguments and write out new ascii file of given size */
int main(int argc, char *argv[]) {

	ofstream outFile;
	int sizeX, sizeY;

	// create all the equations for a simple asci face
	// note order in vector matters
	vector<shared_ptr<ellipse>> theEquations;
	// HMC_CR: Why shared_ptr, here? Who is this code sharing responsibility with, such that when theEquations fall-of-scope, we don't know if we can delete the relevant entries. Said differently: why not just std::vector<ellipse> ?
	theEquations.push_back(make_shared<ellipse>(116, 116, 80, 120, color(34, 98, 112)));
	theEquations.push_back(make_shared<ellipse>(52, 90, 20, 33,color(34, 198, 112)));
	theEquations.push_back(make_shared<ellipse>(168, 90, 20, 33,color(34, 198, 112)));
	theEquations.push_back(make_shared<ellipse>(116, 140, 50, 30,color(134, 98, 112)));
	// HMC_CR: If required, consider using "emplace_back" to construct objects concurrent with vector push_back.
	// HMC_CR: style: Consider instantiating the colors as distinct const objects with "human" friendly names, a la:
	// HMC_CR:   const color kBluish = color(34, 98, 112);
	// HMC_CR:   const color kGreenish = color(34, 198, 112);
	//
	// HMC_CR: It might be worth noting the space that these ellipses are created in. AFAICT, they are in a raster space with the origin in the upper left (ie, +y -> down?).


	if (argc < 4) {
		cerr << "Error format: a.out sizeX sizeY outfileName" << endl;
		// HMC_CR: Consider checking this before doing any work.
		// HMC_CR: syle: prefer simply returning / exiting here -- such that any following code doesn't need to be in an "else" block -- this tends to cut down on excessive and confusing indentation.
	} else {
		sizeX = stoi(argv[1]);
		sizeY = stoi(argv[2]);
		// HMC_CR: Declaration of sizeX and sizeY can probably be move down here, and declared const, ie:
		// HMC_CR:   const int sizeX = stoi(argv[1]);
		// HMC_CR:   const int sizeY = stoi(argv[2]);
		ppmR theWriter(sizeX, sizeY);
		outFile.open(argv[3]);
		// HMC_CR: Declare outFile at this scope (as well as ppmR, which is already local to this scope).
		if (outFile) {
			cout << "writing an image of size: " << sizeX << " " << sizeY << " to: " << argv[3] << endl;
			theWriter.writeHeader(outFile);
			writeOut(outFile, theWriter, theEquations);
		} else {
			// HMC_CR: Similar to the initial argc check, consider moving this earlier (ie, don't do any work until you know the output conditions are reasonably valid). This presents errors earlier, avoids wasted work, and tends to reduce indentation bloat.
			cout << "Error cannot open outfile" << endl;
			// HMC_CR: cout -> cerr (as the earlier argc check is).
			exit(0);
			// HMC_CR: This seems like it merits an error return.
		}
	}

	// HMC_CR: return 0; ?
}
