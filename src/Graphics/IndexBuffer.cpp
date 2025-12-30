#include <IndexBuffer.h>

IndexBuffer::~IndexBuffer()
{
	Destroy();
}

void IndexBuffer::Initialize()
{
	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
}

void IndexBuffer::SetData(void* InIndexData, uint InSize)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, InSize, InIndexData, GL_STATIC_DRAW);
}

void IndexBuffer::Destroy()
{
	if (m_EBO != 0)
	{
		glDeleteBuffers(1, &m_EBO);
	}
}