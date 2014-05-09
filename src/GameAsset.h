/*
	Axiom
	GameAsset.h
	Author: Joseph Watts
	Created on: 29 Apr 2014
	Based on code provided by balor
*/
#include <GL/glew.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

#include "vectormath/scalar/cpp/vectormath_aos.h"
#include "Camera.h"
#include "BoundingBox.h"
#include "ModelTriangle.h"
#include "PolygonTest.h"
#include "GAPlus.h"

using namespace std;
using namespace Vectormath::Aos;

#ifndef GAMEASSET_H_
#define GAMEASSET_H_

  //! GameAsset Class
  /*!
    The super class of all other objects in the game, containing vertex & fragment shaders and the objects model.
  */
class GameAsset {
public:
	GameAsset();
	GameAsset(const string & v_shader, const string & f_shader);
	virtual ~GameAsset();
	
	//! Collision method
  	/*!
    		Method to detect if this asset collides with given asset.
  	*/
	bool collidesWith(GameAsset & a);
	//! Sets GAPlus method
  	/*!
    		Method to change this classes GAPlus.
  	*/
	void setGAP(shared_ptr<GAPlus> g);
	//! Gets GAPlus method
	shared_ptr<GAPlus> getGAP();

	//! Draw Method
	/*!
		Draws object on screen based on vertex and element buffer data
	*/
	virtual void draw();
	virtual void update()=0;

	/*!
    		Method to move object along x dimension by given amount.
  	*/
	void moveX(float x);
	/*!
    		Method to move object along y dimension by given amount.
  	*/
	void moveY(float y);
	/*!
    		Method to move object along z dimension by given amount.
  	*/
	void moveZ(float z);

protected:
	/* functions */
	//! Create shaders & buffers method
  	/*!
    		Creates this assets buffers, shaders and shader program.
  	*/
	int make_resources();
	//! Shader file reader
  	/*!
    		Reads this GameAsset's shader file and returns it.
  	*/
	GLchar* shader_file_contents(const string &filename, GLint * length);
	//! Create Buffers method
  	/*!
    		Creates this assets buffers.
  	*/
	GLuint make_buffer(GLenum target, const void *buffer_data, GLsizei buffer_size);
	//! Create Shaders method
  	/*!
    		Creates this assets shaders.
  	*/
	GLuint make_shader(GLenum type, const char *filename);
	//! Create program method
  	/*!
    		Creates this assets shader program.
  	*/
	GLuint make_program(GLuint vertex_shader, GLuint fragment_shader);
  	/*!
    		Returns this model as a list of ModelTriangle
  	*/
	vector<ModelTriangle> getTriangles();

	/* For keeping track of OpenGL VBOs */
	GLuint vertex_buffer, element_buffer;
	GLuint vertex_shader, fragment_shader, program;
	GLint position_attrib;
	GLint camera_uniform;
	GLint model_uniform;

	GLfloat * g_vertex_buffer_data;
	GLushort * g_element_buffer_data;
      
	// How many vertices/triangles in this model
	int num_vertices;
	int num_triangles;

	shared_ptr<BoundingBox> bbox;

 private:
	//! Seperate initialise method
  	/*!
    		Currently creates this GameAsset's BoundingBox
  	*/
	void common_init(); // because we don't have delegating constructors yet (http://gcc.gnu.org/projects/cxx0x.html)
	string v_shader;
	string f_shader;
	shared_ptr<GAPlus> thiGAP;
};

#endif
