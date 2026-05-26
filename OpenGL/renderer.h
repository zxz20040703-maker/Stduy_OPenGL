#pragma once
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>

void __stdcall debugCallback(GLenum source, GLenum type, GLuint id,GLenum severity, GLsizei length,const GLchar* message, const void* userParam);
static void DebugerEnable();
void GLInit(GLFWwindow*& window);