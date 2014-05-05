/*
	Axiom
	CuboidAsset.cpp
	Author: Joseph Watts
	Created on: 29 Apr 2014
	Based on code provided by aidan
*/

#include "CuboidAsset.h"

CuboidAsset::CuboidAsset(float x, float y, float z, 
					   float sX, float sY, float sZ) : GameAsset(
									string("shaders/hello-gl.v.glsl")
									, string("shaders/hello-gl.f.glsl")
	      )
{
	buildObj(x, y, z, sX, sY, sZ);

	bbox.reset();
	bbox = shared_ptr<BoundingBox>(new BoundingBox(Point3(x, y, z), sX, sY, sZ));

	make_resources();
}

CuboidAsset::CuboidAsset(float x, float y, float z, float sX, float sY, float sZ, const string & v_shader, const string & f_shader) : GameAsset(v_shader, f_shader)
{
	buildObj(x, y, z, sX, sY, sZ);
	bbox.reset();
	bbox = shared_ptr<BoundingBox>(new BoundingBox(Point3(x, y, z), sX, sY, sZ));

	make_resources();
}

CuboidAsset::~CuboidAsset()
{

}

void CuboidAsset::update()
{

}

void CuboidAsset::draw()
{
	GameAsset::draw();
}

void CuboidAsset::buildObj(float x, float y, float z, float sX, float sY, float sZ)
{
	num_vertices = 8;
	num_triangles = 12;
	g_vertex_buffer_data = new GLfloat[num_vertices * 3];
	g_element_buffer_data = new GLushort[num_triangles * 3];

	g_vertex_buffer_data[0]  = -sX/2;
	g_vertex_buffer_data[1]  = -sY/2;		
	g_vertex_buffer_data[2]  = -sZ/2;

	g_vertex_buffer_data[3]  = -sX/2 + sX;
	g_vertex_buffer_data[4]  = -sY/2;		
	g_vertex_buffer_data[5]  = -sZ/2;

	g_vertex_buffer_data[6]  = -sX/2;
	g_vertex_buffer_data[7]  = -sY/2 + sY;		
	g_vertex_buffer_data[8]  = -sZ/2;

	g_vertex_buffer_data[9]  = -sX/2 + sX;
	g_vertex_buffer_data[10] = -sY/2 + sY;		
	g_vertex_buffer_data[11] = -sZ/2;

	g_vertex_buffer_data[12] = -sX/2;
	g_vertex_buffer_data[13] = -sY/2;		
	g_vertex_buffer_data[14] = -sZ/2 + sZ;

	g_vertex_buffer_data[15] = -sX/2 + sX;
	g_vertex_buffer_data[16] = -sY/2;		
	g_vertex_buffer_data[17] = -sZ/2 + sZ;

	g_vertex_buffer_data[18] = -sX/2;
	g_vertex_buffer_data[19] = -sY/2 + sY;		
	g_vertex_buffer_data[20] = -sZ/2 + sZ;

	g_vertex_buffer_data[21] = -sX/2 + sX;
	g_vertex_buffer_data[22] = -sY/2 + sY;		
	g_vertex_buffer_data[23] = -sZ/2 + sZ;

	g_element_buffer_data[0]  = 0;
	g_element_buffer_data[1]  = 1;
	g_element_buffer_data[2]  = 3;

	g_element_buffer_data[3]  = 0;
	g_element_buffer_data[4]  = 2;
	g_element_buffer_data[5]  = 3;

	g_element_buffer_data[6]  = 0;
	g_element_buffer_data[7]  = 4;
	g_element_buffer_data[8]  = 6;

	g_element_buffer_data[9]  = 0;
	g_element_buffer_data[10] = 2;
	g_element_buffer_data[11] = 6;

	g_element_buffer_data[12] = 0;
	g_element_buffer_data[13] = 1;
	g_element_buffer_data[14] = 5;

	g_element_buffer_data[15] = 0;
	g_element_buffer_data[16] = 4;
	g_element_buffer_data[17] = 5;

	g_element_buffer_data[18] = 1;
	g_element_buffer_data[19] = 5;
	g_element_buffer_data[20] = 7;

	g_element_buffer_data[21] = 1;
	g_element_buffer_data[22] = 3;
	g_element_buffer_data[23] = 7;

	g_element_buffer_data[24] = 2;
	g_element_buffer_data[25] = 3;
	g_element_buffer_data[26] = 7;

	g_element_buffer_data[27] = 2;
	g_element_buffer_data[28] = 6;
	g_element_buffer_data[29] = 7;

	g_element_buffer_data[30] = 4;
	g_element_buffer_data[31] = 5;
	g_element_buffer_data[32] = 7;

	g_element_buffer_data[33] = 4;
	g_element_buffer_data[34] = 6;
	g_element_buffer_data[35] = 7;
}
