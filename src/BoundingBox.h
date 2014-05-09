/*
	Axiom
	BoundingBox.h
	Author: Joseph Watts
	Created on: 29 Apr 2014
	Based on code provided by aidan
*/

#ifndef BOUNDINGBOX_H_
#define BOUNDINGBOX_H_


#include <memory>
#include <utility>

#include "vectormath/scalar/cpp/vectormath_aos.h"

using namespace std;
using namespace Vectormath::Aos;

static Vector3 UNIT_X_AXIS(1.0, 0.0, 0.0);
static Vector3 UNIT_Y_AXIS(0.0, 1.0, 0.0);
static Vector3 UNIT_Z_AXIS(0.0, 0.0, 1.0);

enum AXIS {X, Y, Z};

  //! Bounding Box Class
  /*!
    	A simple box used in collision detection.
  */

class BoundingBox {
 public:
  BoundingBox(const Point3 & c, const float extent_x, const float extent_y, const float extent_z);
  //! Collision method
  /*!
   	Tests for a collision between this and the given BoundingBoxs
  */
  bool collidesWith(const BoundingBox & b);
  /*!
   	Part of collision method, used to compare values on 1 axis only.
  */
  pair<float,float> projectOntoAxis(const BoundingBox & b, enum AXIS);
  /*!
   	Gets the BoundingBox's centre.
  */
  shared_ptr<Point3> getCentre();

 private:
  Vector3 h_x, h_y, h_z;
  shared_ptr<Point3> c;
};

#endif
