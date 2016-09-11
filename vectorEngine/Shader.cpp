#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	GLuint vertexShader = createShader(vertexPath, GL_VERTEX_SHADER);
	GLuint fragShader = createShader(fragmentPath, GL_FRAGMENT_SHADER);
	Program = createShaderProgram(vertexShader, fragShader);

	// Clean up shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
}

Shader::Shader(const GLchar* vertexPath, const GLchar* geomPath, const GLchar* fragmentPath)
{
	GLuint vertexShader = createShader(vertexPath, GL_VERTEX_SHADER);
	GLuint geomShader = createShader(geomPath, GL_GEOMETRY_SHADER);
	GLuint fragShader = createShader(fragmentPath, GL_FRAGMENT_SHADER);
	Program = createShaderProgram(vertexShader, geomShader, fragShader);

	// Clean up shaders
	glDeleteShader(vertexShader);
	glDeleteShader(geomShader);
	glDeleteShader(fragShader);
}

void Shader::Use()
{
	glUseProgram(this->Program);
}

std::string Shader::openTextFile(std::string & filename)
{
	std::string shaderCode;

	std::ifstream shaderFile;
	// ensures ifstream objects can throw exceptions:
	shaderFile.exceptions(std::ifstream::badbit);
	try
	{
		// Open files
		shaderFile.open(filename);

		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		// close file handlers
		shaderFile.close();
		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Failed to open shader file: " << filename << std::endl;
	}

	return shaderCode;
}

GLuint Shader::createShader(std::string filename, GLenum shaderType)
{
	GLuint shader;
	shader = glCreateShader(shaderType);

	std::string vertexShaderString = Shader::openTextFile(filename);
	const char * vertexShaderStringChar = vertexShaderString.c_str();
	glShaderSource(shader, 1, &vertexShaderStringChar, NULL);
	glCompileShader(shader);

	// Check for errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "Error: shader compilation failed: " << filename << "!\nInfo: " << infoLog << std::endl;
	}

	return shader;
}

GLuint Shader::createShaderProgram(GLuint vertexShader, GLuint fragShader)
{
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);

	checkShaderProgramErrors(shaderProgram);

	return shaderProgram;
}

GLuint Shader::createShaderProgram(GLuint vertexShader, GLuint geomShader, GLuint fragShader)
{
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, geomShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);

	checkShaderProgramErrors(shaderProgram);

	return shaderProgram;
}

void Shader::checkShaderProgramErrors(GLuint shaderProgram)
{
	// Check for errors
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "Error: shader linking failed\nInfo:" << infoLog << std::endl;
	}
}
