#pragma once

#include <Program.h>
#include <Mesh.h>

class Drawable
{
public:
	Drawable();
	~Drawable() {}

	void Draw();

public:
	shared_ptr<Program> m_Program;
	shared_ptr<Mesh> m_Mesh;
};