#include <Mesh.h>


Mesh::Mesh()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
}

Mesh::~Mesh()
{
	if (m_VBO != 0)
	{
		glDeleteBuffers(1, &m_VBO);
	}

	if (m_EBO != 0)
	{
		glDeleteBuffers(1, &m_EBO);
	}

	if (m_VAO != 0)
	{
		glDeleteVertexArrays(1, &m_VAO);
	}
}

void Mesh::SetVerticesData(void* InVertexData, uint InSize)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, InSize, InVertexData, GL_STATIC_DRAW);
}

void Mesh::SetIndicesData(void* InIndexData, uint InSize)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, InSize, InIndexData, GL_STATIC_DRAW);
}

void Mesh::SetVertexLayout(const vector<LayoutDefinition>& InLayoutDefinitions)
{
	size_t SizeOfAllComponents = 0;
	// first we need to figure out the size of all components
	for (uint i = 0; i < InLayoutDefinitions.size(); ++i)
	{
		const LayoutDefinition& Definition = InLayoutDefinitions[i];
		SizeOfAllComponents += Definition.SizeOfComponent * Definition.Size;
	}

	size_t SizeOfPreviousComponents = 0;
	for(uint i = 0; i < InLayoutDefinitions.size(); ++i)
	{
		if (i == 0)
		{
			SizeOfPreviousComponents = 0;
		}
		else
		{
			const LayoutDefinition& PreviousDefinition = InLayoutDefinitions[i - 1];
			SizeOfPreviousComponents += PreviousDefinition.SizeOfComponent * PreviousDefinition.Size;
		}

		const LayoutDefinition& Definition = InLayoutDefinitions[i];
		glVertexAttribPointer(i, Definition.Size, GL_FLOAT, GL_FALSE, SizeOfAllComponents, (void*)SizeOfPreviousComponents);
		glEnableVertexAttribArray(i);
	}


}

void Mesh::Draw()
{
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_VertexCount, GL_UNSIGNED_INT, 0);
}
