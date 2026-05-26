#pragma once


class VertexBuffer {
private:
	unsigned int m_RendererID;

public:
	VertexBuffer(const void* data ,unsigned int size);
	~VertexBuffer();

	void Bind();
	void Unbind();
};
class IndexBuffer {
	private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public :
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind();
	void Unbind();

};
class VertexArray {
	private:
		unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();
	void Bind();
	void Unbind();
};
	