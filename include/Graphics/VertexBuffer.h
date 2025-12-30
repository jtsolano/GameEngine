#pragma once


class VertexBuffer
{
public:

	VertexBuffer() {}
	~VertexBuffer();

	void Initialize();

	void SetData(void* InVertexData, uint InSize);

	void Destroy();

protected:

	uint m_VBO = 0;

};