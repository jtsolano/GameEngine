#pragma once

#include <Program.h>
#include <Mesh.h>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

struct ConstantRotation
{
	float AngleDegrees;
	glm::vec3 Axis;
};


class Drawable
{
public:
	Drawable();
	~Drawable() {}

	float* GetModelMatrixPtr() { return glm::value_ptr(m_ModelMatrix); }

	void Translate(const glm::vec3& InTranslation);

	void Rotate(float InAngleDegrees, const glm::vec3& InAxis);

	void AddConstantRotation(float InAngleDegrees, const glm::vec3& InAxis)
	{
		ConstantRotation NewRotation;
		NewRotation.AngleDegrees = InAngleDegrees;
		NewRotation.Axis = InAxis;
		m_ConstantRotations.push_back(NewRotation);
	}

	void Update(float DeltaTime)
	{
		for (const ConstantRotation& Rotation : m_ConstantRotations)
		{
			Rotate(Rotation.AngleDegrees * DeltaTime, Rotation.Axis);
		}
	}

public:
	shared_ptr<Program> m_Program;
	shared_ptr<Mesh> m_Mesh;
	glm::mat4 m_ModelMatrix = glm::mat4(1.0f);

	vector<ConstantRotation> m_ConstantRotations;

};