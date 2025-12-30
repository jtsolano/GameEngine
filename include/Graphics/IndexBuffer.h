#pragma once

class IndexBuffer
{
public:

	IndexBuffer() {}
	~IndexBuffer();

	void Initialize();

	void SetData(void* InIndexData, uint InSize);

	void Destroy();

protected:

	uint m_EBO = 0;

};