#pragma once
#include<GL/glew.h>
#include<iostream>


struct ShaderProgramResource
{
	std::string VertexShader;
	std::string FragmentShader;
};


 class Shader {
	 private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	ShaderProgramResource m_Source;
	static unsigned int CompileShader(unsigned int type, const std::string& source);
	static int CreatShader(const std::string& vertexShader, const std::string& fragmentShader);
	static ShaderProgramResource ParseShader(std::string filePath);

 public:
	 Shader(const std::string& filepath) : m_FilePath(filepath), m_RendererID(0)
	 {
		 m_Source = ParseShader(filepath);
		 m_RendererID = CreatShader(m_Source.VertexShader, m_Source.FragmentShader);
	 }
	 ~Shader()
	 {
		 glDeleteProgram(m_RendererID);
	 }

	 Shader& operator=(const Shader& other) = delete;
	 Shader(const Shader& other) = delete;

	 inline void Bind() const
	 {
		 glUseProgram(m_RendererID);
	 }
	 inline void Unbind() const
	 {
		 glUseProgram(0);
	 }
	 const int GetUniformLocation(const std::string& name) const
	 {
		 int location = glGetUniformLocation(m_RendererID, name.c_str());
		 if (location == -1)
			 std::cout << "Warning : uniform" << name << "doesn't exist!" << std::endl;
		 return location;
	 }
 };