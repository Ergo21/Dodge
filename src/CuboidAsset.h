/*
	Axiom
	CuboidAsset.h
	Author: Joseph Watts
	Created on: 29 Apr 2014
	Based on code provided by aidan
*/

#include "GameAsset.h"
//#include "IInterpolator.h"

#ifndef CUBOIDASSET_H
#define CUBOIDASSET_H

  //! CuboidAsset Class
  /*!
    This class is designed to draw cuboids.
  */
class CuboidAsset : public GameAsset {
 public:
  CuboidAsset();
  CuboidAsset(float x, float y, float z, float sX, float sY, float sZ);
  ~CuboidAsset();
  
  //! Update Method
  /*!
    	Updates the asset using the interpolator.
  */
  virtual void update();
  //! Draw Method
  /*!
    	Draws this asset in a 3D context.
  */
  virtual void draw();
  //void setInterpolator(shared_ptr<IInterpolator> li);
 private:
  //shared_ptr<IInterpolator> li;
};

#endif //  CUBOIDASSET_H
