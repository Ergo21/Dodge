/*
	Axiom
	Loop.cpp
	Author: Joseph Watts
	Created on: 8 May 2014
	Based on code provided by aidan
*/

#include "Loop.h"

//! Timing Method
/*
	Method sent to SDL_AddTimer to push SDL_USEREVENT, which is then handled by the handling system.
*/
Uint32 display(Uint32 interval, void *param) {
	SDL_Event event;
	event.type = SDL_USEREVENT;
	event.user.code = RUN_GRAPHICS_DISPLAY;
	event.user.data1 = 0;
	event.user.data2 = 0;
	SDL_PushEvent(&event);
	return interval;
}

Loop::Loop(SDL_Window * tempWindow) {

	Uint32 delay = 1000/30; // in milliseconds

	// Call the function "display" every delay milliseconds
	SDL_AddTimer(delay, display, NULL);
	lopData = new Data();
	lopPhy = new Physics(lopData);
	lopControl = new Controller(lopData, lopPhy);
	lopView = new View(tempWindow, lopData);

}


void Loop::gameLoop() {
	// Add the main event loop
	SDL_Event event;

	while (SDL_WaitEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT: {
			  SDL_Quit();
			  break;
			}
			case SDL_USEREVENT: {
			 lopPhy->updateData();
			 lopView->display();
			  
			  break;
			}
			case SDL_MOUSEMOTION: {
			  if(SDL_GetRelativeMouseMode() == SDL_TRUE) {
				lopControl->mMoveEvents(event);
			  }

			}
			case SDL_KEYUP:
			  break;
			case SDL_KEYDOWN: {
				lopControl->kDownEvents(event);
			}
			  
		}

	}
}
