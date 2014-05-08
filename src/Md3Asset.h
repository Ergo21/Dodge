/*
	Axiom
	Md2Asset.h
	Author: Joseph Watts
	Created on: 29 Apr 2014
	Based on code provided by aidan
*/

#include <GL/glew.h>
#include <GL/gl.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory>

#include "vectormath/scalar/cpp/vectormath_aos.h"
#include "GameAsset.h"


using namespace std;
using namespace Vectormath::Aos;

#ifndef MD3ASSET_H_
#define MD3ASSET_H_

class Md3Asset : public GameAsset {
public:
	Md3Asset(const string &filename);
	Md3Asset(const string &filename, const string & v_shader, const string & f_shader);
	virtual ~Md3Asset();

	virtual void update();
private:
	void import_md3_asset(const string &filename);
		/* MD3 header built from http://icculus.org/~phaethon/q3a/formats/md3format.html */
	struct md3_header_t
	{
	  int ident;                  /* magic number: "IDP3" */
	  int version;                /* version: must be 15 */
	  unsigned char name[64];     	// file name, max 64 characters
	  int flags;
	  int num_frames;		//Number of frame objs in MD3, MAX = 1024
	  int num_tags;			//Number of tag objs in MD3, MAX = 16
	  int num_surfaces;		//Number of surface objs in MD3, MAX = 32
	  int num_skins;		//Number of skin objs in MD3, has no offset
	  int ofs_frames;		//Relative offset from start of MD3 where Frame objs start, frames are sequential
	  int ofs_tags;			//Relative offset from start of MD3 where Tag objs start, tags are sequential
	  int ofs_surfaces;		//Relative offset from start of MD3 where Surface objs start, surfaces are sequential
	  int ofs_EOF;			//Relative offset from start of MD3 to end of MD3
	};
	
	//Compressed frame
	struct md3_frame_t
	{
	  Vector3 min_bounds;		//First corner of bounding box
	  Vector3 max_bounds;		//Second corner of bounding box
	  Vector3 loc_origin;		//Local origin
	  float radius;			//Radius of bounding sphere
	  unsigned char name[16];	//Name of frame, MAX 16 characters
	};

	//Compressed tag
	struct md3_tag_t
	{
	  unsigned char name[64];	//Name of tag, MAX 64 characters
	  Vector3 origin;		//Coords of tag
   	  Vector3 axis[3];		//Orientation of tag
	};
	
	//Compressed surface
	struct md3_surface_t
	{
	  int ident;              	/* magic number: "IDP3" */
	  unsigned char name[64];	//Name of surface, MAX 64 characters
	  int flags;	
	  int num_frames;		//Number of frame objs in MD3, MAX = 1024, should be equal to md3_header_t num_frames
	  int num_shaders;		//Number of shader objs in MD3, MAX = 256
	  int num_verts;		//Number of vertex objs in MD3, MAX = 4096
	  int num_triangles;		//Number of triangles objs in MD3, MAX = 8192
	  int ofs_triangles;		//Relative offset from start of surface where triangle objs start
	  int ofs_shaders;		//Relative offset from start of surface where shader objs start
	  int ofs_st;			//Relative offset from start of surface where texCoord objs start
	  int ofs_XYZNormal;		//Relative offset from start of surface where vertex objs (x,y,z,n) start
	  int ofs_end;			//Relative offset from start of surface to end of surface
	};

	//Compressed shader
	struct md3_shader_t
	{
	  unsigned char name[64];	//Path name of surface, MAX 64 characters
 	  int shader_index;		//Shader index number
	};

	/* Triangle info */
	struct md3_triangle_t
	{
	  int indexes[3];   		//List of offset values into the list of Vertex objs that are the corners of the Triangle object.
	};

	// Texture coordinate
	struct md3_texcoord_t
	{
	  float st[2];			//S-T texture coordinates
	};

	/* Compressed vertex */
	struct md3_vertex_t
	{
	  short x;         	// x coord in left-handed 3-space
	  short y;   		// y coord in left-handed 3-space
	  short z;		// z coord in left-handed 3-space
	  short normal;	  	// Encoded normal vector
	};
};
#endif
