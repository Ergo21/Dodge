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
#include <ctime>

#include "Global.h"
#include "Loop.h"

using namespace std;

#define RUN_GRAPHICS_DISPLAY 0x00;


  //! Setup Method
  /*!
    Creates SDL_Window, before calling gameLoop Method.
  */
  int main(int argc, char ** argv); 

#endif
