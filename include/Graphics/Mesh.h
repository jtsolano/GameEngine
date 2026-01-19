#pragma once


struct LayoutDefinition
{
	int Size; 		 // Number of components (e.g., 3 for vec3)
	int SizeOfComponent; // Size of each component in bytes (e.g., sizeof(float))
};

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

	// Sets vertex layout
	void SetVertexLayout(const vector<LayoutDefinition>& InLayoutDefinitions);

	// Binds the VAO and draws
	void Draw();

protected:
	uint m_VAO = 0;
	uint m_VBO = 0;
	uint m_EBO = 0;
	uint m_VertexCount = 0;
};