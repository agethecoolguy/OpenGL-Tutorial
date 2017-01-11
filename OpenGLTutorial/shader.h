#pragma once

#include <string>
#include <GL/glew.h>

using namespace std;

class Shader
{
public:
	Shader(const string& filename);

	void bind();

	virtual ~Shader();
private:
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& ither) {}
	void operator=(const Shader& other) {}

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
};

