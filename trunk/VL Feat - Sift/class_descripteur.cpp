#include "class_descripteur.h"

// constructeur

rangers_descripteur::rangers_descripteur(){};

rangers_descripteur::rangers_descripteur(double _R_orientation, vl_sift_pix _R_descripteur[128], VlSiftKeypoint _R_keypoint)
{
	R_orientation=_R_orientation;
	for (int i=0;i<128;i++)
	{
		R_descripteur[i]=_R_descripteur[i];
	}
	R_keypoint=_R_keypoint;
}

//get orientation

double rangers_descripteur::rangers_getorientation()
{
	return R_orientation;
}

// get keypoints

VlSiftKeypoint rangers_descripteur::rangers_getkeypoint()
{
	return R_keypoint;
}

// get descripteur

vl_sift_pix * rangers_descripteur::rangers_getdescripteur()
{
	vl_sift_pix * temp = new vl_sift_pix;
	temp = &R_descripteur[0];
	return temp;
}




