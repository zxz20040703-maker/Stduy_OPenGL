#pragma once
#include<vector>
#include<iostream>
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include"stb_image.h"

struct Element
{
	unsigned int type;
	unsigned int count;
	bool isnormalization;


	Element(unsigned int a, unsigned int b, unsigned int c) :type(a), count(b), isnormalization(c) {};
	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		default:
			std::cout << "error type" << std::endl;
			break;
		}
		return 0;
	}
};

class VertexBuffer {
private:
	unsigned int m_RendererID;

public:
	VertexBuffer(const void* data ,unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};
class IndexBuffer {
	private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public :
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
	__inline size_t GetCount() const{
		return m_Count;
	}
};
class ElementsLayout {

private:
	std::vector<Element> contain;
	unsigned int Stride;
public:



	ElementsLayout() : Stride(0) {}

	template<typename T>
	void Push(unsigned int count);

	template<>
	void Push<float>(unsigned int count)
	{

		contain.push_back({ GL_FLOAT , count , GL_FALSE });
		Stride += sizeof(float) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		contain.push_back({ GL_UNSIGNED_INT , count , GL_FALSE });
		Stride += sizeof(unsigned int) * count;
	}

	template<>
	void Push < unsigned char>(unsigned int count) {
		contain.push_back({ GL_FLOAT , count , GL_FALSE });
		Stride += sizeof(unsigned char)*count;
	}

	inline const std::vector<Element>& GetContain() const { return contain; }
	inline const unsigned int& GetStride() const { return Stride; }
};

/// <summary>
/// ½ûÖ¹¿½±´ºÍÒÆ¶¯
/// </summary>
class VertexArray {
	private:
		unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	VertexArray(VertexArray&&) = delete;
	VertexArray& operator=( VertexArray&&)=default;

	VertexArray(const VertexArray&) = delete;
	VertexArray& operator=(const VertexArray&) = delete;

	void Bind() const;
	void Unbind() const;
	void AddBuffer(const VertexBuffer& vbo,const ElementsLayout& layout);
};

class Martial {

};
class Texture {
private :
	const char* texturePath;
	 unsigned char* m_localBuffer;
	unsigned int m_RendererID;
	 int width, height , bpp;

public:
	Texture(const std::string& path);
	void constexpr Bind(unsigned int slot = 0) const;
	void constexpr Unbind() const;

	unsigned int constexpr __inline GetID() const { return m_RendererID; }
};
