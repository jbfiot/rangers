#include "CImg.h"
#include "timer.h"
 using namespace cimg_library;

template <class T> 
 void test ( CImg <T> &img)
 {
	int height = img.height;
	int width = img.width;
	int channel = img.depth;
	CImg <T> img_copy (img);
	CImg <T> ::iterator it;
	it=img_copy.begin();
	CImgDisplay disp(img_copy,"test");
	timer t;
	while (!disp.is_closed) 
	{
		while (it!=img_copy.end())	
		{
			img_copy[it]=0;
			disp.display(img_copy);
			t.restart();
			while (t.elapsed_time()<=0.0000000000000000001){}
			it++;
		}
		
	}
 }
