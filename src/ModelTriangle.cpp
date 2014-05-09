/*
	Axiom
	ModelTriangle.cpp
	Author: Joseph Watts
	Created on: 29 Apr 2014
	Based on code provided by aidan
*/
#include "ModelTriangle.h"

ModelTriangle::ModelTriangle(Point3 p1, Point3 p2, Point3 p3) {
	pointA = p1;
	pointB = p2;
	pointC = p3;
}

Point3 ModelTriangle::getPoi1() {
	return pointA;
}

Point3 ModelTriangle::getPoi2() {
	return pointB;
}

Point3 ModelTriangle::getPoi3() {
	return pointC;
}

Vector3 ModelTriangle::getNormal() {
	Vector3 U, V;

	U = pointB - pointA; 
	V = pointC - pointA;

	return cross(U, V);
}

Vector3 ModelTriangle::getU() {
	return pointB - pointA;
}

Vector3 ModelTriangle::getV() {
	return pointC - pointA;
}
