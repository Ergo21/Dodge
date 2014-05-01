#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include <iostream>
#include <fstream>
#include <vector>

#include "GameAsset.h"
#include "CuboidAsset.h"

using namespace std;

class LevelLoader
{
public:
	vector<shared_ptr<GameAsset>> getLevel(int);		//Called by Level to load strings from txt files in relation to level topography and return
private:
	vector<shared_ptr<GameAsset>> level0;				//Holds topography strings until sent to Level
	vector<string> level0Str;
	void buildLevel();	
};


#endif
