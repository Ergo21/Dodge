/*
	Axiom
	View.cpp
	Author: Joseph Watts
	Created on: 8 May 2014
	Based on code provided by aidan
*/

#include "View.h"

View::View(SDL_Window * tempWindow, Data * d) {
	
	window = tempWindow;
	viewData = d;
}

void View::display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
  
	vector<shared_ptr<GameAsset>> * temAssets = viewData->getList('W');	

  	for(int i = 0; i < temAssets->size(); i++) {
		temAssets->at(i)->draw();
  	}

	//delete temAssets;

	temAssets = viewData->getList('F');

	for(int i = 0; i < temAssets->size(); i++) {
		temAssets->at(i)->draw();
  	}

	//delete temAssets;
	
	temAssets = viewData->getList('B');
	
	for(int i = 0; i < temAssets->size(); i++) {
		temAssets->at(i)->draw();
  	}

	//delete temAssets;
	
  	// Don't forget to swap the buffers
  	SDL_GL_SwapWindow(window);
}
