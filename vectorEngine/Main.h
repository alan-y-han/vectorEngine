#pragma once
#define GLEW_STATIC

#include <iostream>

#include <glew.h>
#include <glfw3.h>

#include "Shader.h"

// Data

GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f,  0.5f, 0.0f
};

// Constants

const GLuint WINDOW_WIDTH = 800;
const GLuint WINDOW_HEIGHT = 600;

// Function prototypes

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
