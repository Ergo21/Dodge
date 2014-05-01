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
	for(auto it : assets) {
	  if(horrible_global_go) {it->update();}
	}
  
	for(auto i : assets) {
	  for(auto j : assets) {
	    if((i != j) && i->collidesWith(*j)) {

	    }
    	  }
  	}

  	for(auto it : assets) {
    	  it->draw();
  	}
	
  	// Don't forget to swap the buffers
  	SDL_GL_SwapWindow(window);
}

void physics() {

}

void gameLoop() {
	// Add the main event loop
	SDL_Event event;
	Matrix3 tCam;
	Vector3 dCam;

	Vector3 locFor = Vector3(0,0,1);
	Vector3 locRig = Vector3(1,0,0);
	Vector3 locUp  = Vector3(0,1,0);
	float tAng = 3.1415926/8;
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
			case SDL_KEYUP:
			  //			  Camera::getInstance().setCamera(Matrix4::identity());
			  break;
			case SDL_KEYDOWN:
			  Matrix4 camera = Camera::getInstance().getCameraM();
			  switch(event.key.keysym.sym){
			  case SDLK_ESCAPE: {
				/*if(SDL_GetRelativeMouseMode() == SDL_TRUE)
				{
					SDL_SetRelativeMouseMode(SDL_FALSE);
				}
				else
				{
					SDL_SetRelativeMouseMode(SDL_TRUE);
				}*/
				break;
			  }
			  case SDLK_w: {
				tCam = Camera::getInstance().getCameraM().getUpper3x3();
				
				dCam = (tCam*Vector3(0.0, 0.0, 1.0));

				Camera::getInstance().setCamera(camera * Matrix4::translation(locFor) );

				break;
			  }
			  case SDLK_s: {
				tCam = Camera::getInstance().getCameraM().getUpper3x3();
				
				dCam = tCam*Vector3(0.0, 0.0, -1.0);

				Camera::getInstance().setCamera(camera * Matrix4::translation(-locFor) );
				break;
			  }
			  case SDLK_a: {
				Camera::getInstance().setCamera(camera * Matrix4::translation(-locRig) );

				break;
			  }
			  case SDLK_d: {
				Camera::getInstance().setCamera(camera * Matrix4::translation(locRig) );

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
			  case SDLK_LEFT: {
				
			    Camera::getInstance().setCamera((camera * Matrix4::rotation(tAng, locUp)));
				tAngMem += tAng;

				if(tAngMem >= 2*3.1415926)
				{
					tAngMem -= 2*3.1415926;
				}
				else if(tAngMem <= -2*3.1415926)
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

				if(tAngMem >= 2*3.1415926)
				{
					tAngMem -= 2*3.1415926;
				}
				else if(tAngMem <= -2*3.1415926)
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
			  case SDLK_o: {
			    	Camera::getInstance().setCamera((camera * Matrix4::rotation(-3.1415926/8, locFor)));
			    	break;
			  }
			  case SDLK_p: {
			    	Camera::getInstance().setCamera((camera * Matrix4::rotation(3.1415926/8, locFor)));
			    	break;
			  }
			  case SDLK_g: {
			    	horrible_global_go = true;
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

	/*assets.push_back(shared_ptr<TriangularPyramidAsset> (new TriangularPyramidAsset(10, 0, 0)));

	assets.push_back(shared_ptr<CuboidAsset> (new CuboidAsset(-2, 0, 0, 1, 2, 1)));*/
	
	LevelLoader temLev;
	assets = temLev.getLevel(1);

	gameLoop();
	
	return 0;
}

