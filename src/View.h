/*
	Axiom
	View.h
	Author: Joseph Watts
	Created on: 8 May 2014
	Based on code provided by aidan
*/

#ifndef VIEW_H
#define VIEW_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>

#include <iostream>
#include <fstream>
#include <vector>

#include "Data.h"
#include "GameAsset.h"
#include "Global.h"

using namespace std;

#define RUN_GRAPHICS_DISPLAY 0x00;

 //! View Class
  /*!
    	A simple class that handles drawing objects and interface on screen.
  */
class View {
	public: 
	View(SDL_Window * tempWindow, Data * d);

	//! Displaying Method
  	/*
  	  	Draws everything on the SDL_Window by calling the GameAsset's draw method.
  	*/
  	void display();
  	
	private:
	Data *viewData;
	SDL_Window * window;
};

#endif




