#include <VertexBuffer.h>


VertexBuffer::~VertexBuffer()
{
	Destroy();
}

void VertexBuffer::Initialize()
{
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
}

void VertexBuffer::SetData(void* InVertexData, uint InSize)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, InSize, InVertexData, GL_STATIC_DRAW);
}

void VertexBuffer::Destroy()
{
	if (m_VBO != 0)
	{
		glDeleteBuffers(1, &m_VBO);
	}
}