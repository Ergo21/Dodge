/*
	Axiom
	Data.h
	Author: Joseph Watts
	Created on: 8 May 2014
	Based on code provided by aidan
*/

#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>

#include "Camera.h"
#include "GameAsset.h"
#include "Global.h"
#include "LevelLoader.h"

using namespace std;

#define RUN_GRAPHICS_DISPLAY 0x00;

 //! Data Class
  /*!
    	A simple class holds data shared between classes.
  */
class Data {
	public:
	//! Data Constructor
	/*!
		Creates data used by multiple classes.
	*/
	Data();

	//! Get List
	/*!
		Returns a list depending on the char given, used to share data among classes
	*/
	vector<shared_ptr<GameAsset>>* getList(char c);

	//! Get Player
	/*!
		Returns player, used to share data among classes
	*/
	shared_ptr<GameAsset> getPlayer();

	private:
	vector<shared_ptr<GameAsset> > ballAssets; //All ball objects
  	vector<shared_ptr<GameAsset> > florAssets; //All floor objects
	vector<shared_ptr<GameAsset> > wallAssets; //All wall objects
  	shared_ptr<GameAsset> player; //Player asset, assumes 1 player

	//! Organise Assets
	/*!
		Splits asset list given by LevelLoader into, several lists of certain Assets.
	*/
	void organAssets(vector<shared_ptr<GameAsset>> tempAssets);
};


#endif
