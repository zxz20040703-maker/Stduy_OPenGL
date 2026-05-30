#pragma once
#include"DrawCallData.h"
#include"shaderer.h"
void __stdcall debugCallback(GLenum source, GLenum type, GLuint id,GLenum severity, GLsizei length,const GLchar* message, const void* userParam);
static void DebugerEnable();
void GLInit(GLFWwindow*& window);

class Renderer {
public:
	void Draw(const VertexArray& vao , const Shader& shader , const IndexBuffer& ibo) const;
	void Clear(const GLbitfield& msk) const noexcept;
};
