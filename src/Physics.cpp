/*
	Axiom
	Physics.cpp
	Author: Joseph Watts
	Created on: 8 May 2014
	Based on code provided by aidan
*/

#include "Physics.h"

Physics::Physics(Data *d) {
	
	phyData = d;
	gameGo = false;
}

void Physics::startGame() {
	if(!gameGo) {
		time(&starTime);
	}
	gameGo = true;
}

void Physics::updateData() {

  vector<shared_ptr<GameAsset>> * ballAssets = phyData->getList('B');
  vector<shared_ptr<GameAsset>> * wallAssets = phyData->getList('W');
  vector<shared_ptr<GameAsset>> * florAssets = phyData->getList('F');

  for(int i = 0; i < ballAssets->size(); i++) {
	shared_ptr<GameAsset> ballI = ballAssets->at(i);

	  if(gameGo) {
		if(movCol(ballI, 'X', ballI->getGAP()->getMovX())) {
			ballI->getGAP()->setMovX(-ballI->getGAP()->getMovX());
		}
		if(movCol(ballI, 'Y', ballI->getGAP()->getMovY())) {
			ballI->getGAP()->setMovY(-ballI->getGAP()->getMovY());
		}
		if(movCol(ballI, 'Z', ballI->getGAP()->getMovZ())) {
			ballI->getGAP()->setMovZ(-ballI->getGAP()->getMovZ());
		}

		ballI->update();
	  }

	for(int j = 0; j < wallAssets->size(); j++) {
	    shared_ptr<GameAsset> objJ = wallAssets->at(j);
	    if(getCol(ballI, objJ)) {
		//cout << "Between ball and wall" <<endl;
	    }
    	}

	for(int j = 0; j < florAssets->size(); j++) {
	    shared_ptr<GameAsset> objJ = florAssets->at(j);
	    if(getCol(ballI, objJ)) {
		//cout << "Collision between collisionables" <<endl;
	    }

	    if(getCol(phyData->getPlayer(), objJ)) {
		//cout << "Collision" << endl;
	    }
    	}
	  
	for(int j = 0; j < ballAssets->size(); j++) {
	    shared_ptr<GameAsset> objJ = ballAssets->at(j);
	    if((ballI != objJ) && getCol(ballI, objJ)) {
		//cout << "Collision between collisionables" <<endl;
	    }
    	}

	if(getCol(ballI, phyData->getPlayer())) {	
		time_t endTime;
		time(&endTime);
		cout << "You survived: " << difftime(endTime, starTime) << " seconds" << endl;
		cout << "And then you died!" <<endl;
		SDL_Event event;
		event.type = SDL_QUIT;
		SDL_PushEvent(&event);
	}
  }
}



bool Physics::getCol(shared_ptr<GameAsset> ob1, shared_ptr<GameAsset> ob2) {
	
	if(!ob1->collidesWith(*ob2)) {
		return false;
	}
	return true;
}

bool Physics::movCol(shared_ptr<GameAsset> ob1, char d, float m) {

	vector<shared_ptr<GameAsset>> * ballAssets = phyData->getList('B');
  	vector<shared_ptr<GameAsset>> * wallAssets = phyData->getList('W');
  	vector<shared_ptr<GameAsset>> * florAssets = phyData->getList('F');
	shared_ptr<GameAsset> it;
	if(d == 'X') {
		ob1->moveX(m);
		for(int i = 0; i < wallAssets->size(); i++) {
			it = wallAssets->at(i);
			if(getCol(ob1, it)) {
				ob1->moveX(-m);
				return true;
			}
		}
		for(int i = 0; i < ballAssets->size(); i++) {
			it = ballAssets->at(i);
			if(it != ob1 && getCol(ob1, it)) {
				ob1->moveX(-m);
				it->getGAP()->setMovX(-it->getGAP()->getMovX());
				return true;
			}
		}
		ob1->moveX(-m);
	} 
	else if(d == 'Y') {
		ob1->moveY(m);
		for(int i = 0; i < wallAssets->size(); i++) {
			it = wallAssets->at(i);
			if(getCol(ob1, it)) {
				ob1->moveY(-m);
				return true;
			}
		}
		for(int i = 0; i < ballAssets->size(); i++) {
			it = ballAssets->at(i);
			if(it != ob1 && getCol(ob1, it)) {
				ob1->moveY(-m);
				it->getGAP()->setMovY(-it->getGAP()->getMovY());
				return true;
			}
		}
		
		ob1->moveY(-m);
	}
	else if(d == 'Z') {
		ob1->moveZ(m);
		for(int i = 0; i < wallAssets->size(); i++) {
			it = wallAssets->at(i);
			if(getCol(ob1, it)) {
				ob1->moveZ(-m);
				return true;
			}
		}
		for(int i = 0; i < ballAssets->size(); i++) {
			it = ballAssets->at(i);
			if(it != ob1 && getCol(ob1, it)) {
				ob1->moveZ(-m);
				it->getGAP()->setMovZ(-it->getGAP()->getMovZ());
				return true;
			}
		}
		ob1->moveZ(-m);
	}
	return false;
}

bool Physics::seaVec(vector<Global::Force> v, Global::Force f) {
	if(v.empty()) {
		return false;
	}

	for(auto it : v) {
		if(it == f) {
			return true;
		}
	}
	return false;
}

