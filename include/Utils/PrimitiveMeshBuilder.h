#pragma once

#include <Mesh.h>

namespace PrimitiveMeshBuilder
{
	shared_ptr<Mesh> BuildQuad(float InQuadSize);

	shared_ptr<Mesh> BuildCube();

	shared_ptr<Mesh> BuildSphere();

	shared_ptr<Mesh> BuildTorus();

}