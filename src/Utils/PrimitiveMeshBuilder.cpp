#include "PrimitiveMeshBuilder.h"


shared_ptr<Mesh> PrimitiveMeshBuilder::BuildQuad(float InQuadSize)
{
	shared_ptr<Mesh> NewMesh = make_shared<Mesh>();

	float Vertices[] = { 
		InQuadSize,  InQuadSize, 0.0f, 
		InQuadSize, -InQuadSize, 0.0f,
		-InQuadSize, -InQuadSize, 0.0f,
		-InQuadSize,  InQuadSize, 0.0f
	};

	uint Indices[] = { 0, 1, 3,	1, 2, 3 };
	NewMesh->SetVerticesData(Vertices, sizeof(Vertices));
	NewMesh->SetIndicesData(Indices, sizeof(Indices));
	NewMesh->SetVertexCount(6);

	return NewMesh;
}
