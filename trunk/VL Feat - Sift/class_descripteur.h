
extern "C"
{
#include "sift.h"
}

#pragma once
#ifndef _CLASS_DESCRIPTEUR
#define _CLASS_DESCRIPTEUR


#include <vector>
using namespace std;

class rangers_descripteur 
{
public:
	//constructeur par default
	rangers_descripteur();
	//Destructeur
	~rangers_descripteur(){};
	//constructeur
	rangers_descripteur(double _R_orientation,vl_sift_pix  _R_descripteur[128],VlSiftKeypoint _R_keypoint);
	// Get orientation
	double rangers_getorientation();
	//Get Keypoints;
	VlSiftKeypoint rangers_getkeypoint();
	//Get descripteur
	vl_sift_pix * rangers_getdescripteur();


private:
	double R_orientation;
	vl_sift_pix R_descripteur[128];
	VlSiftKeypoint R_keypoint;
};


typedef vector<rangers_descripteur> tableau_descripteur;

#endif