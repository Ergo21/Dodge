#ifndef MAIN_H_
#define MAIN_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>

using namespace std;

//! A test class.
/*!
    A simple class to test tools such as doxygen
*/

class Main
{
 public:
  //! A test method.
  /*!
    A simple Hello World method
  */
  int main(int argc, char ** argv);
}
