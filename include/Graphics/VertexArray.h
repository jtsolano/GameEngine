#pragma once

#include <VertexBuffer.h>
#include <IndexBuffer.h>

class VertexArray
{
public:

	VertexArray() {}
	~VertexArray() {}

	void Initialize();

	// Binds the VAO and draws the using the index buffer.
	void Draw();

	VertexBuffer m_VBO;
	IndexBuffer m_EBO;

protected:

	uint m_VAO = 0;
};