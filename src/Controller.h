/*
	Axiom
	Controller.h
	Author: Joseph Watts
	Created on: 8 May 2014
	Based on code provided by aidan
*/

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <fstream>
#include <vector>

#include <SDL2/SDL.h>

#include "GameAsset.h"
#include "Md2Asset.h"
#include "TriangularPyramidAsset.h"
#include "BallisticInterpolator.h"
#include "Camera.h"
#include "CuboidAsset.h"
#include "LevelLoader.h"
#include "Global.h"

#include "Data.h"
#include "Physics.h"

using namespace std;

 //! Controller Class
  /*!
    	A simple class that handles Mouse and Keyboard events.
  */
class Controller {
	public: 
	Controller(Data * d, Physics * p);
	void mMoveEvents(SDL_Event &event);
	void kDownEvents(SDL_Event &event);

	private:
	Data * conData;
	Physics * conPhy;
	Matrix3 tCam;
	Vector3 dCam;
	Vector3 locFor;
	Vector3 locRig;
	Vector3 locUp;
	float pi;
	float tAng;
	float tAngMem;

	void moveX(int d);
	void moveZ(int d);
};


#endif
