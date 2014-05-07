/*
	Axiom
	Main.cpp
	Author: Joseph Watts
	Created on: 29 Apr 2014
	Based on code provided by aidan
*/

#include "Main.h"

/*
 * SDL timers run in separate threads.  In the timer thread
 * push an event onto the event queue.  This event signifies
 * to call display() from the thread in which the OpenGL 
 * context was created.
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

void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
  
	// This O(n + n^2 + n) sequence of loops is written for clarity,
	// not efficiency
  
	for(auto i : ballAssets) {
	  if(horrible_global_go) {
		if(movCol(i, 'X', i->getGAP()->getMovX())) {
			i->getGAP()->setMovX(-i->getGAP()->getMovX());
		}
		if(movCol(i, 'Y', i->getGAP()->getMovY())) {
			i->getGAP()->setMovY(-i->getGAP()->getMovY());
		}
		if(movCol(i, 'Z', i->getGAP()->getMovZ())) {
			i->getGAP()->setMovZ(-i->getGAP()->getMovZ());
		}

		i->update();
	  }

	  for(auto j : wallAssets) {
	    if(getCol(i, j)) {
		//cout << "Between ball and wall" <<endl;
	    }
    	  }

	  for(auto j : florAssets) {
	    if(getCol(i, j)) {
		//cout << "Collision between collisionables" <<endl;
	    }

	    if(getCol(player, j)) {
		//cout << "Collision" << endl;
	    }
    	  }
	  
	  for(auto j : ballAssets) {
	    if((i != j) && getCol(i, j)) {
		//cout << "Collision between collisionables" <<endl;
	    }
    	  }

	  if(getCol(i, player)) {	
		time_t endTime;
		time(&endTime);
		cout << "You survived: " << difftime(endTime, starTime) << " seconds" << endl;
		cout << "And then you died!" <<endl;
		SDL_Event event;
		event.type = SDL_QUIT;
		SDL_PushEvent(&event);
	  }
  	}

  	for(auto it : wallAssets) {
		it->draw();
  	}

	for(auto it : florAssets) {
		it->draw();
  	}
	
	for(auto it : ballAssets) {
		it->draw();
  	}

	
	
  	// Don't forget to swap the buffers
  	SDL_GL_SwapWindow(window);
}

bool getCol(shared_ptr<GameAsset> ob1, shared_ptr<GameAsset> ob2) {
	
	if(!ob1->collidesWith(*ob2)) {
		return false;
	}
	return true;
}

bool movCol(shared_ptr<GameAsset> ob1, char d, float m) {
	if(d == 'X') {
		ob1->moveX(m);
		for(auto it : wallAssets) {
			if(getCol(ob1, it)) {
				ob1->moveX(-m);
				return true;
			}
		}
		for(auto it : ballAssets) {
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
		for(auto it : wallAssets) {
			if(getCol(ob1, it)) {
				ob1->moveY(-m);
				return true;
			}
		}
		for(auto it : ballAssets) {
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
		for(auto it : wallAssets) {
			if(getCol(ob1, it)) {
				ob1->moveZ(-m);
				return true;
			}
		}
		for(auto it : ballAssets) {
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

bool seaVec(vector<Global::Force> v, Global::Force f) {
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

void gameLoop() {
	// Add the main event loop
	SDL_Event event;
	Matrix3 tCam;
	Vector3 dCam;

	Vector3 locFor = Vector3(0,0,1);
	Vector3 locRig = Vector3(1,0,0);
	Vector3 locUp  = Vector3(0,1,0);
	float pi = 3.1415926;
	float tAng = pi/256;
	float tAngMem = 0;

	while (SDL_WaitEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT: {
			  SDL_Quit();
			  break;
			}
			case SDL_USEREVENT: {
			  display();
			  break;
			}
			case SDL_MOUSEMOTION: {
			  if(SDL_GetRelativeMouseMode() == SDL_TRUE)
			  {
				Matrix4 camera = Camera::getInstance().getCameraM();			

				if(event.motion.xrel < -5)
				{
					Camera::getInstance().setCamera((camera * Matrix4::rotation(tAng, locUp)));
					tAngMem += tAng;
				}
				else if(event.motion.xrel > 5)
				{
					Camera::getInstance().setCamera((camera * Matrix4::rotation(-tAng, locUp)));
					tAngMem -= tAng;
				}

				//if(event.motion.yrel > 5)	//Bugs when used for too long
				//{
				//	Camera::getInstance().setCamera((camera * Matrix4::rotation(-tAng, locRig)));
				//}
				//else if(event.motion.yrel < -5)
				//{				
				//	Camera::getInstance().setCamera((camera * Matrix4::rotation(tAng, locRig)));
				//}
				
				if(tAngMem >= 3.1415926)
				{
					tAngMem -= 2*3.1415926;
				}
				else if(tAngMem <= -3.1415926)
				{
					tAngMem += 2*3.1415926;
				}
				
				locRig = Vector3( cos(tAngMem), locRig.getY(), sin(tAngMem));
				locFor = Vector3( sin(tAngMem), locFor.getY(), cos(tAngMem));
				//cout << "locRig X: " << cos(tAngMem) << ", Y: " << locRig.getY() << ", Z: " << sin(tAngMem) << endl;
				//cout << "locFor X: " << sin(tAngMem) << ", Y: " << locFor.getY() << ", Z: " << cos(tAngMem) << endl;

			   }

			}
			case SDL_KEYUP:
			  //			  Camera::getInstance().setCamera(Matrix4::identity());
			  break;
			case SDL_KEYDOWN:
			  Matrix4 camera = Camera::getInstance().getCameraM();
			  switch(event.key.keysym.sym){
			  case SDLK_ESCAPE: {
				if(SDL_GetRelativeMouseMode() == SDL_TRUE)
				{
					SDL_SetRelativeMouseMode(SDL_FALSE);
				}
				else
				{
					SDL_SetRelativeMouseMode(SDL_TRUE);
				}
				break;
			  }
			  case SDLK_w: {
				float x = 0;
				float z = 1;

				if(tAngMem >= 0 && tAngMem <= pi/2)
				{
					x = -tAngMem/(pi/2);
					z = x + 1;
				}
				else if(tAngMem > pi/2 && tAngMem <= pi)
				{
					x = (tAngMem-(pi/2))/(pi/2) - 1;
					z = -1-x;
				}
				else if(tAngMem > -pi && tAngMem <= -pi/2)
				{
					x = 1 + (tAngMem + (pi/2))/(pi/2); 
					z = x - 1; 
				}
				else
				{
					x = -tAngMem/(pi/2);
					z = 1 -x;
				}
				Vector4 thTemCam = Camera::getInstance().getCameraM().getCol3();
				if(movCol(player, 'X', x)) {
					x = 0;
				}
				else {
					player->moveX(x);
				}
				
				if(movCol(player, 'Z', z)) {
					z = 0;
				}
				else {
					player->moveZ(z);
				}
				thTemCam.setX(thTemCam.getX()+x);
				thTemCam.setZ(thTemCam.getZ()+z);
				Camera::getInstance().getCameraM().setCol3(thTemCam);
				break;
			  }
			  case SDLK_s: {
				float x = 0;
				float z = -1;

				if(tAngMem >= 0 && tAngMem <= pi/2)
				{
					x = -tAngMem/(pi/2);
					z = x + 1;
				}
				else if(tAngMem > pi/2 && tAngMem <= pi)
				{
					x = (tAngMem-(pi/2))/(pi/2) - 1;
					z = -1-x;
				}
				else if(tAngMem > -pi && tAngMem <= -pi/2)
				{
					x = 1 + (tAngMem + (pi/2))/(pi/2);
					z = x - 1; 
				}
				else
				{
					x = -tAngMem/(pi/2);
					z = 1 -x;
				}
				Vector4 thTemCam = Camera::getInstance().getCameraM().getCol3();

				if(movCol(player, 'X', -x)) {
					x = 0;
				}
				else {
					player->moveX(-x);
				}
				
				if(movCol(player, 'Z', -z)) {
					z = 0;
				}
				else {
					player->moveZ(-z);
				}

				thTemCam.setX(thTemCam.getX()-x);
				thTemCam.setZ(thTemCam.getZ()-z);
				Camera::getInstance().getCameraM().setCol3(thTemCam);
				break;
			  }
			  case SDLK_a: {
				float x = 1; //1 is right
				float z = 0; //1 is Forward, angle left is positive going to pi before flipping to -pi

				if(tAngMem >= 0 && tAngMem <= pi/2)
				{
					x = 1-tAngMem/(pi/2);
					z = 1 - x;
				}
				else if(tAngMem > pi/2 && tAngMem <= pi)
				{
					x = -(tAngMem-(pi/2))/(pi/2); //Neg 0 -1
					z = 1+x; //Pos 1 0
				}
				else if(tAngMem > -pi && tAngMem <= -pi/2)
				{
					x = (tAngMem + (pi/2))/(pi/2); //Neg 0 -1
					z = -1-x; //Neg -1 0
					//x = -(tAngMem+pi)/(pi/2);
					//z = -1-x;
				}
				else
				{
					x = 1+tAngMem/(pi/2); //Pos 1 0
					z = x-1; //Neg 0 -1
				}
				Vector4 thTemCam = Camera::getInstance().getCameraM().getCol3();

				if(movCol(player, 'X', -x)) {
					x = 0;
				}
				else {
					player->moveX(-x);
				}
				
				if(movCol(player, 'Z', -z)) {
					z = 0;
				}
				else {
					player->moveZ(-z);
				}
			
				thTemCam.setX(thTemCam.getX()-x);
				thTemCam.setZ(thTemCam.getZ()-z);
				Camera::getInstance().getCameraM().setCol3(thTemCam);
				break;
			  }
			  case SDLK_d: {
				float x = 1; //1 is right
				float z = 0; //1 is Forward, angle left is positive going to pi before flipping to -pi

				if(tAngMem >= 0 && tAngMem <= pi/2)
				{
					x = 1-tAngMem/(pi/2);
					z = 1 - x;
				}
				else if(tAngMem > pi/2 && tAngMem <= pi)
				{
					x = -(tAngMem-(pi/2))/(pi/2); //Neg 0 -1
					z = 1+x; //Pos 1 0
				}
				else if(tAngMem > -pi && tAngMem <= -pi/2)
				{
					x = (tAngMem + (pi/2))/(pi/2); //Neg 0 -1
					z = -1-x; //Neg -1 0
					//x = -(tAngMem+pi)/(pi/2);
					//z = -1-x;
				}
				else
				{
					x = 1+tAngMem/(pi/2); //Pos 1 0
					z = x-1; //Neg 0 -1
				}
				Vector4 thTemCam = Camera::getInstance().getCameraM().getCol3();

				if(movCol(player, 'X', x)) {
					x = 0;
				}
				else {
					player->moveX(x);
				}
				
				if(movCol(player, 'Z', z)) {
					z = 0;
				}
				else {
					player->moveZ(z);
				}

				thTemCam.setX(thTemCam.getX()+x);
				thTemCam.setZ(thTemCam.getZ()+z);
				Camera::getInstance().getCameraM().setCol3(thTemCam);
				break;
			  }
			  case SDLK_f: {
				for(int i = 0; i < 16; i+=4)
				{
					float tCam1 = Camera::getInstance().getCamera()[i];
					float tCam2 = Camera::getInstance().getCamera()[i+1];
					float tCam3 = Camera::getInstance().getCamera()[i+2];
					float tCam4 = Camera::getInstance().getCamera()[i+3];
					cout << "Line: " << tCam1 << " " << tCam2 << " " << tCam3 << " " << tCam4 << endl;
				}
			cout << "" <<endl;
				  cout << locUp.getX() <<endl;
				cout << locUp.getY() <<endl;
				cout << locUp.getZ() <<endl;
				
				cout<< " "<<endl;
				break;
			  }
			  case SDLK_o: {
			    	Camera::getInstance().setCamera((camera * Matrix4::rotation(-3.1415926/8, locFor)));
			    	break;
			  }
			  case SDLK_p: {
			    	Camera::getInstance().setCamera((camera * Matrix4::rotation(3.1415926/8, locFor)));
			    	break;
			  }
			  case SDLK_g: {
				if(!horrible_global_go) { time(&starTime);};
			    	horrible_global_go = true;
			    	break;
			  }
			   case SDLK_LEFT: {
				
			    Camera::getInstance().setCamera((camera * Matrix4::rotation(tAng, locUp)));
				tAngMem += tAng;

				if(tAngMem >= 3.1415926)
				{
					tAngMem -= 2*3.1415926;
				}
				else if(tAngMem <= -3.1415926)
				{
					tAngMem += 2*3.1415926;
				}

				locRig = Vector3( cos(tAngMem), locRig.getY(), sin(tAngMem));
				locFor = Vector3( sin(tAngMem), locFor.getY(), cos(tAngMem));

			    break;
			  }
			  case SDLK_RIGHT: {
			    Camera::getInstance().setCamera(camera * Matrix4::rotation(-tAng, locUp) );
				tAngMem -= tAng;

				if(tAngMem >= 3.1415926)
				{
					tAngMem -= 2*3.1415926;
				}
				else if(tAngMem <= -3.1415926)
				{
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
			  break;
			}

	}
}

int main(int argc, char ** argv)
{
	Uint32 width = 640;
	Uint32 height = 480;
	Uint32 delay = 1000/30; // in milliseconds

	// Initialise SDL - when using C/C++ it's common to have to
	// initialise libraries by calling a function within them.
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER)<0) {
			cout << "Failed to initialise SDL: " << SDL_GetError() << endl;
			SDL_Quit();
	}

	// When we close a window quit the SDL application
	atexit(SDL_Quit);

	// Create a new window with an OpenGL surface
	window = SDL_CreateWindow("Axiom", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 
								SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
	if (nullptr == window) {
			cout << "Failed to create SDL window: " << SDL_GetError() << endl;
			SDL_Quit();
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (nullptr == glContext){
		cout << "Failed to create OpenGL context: " << SDL_GetError() << endl;
		SDL_Quit();
	}

	// Initialise GLEW - an easy way to ensure OpenGl 2.0+
	// The *must* be done after we have set the video mode - otherwise we have no OpenGL context.
	glewInit();
	if (!glewIsSupported("GL_VERSION_2_0")) {
	  cerr<< "OpenGL 2.0 not available" << endl;
	  return 1;
	}
	
	// Call the function "display" every delay milliseconds
	SDL_AddTimer(delay, display, NULL);
	//SDL_SetRelativeMouseMode(SDL_TRUE);

	/*assets.push_back(shared_ptr<TriangularPyramidAsset> (new TriangularPyramidAsset(10, 0, 0)));

	assets.push_back(shared_ptr<CuboidAsset> (new CuboidAsset(-2, 0, 0, 1, 2, 1)));*/
	
	LevelLoader temLev;
	vector<shared_ptr<GameAsset>> assets = temLev.getLevel(1);
	
	for(auto in : assets) {
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

	gameLoop();
	
	return 0;
}

