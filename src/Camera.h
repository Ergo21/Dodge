/*
	Axiom
	Camera.h
	Author: Joseph Watts
	Created on: 29 Apr 2014
	Based on code provided by aidan
*/

#include <vectormath/scalar/cpp/vectormath_aos.h>

#ifndef CAMERA_H_
#define CAMERA_H_

using namespace Vectormath::Aos;

//! Camera class.
/*!
    Stores a 4x4 Matrix to transform the world and changes the Matrix as appropriate when the camera moves.
*/

class Camera {
public:
	/*!
	    Not implemented.
	*/
	virtual ~Camera();
	/*!
	    Creates itself if undefined and returns itself.
	*/
	static Camera& getInstance();
	/*!
	    Changes the Camera's 4x4 Matrix to the one given.
	*/
	void setCamera(const Matrix4 & m);
	/*!
	    Changes the Camera's 4x4 Matrix to the one returned by Matrix4's lookAt method.
	*/
	void lookAt(const Point3 &eye, const Point3 &point, const Vector3 &up);
	/*!
	    Returns the Camera's 4x4 Matrix as an array of floats
	*/
	float* getCamera();
	/*!
	    Returns the Camera's 4x4 Matrix
	*/
	Matrix4& getCameraM();

private:
	/*!
	    Creates camera as 4x4 Matrix with no transformation
	*/
	Camera(){camera = new Matrix4(Matrix4::identity());};
	/*!
	    Not implemented.
	*/
	Camera(Camera& c){};
	/*!
	    Not implemented.
	*/
	static Camera * c;
	Matrix4 * camera;
};

#endif
