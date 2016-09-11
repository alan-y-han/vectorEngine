#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glew.h>

class Shader
{
public:

	GLuint Program;

	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	Shader(const GLchar* vertexPath, const GLchar* geomPath, const GLchar* fragmentPath);
	void Use();

	static std::string openTextFile(std::string & filename);
	static GLuint createShader(std::string filename, GLenum shaderType);
	static GLuint createShaderProgram(GLuint vertexShader, GLuint fragShader);
	static GLuint createShaderProgram(GLuint vertexShader, GLuint geomShader, GLuint fragShader);

private:
	static void checkShaderProgramErrors(GLuint shaderProgram);
};
