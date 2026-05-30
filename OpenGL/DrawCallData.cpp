#include"DrawCallData.h"
#include"renderer.h"


VertexBuffer::VertexBuffer(const void* data , unsigned int size )
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}
void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	:m_Count(count)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}
IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}
void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}
void IndexBuffer::Unbind()const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
}
VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind( ) const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
void VertexArray::AddBuffer(const VertexBuffer& vbo  ,const ElementsLayout& layout )
{
	this->Bind();
	vbo.Bind();
	unsigned int offset = 0;

	auto& contain = layout.GetContain();
	for (int i = 0; i < contain.size(); i++) 
	{
		auto& element = contain[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer( i ,element.count ,element.type , element.isnormalization , layout.GetStride(), (const void*)offset);
		offset += element.count * Element::GetSizeOfType(element.type);
	}

}

Texture::Texture(const std::string& path)
	: texturePath(path.c_str()), m_localBuffer(nullptr), m_RendererID(0), width(0), height(0), bpp(0)
{
	stbi_set_flip_vertically_on_load(1);
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_TEXTURE_2D, m_RendererID);

	m_localBuffer = stbi_load(texturePath, &width, &height, &bpp, 4);
	glTextureParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(m_RendererID, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

}

void Texture ::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

Texture::~Texture()
{
	glDeleteBuffers(1, &m_RendererID);
	if (m_localBuffer)
		stbi_image_free(m_localBuffer);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D ,0);
}
