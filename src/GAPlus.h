/*
	Axiom
	GAPlus.h
	Author: Joseph Watts
	Created on: 29 Apr 2014
*/
#ifndef GAPLUS_H_
#define GAPLUS_H_

#include <vector>

#include "Global.h"

using namespace std;
  //! GAPlus Class
  /*!
    Holds more information on a GameAsset.
  */

class GAPlus{
public:
	//! GAPlus Constructor
  	/*!
    		Requires a char, which represents what the GameAsset is, and a list of forces this Asset is subject to.
  	*/
	GAPlus(char t, vector<Global::Force> f);
	~GAPlus();
	//! Get type method
  	/*!
    		Type = char
  	*/
	char getTy();
	//! Get list of forces method
  	/*!
    		List of forces this Asset is subject to.
  	*/
	vector<Global::Force> getFor();
	//! Get movement value along X axis
	float getMovX();
	//! Get movement value along Y axis
	float getMovY();
	//! Get movement value along Z axis
	float getMovZ();
	//! Set movement value along X axis
	void setMovX(float x);
	//! Set movement value along Y axis
	void setMovY(float y);
	//! Set movement value along Z axis
	void setMovZ(float z);
private:
	char thiType;
	vector<Global::Force> thiFor; //List of forces
	float movX;
	float movY;	
	float movZ;
};

#endif
