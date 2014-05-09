/*
	Axiom
	Loop.h
	Author: Joseph Watts
	Created on: 8 May 2014
	Based on code provided by aidan
*/

#ifndef LOOP_H
#define LOOP_H

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <ctime>
#include <GL/glew.h>
#include <GL/gl.h>
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

#include "Controller.h"
#include "Physics.h"
#include "View.h"

using namespace std;

#define RUN_GRAPHICS_DISPLAY 0x00;

 //! Loop Class
  /*!
    	A simple class that loops the game world calling other classes etc.
  */
class Loop {
	public:
	//! Loop Constructor
	/*!
		Initialises world to be looped
	*/
	Loop(SDL_Window * tempWindow);


	//! Main loop Method
  	/*
  	  	The games main loop that handles user input, calls physics & display methods
  	*/
  	void gameLoop();

	private:
	
	Data *lopData;
	Controller *lopControl;
	Physics *lopPhy;
	View *lopView;

};


#endif
