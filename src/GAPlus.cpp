/*
	Axiom
	GAPlus.cpp
	Author: Joseph Watts
	Created on: 29 Apr 2014
*/

#include "GAPlus.h"

GAPlus::GAPlus(char t, vector<Global::Force> f) {
	thiType = t;
	thiFor = f;
	movX = 0;
	movY = 0;
	movZ = 0;
}

GAPlus::~GAPlus() {
}

char GAPlus::getTy() {
	return thiType;
}

vector<Global::Force> GAPlus::getFor() {
	return thiFor;
}

float GAPlus::getMovX() {
	return movX;
}

float GAPlus::getMovY() {
	return movY;
}

float GAPlus::getMovZ() {
	return movZ;
}

void GAPlus::setMovX(float x) {
	movX = x;
}

void GAPlus::setMovY(float y) {
	movY = y;
}

void GAPlus::setMovZ(float z) {
	movZ = z;
}
