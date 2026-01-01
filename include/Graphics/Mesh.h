#pragma once

/**
 * Mesh
 * Uses Vertex Array Object, Vertex Buffer Object, Element Buffer Object to represent a mesh using OpenGL.
 */
class Mesh
{
public:

	Mesh();

	~Mesh();

	void SetVerticesData(void* InVertexData, uint InSize);

	void SetIndicesData(void* InIndexData, uint InSize);

	void SetVertexCount(uint InVertexCount) { m_VertexCount = InVertexCount; }

	// Binds the VAO and draws
	void Draw();

protected:
	uint m_VAO = 0;
	uint m_VBO = 0;
	uint m_EBO = 0;
	uint m_VertexCount = 0;
};