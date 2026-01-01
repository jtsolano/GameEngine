#include <Drawable.h>

Drawable::Drawable()
{
	m_Program = make_shared<Program>();
	m_Mesh = make_shared<Mesh>();
}

void Drawable::Draw()
{
	m_Program->Use();
	m_Mesh->Draw();
}