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
  //! Constructor Method
  /*!
    	x, y, z = Coords, sX, sY, sZ = dimensions
  */
  CuboidAsset(float x, float y, float z, float sX, float sY, float sZ);
  //! Constructor Method with shaders
  /*!
    	Two extra parameters to customize shaders, vertex then fragment shader.
  */
  CuboidAsset(float x, float y, float z, float sX, float sY, float sZ, const string & v_shader, const string & f_shader);
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
	void buildObj(float x, float y, float z, float sX, float sY, float sZ);
};

#endif //  CUBOIDASSET_H
