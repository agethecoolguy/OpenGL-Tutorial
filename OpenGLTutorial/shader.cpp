#include "shader.h"
#include <fstream>
#include <iostream>

static string loadShader(const string& filename);
static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage);
static GLuint createShader(const string& text, GLenum shaderType);

Shader::Shader(const string& filename)
{
	m_program = glCreateProgram();
	m_shaders[0] = createShader(loadShader(filename + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = createShader(loadShader(filename + ".fs"), GL_FRAGMENT_SHADER);

	for (int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(m_program, m_shaders[i]);
	}

	glBindAttribLocation(m_program, 0, "position");

	glLinkProgram(m_program);
	checkShaderError(m_program, GL_LINK_STATUS, true, "Error: Program failed to link: ");

	glValidateProgram(m_program);
	checkShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program failed to validate: ");
}

Shader::~Shader()
{
	for (int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}

	glDeleteProgram(m_program);
}

void Shader::bind()
{
	glUseProgram(m_program);
}

static GLuint createShader(const string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
	{
		cerr << "Error: shader creation failed" << endl;
	}

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	checkShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader failed to compile: ");

	return shader;
}

static string loadShader(const string& filename)
{
	ifstream file;
	file.open((filename).c_str());

	string output;
	string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		cerr << "Unable to load shader: " << filename << endl;
	}

	return output;
}

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
	{
		glGetProgramiv(shader, flag, &success);
	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE)
	{
		if (isProgram)
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}

		cerr << errorMessage << ": " << error << endl;
	}
}
