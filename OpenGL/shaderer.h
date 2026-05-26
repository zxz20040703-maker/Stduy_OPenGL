#pragma once
#include<GL/glew.h>
#include<iostream>
#include<fstream>
#include<sstream>

struct ShaderProgramResource
{
	std::string VertexShader;
	std::string FragmentShader;
};
 ShaderProgramResource ParseShader(std::string filePath);

unsigned int CompileShader(unsigned int type, const std::string& source);

 
 int CreatShader(const std::string& vertexShader, const std::string& fragmentShader);