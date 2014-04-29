/*
	Axiom
	PolygonTest.h
	Author: Joseph Watts
	Created on: 29 Apr 2014
	Based on code provided by aidan
*/
#ifndef POLYGONTEST_H_
#define POLYGONTEST_H_

#include <utility>
#include <memory>
#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>
#include <iostream>

#include "vectormath/scalar/cpp/vectormath_aos.h"
#include "ModelTriangle.h"

using namespace Vectormath::Aos;
using namespace std;
 
  //! PolygonTest Class
  /*!
    This class is designed to use Polygon soup collision detection. Currently not working.
  */
class PolygonTest {
 public:
  	/*!
  	  This method goes through the list of ModelTriangle sent to it and compares it with all of the other list.
  	*/
	static bool getCollision(vector<ModelTriangle> tL1, vector<ModelTriangle> tL2);
 
private:
	/*!
  	  Part of the getCollision() method, checks for collision between 2 ModelTriangle 
  	*/
	static bool locColsDet(ModelTriangle tr1, ModelTriangle tr2);
};

#endif
