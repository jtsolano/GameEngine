#include <Drawable.h>

Drawable::Drawable()
{
	m_Program = make_shared<Program>();
	m_Mesh = make_shared<Mesh>();
}

void Drawable::Translate(const glm::vec3& InTranslation)
{
	m_ModelMatrix = glm::translate(m_ModelMatrix, InTranslation);
}

void Drawable::Rotate(float InAngleDegrees, const glm::vec3& InAxis)
{
	m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(InAngleDegrees), InAxis);
}
