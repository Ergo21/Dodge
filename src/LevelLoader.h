/*
	Axiom
	LevelLoader.h
	Author: Joseph Watts
	Created on: 8 May 2014
	Based on code provided by aidan
*/

#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include <iostream>
#include <fstream>
#include <vector>

#include "GameAsset.h"
#include "CuboidAsset.h"
#include "GAPlus.h"

using namespace std;

 //! Level Class
  /*!
    	A simple class that reads a .txt file and produces creates a vector of GameAssets based on it.
  */
class LevelLoader
{
public:
	//! Get level method
  	/*!
  	  Sends an integer which acts as the level name, returning a vector of GameAsset.
  	*/
	vector<shared_ptr<GameAsset>> getLevel(int);		//Called by Level to load strings from txt files in relation to level topography and return
private:	
	vector<shared_ptr<GameAsset>> level0;	
	vector<string> level0Str;
	//! Build level method
  	/*!
  	  Creates the vector contents based on level .txt file. P = player (1 only), F = floor, W = wall, B = "ball"
  	*/
	void buildLevel();
		
};


#endif
