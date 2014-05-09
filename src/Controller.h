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

#include "Camera.h"
#include "Data.h"
#include "Global.h"
#include "Physics.h"

using namespace std;

 //! Controller Class
  /*!
    	A simple class that handles Mouse and Keyboard events.
  */
class Controller {
	public: 
	//! Constructor
	/*!
		Requires Data to change the world, and Physics to test for player movement collision.
	*/
	Controller(Data * d, Physics * p);
	//! Move Mouse Event Handler
	/*!
		Currently only handles mouse x movement (mouse y movement is in code but buggy), rotates the camera.
	*/
	void mMoveEvents(SDL_Event &event);
	//! Key Down Event Handler
	/*!
		WASD- Move player/camera, g- Start game
	*/
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
	 
	/*!
		Move player to their relative Left/Right, depending on value of d(-1, 1)
	*/
	void moveX(int d);
	/*!
		Move player to their relative Forward/Back, depending on value of d(1, -1)
	*/	
	void moveZ(int d);
};


#endif
