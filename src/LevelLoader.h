#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include <iostream>
#include <fstream>
#include <vector>

#include "GameAsset.h"
#include "CuboidAsset.h"

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
	//! Build level method
  	/*!
  	  Creates the vector contents.
  	*/
	void buildLevel();
	vector<shared_ptr<GameAsset>> level0;				//Holds topography strings until sent to Level
	vector<string> level0Str;
		
};


#endif
