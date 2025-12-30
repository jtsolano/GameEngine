#include <VertexArray.h>


void VertexArray::Initialize()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);


	m_VBO.Initialize();
	m_EBO.Initialize();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void VertexArray::Draw()
{
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

