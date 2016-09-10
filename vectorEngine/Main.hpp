#pragma once

#include <iostream>


// External
#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);