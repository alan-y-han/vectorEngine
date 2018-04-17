#pragma once

#include <glad\glad.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


class Shader
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setFloat4(const std::string &name, float v1, float v2, float v3, float v4) const;
private:
    std::string readShaderFile(const char* filepath);
    unsigned int compileShader(int shaderType, const char* shaderCode, const char* debugName);
};

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // 1. retrieve the vertex/fragment source code from filepath
    std::string vShaderStr = readShaderFile(vertexPath).c_str();
    const char* vShaderCode = vShaderStr.c_str();
    std::string fShaderStr = readShaderFile(fragmentPath).c_str();
    const char* fShaderCode = fShaderStr.c_str();

    // 2. compile shaders
    unsigned int vertex = compileShader(GL_VERTEX_SHADER, vShaderCode, "VERTEX");
    unsigned int fragment = compileShader(GL_FRAGMENT_SHADER, fShaderCode, "FRAGMENT");

    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // print linking errors if any
    int success;
    char infoLog[512];
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat4(const std::string &name, float v1, float v2, float v3, float v4) const
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), v1, v2, v3, v4);
}

std::string Shader::readShaderFile(const char * filePath)
{
    std::string shaderCode;
    std::ifstream shaderFile;
    // ensure ifstream object can throw exceptions:
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open file
        shaderFile.open(filePath);
        std::stringstream vShaderStream;
        // read file's buffer contents into streams
        vShaderStream << shaderFile.rdbuf();
        // close file handlers
        shaderFile.close();
        // convert stream into string
        shaderCode = vShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE \"" << filePath << "\" NOT_SUCCESFULLY_READ" << std::endl;
    }
    return shaderCode;
}

unsigned int Shader::compileShader(int shaderType, const char* shaderCode, const char* debugName)
{
    unsigned int shader;

    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);

    // print compile errors if any
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::" << debugName << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    };
    return shader;
}
