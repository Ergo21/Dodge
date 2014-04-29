/*
	Axiom
	GameAsset.cpp
	Author: Joseph Watts
	Created on: 29 Apr 2014
	Based on code provided by balor
*/

#include "GameAsset.h"

void GameAsset::common_init() {
  bbox = shared_ptr<BoundingBox>(new BoundingBox(Point3(0,0,0), 1.0, 1.0, 1.0)); // unit cube
}

GameAsset::GameAsset() {
  common_init();
  this->v_shader = "shaders/hello-gl.v.glsl";
  this->f_shader = "shaders/hello-gl.f.glsl";
}

GameAsset::GameAsset(const string & v_shader, const string & f_shader) {
  common_init();
  this->v_shader = v_shader;
  this->f_shader = f_shader;
}

GameAsset::~GameAsset() {
	// TODO Auto-generated destructor stub
}

bool GameAsset::collidesWith(GameAsset & a ) {
  /*if(bbox->collidesWith((*a.bbox)))
  {
	  //cout<<"Bounding box collision detected"<<endl;
	  return PolygonTest::getCollision(this->getTriangles(), a.getTriangles());
  }
  return false;*/
	//return PolygonTest::getCollision(this->getTriangles(), a.getTriangles());
	return bbox->collidesWith((*a.bbox));
}

/*vector<ModelTriangle> GameAsset::getTriangles()
{
	vector<ModelTriangle> thTriangles;
	Point3 poi1, poi2, poi3;
	int eleSize = num_triangles*3;
	for(int i = 0; i < eleSize; i += 3)
	{
		poi1 = Point3(g_vertex_buffer_data[(g_element_buffer_data[i])], 
					  g_vertex_buffer_data[(g_element_buffer_data[i]) + 1],
					  g_vertex_buffer_data[(g_element_buffer_data[i]) + 2]);

		poi2 = Point3(g_vertex_buffer_data[(g_element_buffer_data[(i)+1])], 
					  g_vertex_buffer_data[(g_element_buffer_data[(i)+1]) + 1],
					  g_vertex_buffer_data[(g_element_buffer_data[(i)+1]) + 2]);

		poi3 = Point3(g_vertex_buffer_data[(g_element_buffer_data[(i)+2])], 
					  g_vertex_buffer_data[(g_element_buffer_data[(i)+2]) + 1],
					  g_vertex_buffer_data[(g_element_buffer_data[(i)+2]) + 2]);
		//use vertex and element buffers
		thTriangles.push_back(ModelTriangle(poi1, poi2, poi3));
	}
	return thTriangles;
}*/

void GameAsset::draw() {
  glUseProgram(program);

  Matrix4 cam = Camera::getInstance().getCameraM();
  
  
  float cam_unpacked[] = {cam.getCol0().getX(), cam.getCol0().getY(), cam.getCol0().getZ(), cam.getCol0().getW(),
						  cam.getCol1().getX(), cam.getCol1().getY(), cam.getCol1().getZ(), cam.getCol1().getW(),
						  cam.getCol2().getX(), cam.getCol2().getY(), cam.getCol2().getZ(), cam.getCol2().getW(),
						  0,0,0,1};
						  //cam.getCol3().getX(), cam.getCol3().getY(), cam.getCol3().getZ(), cam.getCol3().getW()};

  float model_unpacked[] = {1,0,0, 0,
							0,1,0, 0,
							0,0,1, 0,
							bbox->getCentre()->getX()-cam.getCol3().getX(), bbox->getCentre()->getY()-cam.getCol3().getY(), bbox->getCentre()->getZ()-cam.getCol3().getZ(), 1};

  //  std::cout << "tx.x " << tx.getX() << "\ttx.y " << tx.getY() << "\t tx.z " << tx.getZ() << std::endl;
  
  glUniformMatrix4fv(camera_uniform, 1, GL_FALSE, cam_unpacked);
  glUniformMatrix4fv(model_uniform, 1, GL_FALSE, model_unpacked);

  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glVertexAttribPointer(
			position_attrib,                  // attribute 
			3,                                // size 
			GL_FLOAT,                         // type 
			GL_FALSE,                         // normalized? 
			0,                                // stride 
			(void*)0                          // array buffer offset 
			);
  glEnableVertexAttribArray(position_attrib);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
  glDrawElements(
		 GL_TRIANGLES,
		 3 * this->num_triangles,
		 GL_UNSIGNED_SHORT,
		 (GLvoid*) 0
		 );
  
  glDisableVertexAttribArray(position_attrib);
}

/*
 * Functions for general purpose stuff
 */
GLchar * GameAsset::shader_file_contents(const string &filename, GLint * length)
{
  ifstream input_file;
  input_file.open(filename.c_str(), ios::in);

  input_file.seekg(0, ios::end);  // go to the end of the file
  *length = input_file.tellg();  // get length of the file
  input_file.seekg(0, ios::beg);  // go to beginning of the file

  GLchar * buffer = new GLchar[(*length)+1];
  input_file.read(buffer, *length);
  buffer[(*length)+1]='\0';  // Ensure null terminated

  input_file.close();
  return buffer;
}

/*
 * Functions for creating OpenGL objects:
 */
GLuint GameAsset::make_buffer(
    GLenum target,
    const void *buffer_data,
    GLsizei buffer_size
) {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, buffer_size, buffer_data, GL_STATIC_DRAW);
    return buffer;
}

GLuint GameAsset::make_shader(GLenum type, const char *filename)
{
    GLint length;
    GLchar *source = shader_file_contents(filename, &length);
    GLuint shader;
    GLint shader_ok;

    if (!source)
        return 0;

    shader = glCreateShader(type);
    glShaderSource(shader, 1, (const GLchar**)&source, &length);
    //delete(source);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
    if (!shader_ok) {
        cerr << "Failed to compile " << filename << " with error code " << shader_ok << endl;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

GLuint GameAsset::make_program(GLuint vertex_shader, GLuint fragment_shader)
{
    GLint program_ok;

    GLuint program = glCreateProgram();

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &program_ok);
    if (!program_ok) {
        cerr<< "Failed to link shader program:" << endl;
        glDeleteProgram(program);
        return 0;
    }
    return program;
}

/*
 * Load and create all of our resources:
 */
int GameAsset::make_resources(void)
{
    vertex_buffer = make_buffer(
        GL_ARRAY_BUFFER,
        g_vertex_buffer_data,
        3 * sizeof(GLfloat) * this->num_vertices
    );
    element_buffer = make_buffer(
        GL_ELEMENT_ARRAY_BUFFER,
        g_element_buffer_data,
        3 *  sizeof(GLushort) * this->num_triangles
    );

    vertex_shader = make_shader(
        GL_VERTEX_SHADER,
        this->v_shader.c_str()
    );
    if (vertex_shader == 0)
        return 0;

    fragment_shader = make_shader(
        GL_FRAGMENT_SHADER,
        this->f_shader.c_str()
    );
    if (fragment_shader == 0)
        return 0;
    
    program = make_program(vertex_shader, fragment_shader);
    if (program == 0)
        return 0;

    position_attrib = glGetAttribLocation(program, "position");
    camera_uniform = glGetUniformLocation(program, "camera");
	model_uniform = glGetUniformLocation(program, "model");

    return 1;
}
