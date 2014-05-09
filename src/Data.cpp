/*
	Axiom
	Data.cpp
	Author: Joseph Watts
	Created on: 8 May 2014
	Based on code provided by aidan
*/

#include "Data.h"

Data::Data() {
	LevelLoader temLev;
	vector<shared_ptr<GameAsset>> tAssets = temLev.getLevel(1);

	organAssets(tAssets);
}

void Data::organAssets(vector<shared_ptr<GameAsset>> tempAssets) {
	for(auto in : tempAssets) {
		switch(in->getGAP()->getTy()) {
			case 'W': {
				wallAssets.push_back(in);
				break;
			}
			case 'F': {
				florAssets.push_back(in);
				break;
			}
			case 'B': {
				ballAssets.push_back(in);
				break;
			}
			case 'P': {
				player = in;
				break;
			}			
		}
	}

}

vector<shared_ptr<GameAsset>>* Data::getList(char c) {
	switch(c) {
		case 'B': {
			return &ballAssets;
		}
		case 'F': {
			return &florAssets;
		}
		case 'W': {
			return &wallAssets;
		}
		default: {
			return NULL;
		}
	}

}

shared_ptr<GameAsset> Data::getPlayer() {
	return player;
}
