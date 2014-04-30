/*
	Axiom
	Main.h
	Author: Joseph Watts
	Created on: 29 Apr 2014
	Based on code provided by aidan
*/
#ifndef MAIN_H_
#define MAIN_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

#include "GameAsset.h"
#include "Md2Asset.h"
#include "TriangularPyramidAsset.h"
#include "BallisticInterpolator.h"
#include "Camera.h"
#include "CuboidAsset.h"

using namespace std;

#define RUN_GRAPHICS_DISPLAY 0x00;


  //! Setup Method
  /*!
    Creates SDL_Window, before calling gameLoop Method
  */
  int main(int argc, char ** argv);

  bool horrible_global_go = false;
  vector<shared_ptr<GameAsset> > assets; //All world objects
  SDL_Window * window = nullptr;

  //! Timing Method
  /*
	Method sent to SDL_AddTimer to push SDL_USEREVENT, which is then handled by the handling system.
  */
  Uint32 display(Uint32 interval, void *param);
  //! Displaying Method
  /*
    	Draws everything on the SDL_Window by calling the GameAsset's draw & update method.
  */
  void display();
  //! Main loop Method
  /*
    	The games main loop that handles user input, calls physics & display methods
  */
  void gameLoop();
  //! The world update Method
  /*
    	The method that updates the world due to things such as gravity.
  */
  void physics();

#endif
