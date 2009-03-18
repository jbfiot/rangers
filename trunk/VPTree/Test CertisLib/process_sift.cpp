#include "process_sift.h"

#include <iostream>
#include <CL/Graphics/Graphics.h>
#include <CL/Images/Image.h>
#include <CL/Images/IO.h>

#include <CL/LinAlg/Vector.h>
#include <CL/LinAlg/Matrix.h>
#include <CL/LinAlg/SymMatrix.h>
//#include <CL/Common/IO.h>
//#include <CL/Common/Timer.h>
#include <CL/Common/SmallVector.h>

//SIFT
#include "CL/Feat/SIFT.h"
#include "CL/Feat/Graphics.h"
#include <time.h>


using namespace std;
using namespace CL::Graphics;
using namespace CL::Images;

using namespace CL::LinAlg;
using namespace CL::Common;
using namespace CL::Feat;


void process_sifts_in_image(string buffer_image, std::vector<Feature> &feats)
{
	static int index = 1;
	cout << "Processing SIFTs in image " << index << " (" << buffer_image << ")" << endl;

	Image<RGB<byte>,2> I1;
	load(I1, buffer_image);

	// Détecter les SIFTS pour l'image 1
	SIFTDetector D;
	D.setFirstOctave(1);
	D.setNumOfOct(4);
	D.setPeakThresh(1.);

	Array<SIFTDetector::Feature> feats1=D.run(I1);
	int size = feats1.size();
	cout << "On a détecté " << size << " points SIFT dans l'image de référence." << endl;
	feats.resize(size);
	
	for (int i=0; i<size; ++i)
	{
		SmallArray<double,128> descriptors_image = feats1[i].desc;
		feats[i].coeffs.resize(128);
		for (int j=0; j<128; ++j)
			feats[i].coeffs[j] = descriptors_image[j];
		feats[i].position.push_back( feats1[i].pos.x() );
		feats[i].position.push_back( feats1[i].pos.y() );
		feats[i].index_image = index;
	}

	index++;
}
