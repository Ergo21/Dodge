/*
	Axiom
	Physics.h
	Author: Joseph Watts
	Created on: 8 May 2014
	Based on code provided by aidan
*/

#ifndef PHYSICS_H
#define PHYSICS_H

#include <iostream>
#include <fstream>
#include <vector>

#include "GameAsset.h"
#include "Md2Asset.h"
#include "TriangularPyramidAsset.h"
#include "BallisticInterpolator.h"
#include "Camera.h"
#include "CuboidAsset.h"
#include "LevelLoader.h"
#include "Global.h"

#include "Data.h"

using namespace std;

 //! Physics Class
  /*!
    	A simple class that handles the updates of objects including collision.
  */
class Physics {
	public: 
	Physics(Data * d);

	//! Start Method
	/*
		Turns on world update
	*/
	void startGame();

	//! Update Method
	/*
		World update
	*/
	void updateData();

  	//! Collision Method
  	/*
  	  	Checks if the two objects are viable for collision e.g. both aren't static.
  	*/
  	bool getCol(shared_ptr<GameAsset> ob1, shared_ptr<GameAsset> ob2); 
  	//! Search Vector
  	/*
  	  	Searches vector for a given Force.
  	*/
  	bool seaVec(vector<Global::Force> v, Global::Force f);
  	//! Movement collision
  	/*
  	  	Checks if a movement in a particular direction will cause a collision.
  	*/
  	bool movCol(shared_ptr<GameAsset> ob1, char d, float m);

	private:
	bool gameGo;
	Data * phyData;
	time_t starTime;
};

#endif
