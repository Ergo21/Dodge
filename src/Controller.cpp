/*
	Axiom
	Controller.cpp
	Author: Joseph Watts
	Created on: 8 May 2014
	Based on code provided by aidan
*/

#include "Controller.h"

Controller::Controller(Data * d, Physics * p) {
	conData = d;
	conPhy = p;
	locFor = Vector3(0,0,1);
	locRig = Vector3(1,0,0);
	locUp  = Vector3(0,1,0);
	pi = 3.1415926;
	tAng = pi/256;
	tAngMem = 0;
}

void Controller::mMoveEvents(SDL_Event &event) {		//Mouse Motion

	Matrix4 camera = Camera::getInstance().getCameraM();			

	if(event.motion.xrel*event.motion.xrel > event.motion.yrel*event.motion.yrel) {
		if(event.motion.xrel < -5) {
			Camera::getInstance().setCamera((camera * Matrix4::rotation(-tAng*((int)event.motion.xrel/10), locUp)));
			tAngMem -= tAng*((int)event.motion.xrel/10);
		}
		else if(event.motion.xrel > 5) {
			Camera::getInstance().setCamera((camera * Matrix4::rotation(-tAng*((int)event.motion.xrel/10), locUp)));
			tAngMem -= tAng*((int)event.motion.xrel/10);
		}
	}
	else {

		if(event.motion.yrel > 5)	//Y camera movement, Bugs when used for too long
		{
			Camera::getInstance().setCamera((camera * Matrix4::rotation(-tAng*((int)event.motion.yrel/10), locRig)));
		}
		else if(event.motion.yrel < -5) {				
			Camera::getInstance().setCamera((camera * Matrix4::rotation(-tAng*((int)event.motion.yrel/10), locRig)));
		}

	}
				
	if(tAngMem >= 3.1415926) {
		tAngMem -= 2*3.1415926;
	}
	else if(tAngMem <= -3.1415926) {
		tAngMem += 2*3.1415926;
	}
			
	locRig = Vector3( cos(tAngMem), locRig.getY(), sin(tAngMem));
	locFor = Vector3( sin(tAngMem), locFor.getY(), cos(tAngMem));

}



void Controller::kDownEvents(SDL_Event &event) {		//Key down
	Matrix4 camera = Camera::getInstance().getCameraM();
	
	switch(event.key.keysym.sym) {
		case SDLK_ESCAPE: {
			if(SDL_GetRelativeMouseMode() == SDL_TRUE) {
				SDL_SetRelativeMouseMode(SDL_FALSE);
			}
			else {
				SDL_SetRelativeMouseMode(SDL_TRUE);
			}
			break;
		}
		//All movement is relative to players view
		case SDLK_w: {	
			moveZ(1);	
			break;
		}
		case SDLK_s: {
			moveZ(-1);
			break;
		}
		case SDLK_a: {
			moveX(-1);
			break;
		}
		case SDLK_d: {
			moveX(1);
			break;
		}
		case SDLK_g: {
			conPhy->startGame();
			    	break;
			}
		//Rotate Camera
		case SDLK_LEFT: {		
			Camera::getInstance().setCamera((camera * Matrix4::rotation(tAng, locUp)));
			tAngMem += tAng;

			if(tAngMem >= 3.1415926) {
				tAngMem -= 2*3.1415926;
			}
			else if(tAngMem <= -3.1415926) {
				tAngMem += 2*3.1415926;
			}

			locRig = Vector3( cos(tAngMem), locRig.getY(), sin(tAngMem));
			locFor = Vector3( sin(tAngMem), locFor.getY(), cos(tAngMem));

			break;
		}
		case SDLK_RIGHT: {
			Camera::getInstance().setCamera(camera * Matrix4::rotation(-tAng, locUp) );
			tAngMem -= tAng;

			if(tAngMem >= 3.1415926) {
				tAngMem -= 2*3.1415926;
			}
			else if(tAngMem <= -3.1415926) {
				tAngMem += 2*3.1415926;
			}

			locRig = Vector3( cos(tAngMem), locRig.getY(), sin(tAngMem));
			locFor = Vector3( sin(tAngMem), locFor.getY(), cos(tAngMem));

			break;
		}
		case SDLK_UP: {
		    	Camera::getInstance().setCamera((camera * Matrix4::rotation(3.1415926/8, locRig)));
		    	break;
		}
		case SDLK_DOWN: {
		    	Camera::getInstance().setCamera((camera * Matrix4::rotation(-3.1415926/8, locRig)));
		    	break;
		}
		default:
		    	break;
	}

}

void Controller::moveX(int d) {
	float x = 1; //1 is right
	float z = 0; //1 is Forward, angle left is positive going to pi before flipping to -pi

	if(tAngMem >= 0 && tAngMem <= pi/2) {
		x = 1-tAngMem/(pi/2);
		z = 1 - x;
	}
	else if(tAngMem > pi/2 && tAngMem <= pi) {
		x = -(tAngMem-(pi/2))/(pi/2); //Neg 0 -1
		z = 1+x; //Pos 1 0
	}
	else if(tAngMem > -pi && tAngMem <= -pi/2) {
		x = (tAngMem + (pi/2))/(pi/2); //Neg 0 -1
		z = -1-x; //Neg -1 0
	}
	else {
		x = 1+tAngMem/(pi/2); //Pos 1 0
		z = x-1; //Neg 0 -1
	}
	
	Vector4 thTemCam = Camera::getInstance().getCameraM().getCol3();

	x = x*d;
	z = z*d;

	if(conPhy->movCol(conData->getPlayer(), 'X', x)) {
		x = 0;
	}
	else {
		conData->getPlayer()->moveX(x);
	}
			
	if(conPhy->movCol(conData->getPlayer(), 'Z', z)) {
		z = 0;
	}
	else {
		conData->getPlayer()->moveZ(z);
	}

	thTemCam.setX(thTemCam.getX()+x);
	thTemCam.setZ(thTemCam.getZ()+z);
	Camera::getInstance().getCameraM().setCol3(thTemCam);
}

void Controller::moveZ(int d) {
	float x = 0;
	float z = 1;

	if(tAngMem >= 0 && tAngMem <= pi/2) {
		x = -tAngMem/(pi/2);
		z = x + 1;
	}
	else if(tAngMem > pi/2 && tAngMem <= pi) {
		x = (tAngMem-(pi/2))/(pi/2) - 1;
		z = -1-x;
	}
	else if(tAngMem > -pi && tAngMem <= -pi/2) {
		x = 1 + (tAngMem + (pi/2))/(pi/2); 
		z = x - 1; 
	}
	else {
		x = -tAngMem/(pi/2);
		z = 1 -x;
	}

	Vector4 thTemCam = Camera::getInstance().getCameraM().getCol3();

	x = x*d;
	z = z*d;

	if(conPhy->movCol(conData->getPlayer(), 'X', x)) {
		x = 0;
	}
	else {
		conData->getPlayer()->moveX(x);
	}
				
	if(conPhy->movCol(conData->getPlayer(), 'Z', z)) {
		z = 0;
	}
	else {
		conData->getPlayer()->moveZ(z);
	}

	thTemCam.setX(thTemCam.getX()+x);
	thTemCam.setZ(thTemCam.getZ()+z);
	Camera::getInstance().getCameraM().setCol3(thTemCam);
}


