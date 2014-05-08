/*
	Axiom
	Md2Asset.cpp
	Author: Joseph Watts
	Created on: 29 Apr 2014
	Based on code provided by aidan
*/
#include "Md3Asset.h"

Md3Asset::Md3Asset(const string &filename) : GameAsset(string("shaders/hello-gl.v.glsl"), string("shaders/hello-gl.f.glsl")) {
  
        import_md3_asset(filename);

	// set the bounding box
	// TODO: make this a non-arbitrary position.  Currently it makes no sense at all.
	//bbox = shared_ptr<BoundingBox>(new BoundingBox(Point3(1.0f, 1.0f, 1.0f), 1.0f, 1.0f, 1.0f));

	// make the objects to display
	if(0 == make_resources()) {
	  cout << "Can't make the required OpenGL resources for Md3Asset." << endl;	  
	  // TODO: exit nicely here
	}

}

Md3Asset::Md3Asset(const string &filename, const string & v_shader, const string & f_shader) : GameAsset(v_shader, f_shader) {
  
        import_md3_asset(filename);

	// set the bounding box
	// TODO: make this a non-arbitrary position.  Currently it makes no sense at all.
	//bbox = shared_ptr<BoundingBox>(new BoundingBox(Point3(1.0f, 1.0f, 1.0f), 1.0f, 1.0f, 1.0f));

	// make the objects to display
	if(0 == make_resources()) {
	  cout << "Can't make the required OpenGL resources for Md3Asset." << endl;	  
	  // TODO: exit nicely here
	}

}

Md3Asset::~Md3Asset() {
  // TODO: clean up
}

void Md3Asset::update() {
}

void Md3Asset::import_md3_asset(const string &filename) {
	ifstream md3file;
	md3file.open(filename, ios::in|ios::binary);

	// C stuff
	//md3_header_t * md3header = (struct md3_header_t *)
	//	malloc(sizeof(struct md3_header_t));
	// Or we could use a stack allocated variable.
	md3_header_t md3header;

	// it involves evil casting.
	md3file.read((char *) &md3header, sizeof (struct md3_header_t));

	if ((md3header.ident != 860898377) ||
			(md3header.version != 15)) {
		/* Error! */
		cerr << "Error: bad version or identifier" << endl;
	}
	
	//Currently supports 1 frame only

	md3_surface_t * surf = new md3_surface_t[md3header.num_surfaces]; //Surfaces in this frame

	vector<GLushort> * locElements = new vector<GLushort>();
	vector<GLfloat> * locVertices = new vector<GLfloat>();

	int ofsSurf = md3header.ofs_surfaces;

	int verShift = 0;

	for(int i = 0; i < md3header.num_surfaces; i++)
	{
		md3file.seekg(ofsSurf, std::ios::beg);	//Go to this surface
		md3file.read((char *)&surf[i], sizeof(md3_surface_t));	//Read md3 surface and store as surf[i]

		md3_triangle_t * mTris = new md3_triangle_t[surf[i].num_triangles]; //Number of triangles in this surface

		md3file.seekg(ofsSurf + surf[i].ofs_triangles, std::ios::beg); //Go to this triangle
		md3file.read((char*)mTris, sizeof(md3_triangle_t)* surf[i].num_triangles);	   //Read md3 triangle and store in mTris

		verShift = locVertices->size();

		for (int j = 0; j < surf[i].num_triangles * 3; j++) {
			locElements->push_back( (mTris[j].indexes[0] + verShift));
			locElements->push_back( (mTris[j].indexes[1] + verShift));
			locElements->push_back( (mTris[j].indexes[2] + verShift));
		}


		md3_vertex_t * vertLoc = new md3_vertex_t[surf[i].num_verts];
		md3file.seekg(ofsSurf + surf[i].ofs_XYZNormal, std::ios::beg);
		md3file.read((char*)vertLoc, sizeof(md3_vertex_t)* surf[i].num_verts);

		for (int j = 0; j < surf[i].num_verts; j++) {
			locVertices->push_back(vertLoc[j].x/64);
			//cout<<vertLoc[j].x/64<<endl;
			locVertices->push_back(vertLoc[j].y/64);
			locVertices->push_back(vertLoc[j].z/64);
		}

		//cout<< "Triangles: " << surf[i].num_triangles << endl;


		ofsSurf += surf[i].ofs_end;

		delete[] vertLoc;
		delete[] mTris;

	}
	this->g_element_buffer_data = new GLushort[locElements->size()]; // 3 vertices per triangle

	for(int i = 0; i < locElements->size(); i++) {
		g_element_buffer_data[i] = locElements->at(i);
	}

	this->g_vertex_buffer_data = new GLfloat[locVertices->size()];

	for(int i = 0; i < locVertices->size(); i++) {
		g_vertex_buffer_data[i] = locVertices->at(i);
	}

	// Hopefully we now have vertices.  Note: No error checking.
	// cleanup
	md3file.close();
	delete locElements;
	delete locVertices;
}
