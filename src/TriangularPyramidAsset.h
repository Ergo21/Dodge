/*
	Axiom
	TriangularPyramidAsset.h
	Author: Joseph Watts
	Created on: 29 Apr 2014
	Based on code provided by aidan
*/

#include "GameAsset.h"
#include "IInterpolator.h"

#ifndef TRIANGULARPYRAMIDASSET_H_
#define TRIANGULARPYRAMIDASSET_H_

  //! TriangularPyramidAsset Class
  /*!
    	A class to a simple triangular pyramid.
  */
class TriangularPyramidAsset : public GameAsset {
 public:
  TriangularPyramidAsset();
  TriangularPyramidAsset(float x, float y, float z);
  ~TriangularPyramidAsset();

  //! Update Method
  /*!
    	Updates the asset.
  */
  virtual void update();
  //! Draw Method
  /*!
    	Draws this asset in a 3D context.
  */
  virtual void draw();
  void setInterpolator(shared_ptr<IInterpolator> li);
 private:
  shared_ptr<IInterpolator> li;
};

#endif // TRIANGULARPYRAMIDASSET_H_
