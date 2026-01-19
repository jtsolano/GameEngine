#pragma once

#include <Mesh.h>
#include <Color.h>

namespace PrimitiveMeshBuilder
{
	shared_ptr<Mesh> BuildScreenQuad();

	shared_ptr<Mesh> BuildQuad(float InQuadSize);

	shared_ptr<Mesh> BuildQuad(float InQuadSize, Color InColor);

	shared_ptr<Mesh> BuildQuadTexture(float InQuadSize);

	shared_ptr<Mesh> BuildCube(float InCubeSize);

	shared_ptr<Mesh> BuildCubeTextured(float InCubeSize);

	shared_ptr<Mesh> BuildSphere();

	shared_ptr<Mesh> BuildTorus();

}