/*
	Axiom
	ModelTriangle.h
	Author: Joseph Watts
	Created on: 29 Apr 2014
	Based on code provided by aidan
*/
#ifndef MODELTRIANGLE_H_
#define MODELTRIANGLE_H_

#include <utility>
#include <memory>
#include <GL/glew.h>
#include <GL/gl.h>

#include "vectormath/scalar/cpp/vectormath_aos.h"

using namespace Vectormath::Aos;
using namespace std;
	
//! ModelTriangle class
/*!
  This class is a triangle made up of 3 3D points. Used for Polygon soup collision detection and model loading. Not currently used.  	
*/

class ModelTriangle {
 public:
  ModelTriangle(Point3 p1, Point3 p2, Point3 p3);
  Point3 getPoi1();
  Point3 getPoi2();
  Point3 getPoi3();
  Vector3 getNormal();
  Vector3 getU();
  Vector3 getV();

private:
  Point3 pointA, pointB, pointC;

};

#endif
