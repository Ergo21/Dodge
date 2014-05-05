/*
	Axiom
	GAPlus.cpp
	Author: Joseph Watts
	Created on: 29 Apr 2014
*/

#include "GAPlus.h"

GAPlus::GAPlus(char t, vector<Global::Force> f)
{
	thiType = t;
	thiFor = f;
}

GAPlus::~GAPlus()
{
}

char GAPlus::getTy()
{
	return thiType;
}

vector<Global::Force> GAPlus::getFor()
{
	return thiFor;
}

