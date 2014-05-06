/*
	Axiom
	GAPlus.h
	Author: Joseph Watts
	Created on: 29 Apr 2014
*/
#include <vector>

#include "Global.h"

#ifndef GAPLUS_H_
#define GAPLUS_H_

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
	float getMovX();
	float getMovY();
	float getMovZ();
	void setMovX(float x);
	void setMovY(float y);
	void setMovZ(float z);
private:
	char thiType;
	vector<Global::Force> thiFor; //List of forces by number 0 = Collisionable, 1 = Gravity
	float movX;
	float movY;	
	float movZ;
};

#endif
