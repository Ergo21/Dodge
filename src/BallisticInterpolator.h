/*
	Axiom
	BallisticInterpolator.h
	Author: Joseph Watts
	Created on: 29 Apr 2014
	Based on code provided by aidan
*/

#include <vectormath/scalar/cpp/vectormath_aos.h>

#include "IInterpolator.h"

using namespace Vectormath::Aos;

#ifndef BALLISTICINTERPOLATOR_H_
#define BALLISTICINTERPOLATOR_H_

class BallisticInterpolator : public IInterpolator {
 public:
  BallisticInterpolator(Vector3 launch, int fps);
  Vector3 update();
 private:
  int fps, count;
  Vector3 * launch, * G;
};

#endif
