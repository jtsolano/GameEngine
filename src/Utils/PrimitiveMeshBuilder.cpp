#include "PrimitiveMeshBuilder.h"
#include <Color.h>

shared_ptr<Mesh> PrimitiveMeshBuilder::BuildScreenQuad()
{
	shared_ptr<Mesh> NewMesh = make_shared<Mesh>();

	float Vertices[] = {
		1.f,  1.f, 0.0f,
		1.f, -1.f, 0.0f,
		-1.f, -1.f, 0.0f,
		-1.f,  1.f, 0.0f
	};

	uint Indices[] = { 0, 1, 3,	1, 2, 3 };
	NewMesh->SetVerticesData(Vertices, sizeof(Vertices));
	NewMesh->SetIndicesData(Indices, sizeof(Indices));
	NewMesh->SetVertexCount(6);

	return NewMesh;

	return shared_ptr<Mesh>();
}

shared_ptr<Mesh> PrimitiveMeshBuilder::BuildQuad(float InQuadSize, Color InColor)
{
	shared_ptr<Mesh> NewMesh = make_shared<Mesh>();

	float Vertices[] = { 
		InQuadSize,  InQuadSize, 0.0f, InColor.R, InColor.G,InColor.B,
		InQuadSize, -InQuadSize, 0.0f, InColor.R, InColor.G, InColor.B,
		-InQuadSize, -InQuadSize, 0.0f, InColor.R, InColor.G, InColor.B,
		-InQuadSize,  InQuadSize, 0.0f, InColor.R, InColor.G, InColor.B
	};

	uint Indices[] = { 0, 1, 3,	1, 2, 3 };
	NewMesh->SetVerticesData(Vertices, sizeof(Vertices));
	NewMesh->SetIndicesData(Indices, sizeof(Indices));
	NewMesh->SetVertexCount(6);
	NewMesh->SetVertexLayout({ {3, sizeof(float)}, {3, sizeof(float)} });

	return NewMesh;
}

shared_ptr<Mesh> PrimitiveMeshBuilder::BuildQuadTexture(float InQuadSize)
{
	shared_ptr<Mesh> NewMesh = make_shared<Mesh>();

	float Vertices[] = {
		InQuadSize,  InQuadSize, 0.0f, 1.0f, 1.0f,
		InQuadSize, -InQuadSize, 0.0f, 1.0f, 0.0f,
		-InQuadSize, -InQuadSize, 0.0f, 0.0f, 0.0f,
		-InQuadSize,  InQuadSize, 0.0f, 0.0f, 1.0f
	};

	uint Indices[] = { 0, 1, 3,	1, 2, 3 };
	NewMesh->SetVerticesData(Vertices, sizeof(Vertices));
	NewMesh->SetIndicesData(Indices, sizeof(Indices));
	NewMesh->SetVertexCount(6);
	NewMesh->SetVertexLayout({ {3, sizeof(float)}, {2, sizeof(float)} });
	return NewMesh;
}

shared_ptr<Mesh> PrimitiveMeshBuilder::BuildQuad(float InQuadSize)
{
	shared_ptr<Mesh> NewMesh = make_shared<Mesh>();

	float Vertices[] = {
		InQuadSize,  InQuadSize, 0.0f,
		InQuadSize, -InQuadSize, 0.0f,
		-InQuadSize, -InQuadSize, 0.0f,
		-InQuadSize,  InQuadSize, 0.0f,
	};

	uint Indices[] = { 0, 1, 3,	1, 2, 3 };
	NewMesh->SetVerticesData(Vertices, sizeof(Vertices));
	NewMesh->SetIndicesData(Indices, sizeof(Indices));
	NewMesh->SetVertexCount(6);
	NewMesh->SetVertexLayout({{3, sizeof(float)}});
	return NewMesh;
}

shared_ptr<Mesh> PrimitiveMeshBuilder::BuildCube(float InCubeSize)
{
	shared_ptr<Mesh> NewMesh = make_shared<Mesh>();

	float Vertices[] = {
		InCubeSize,  InCubeSize, InCubeSize,
		InCubeSize, -InCubeSize, InCubeSize,
		-InCubeSize, -InCubeSize, InCubeSize,
		-InCubeSize,  InCubeSize, InCubeSize,
		InCubeSize,  InCubeSize, -InCubeSize,
		InCubeSize, -InCubeSize, -InCubeSize,
		-InCubeSize, -InCubeSize, -InCubeSize,
		-InCubeSize,  InCubeSize, -InCubeSize,
	};

	uint Indices[] = { 
		0, 1, 3,	1, 2, 3, // Front face
		4, 5, 7,	5, 6, 7, // Back face
		4, 5, 0,	5, 1, 0, // Right face
		7, 6, 3,	6, 2, 3, // Left face
		4, 0, 7,	0, 3, 7, // Top face
		1, 5, 2,	5, 6, 2  // Bottom face
	};

	NewMesh->SetVerticesData(Vertices, sizeof(Vertices));
	NewMesh->SetIndicesData(Indices, sizeof(Indices));
	NewMesh->SetVertexCount(36);
	NewMesh->SetVertexLayout({ {3, sizeof(float)} });

	return NewMesh;
}

shared_ptr<Mesh> PrimitiveMeshBuilder::BuildCubeTextured(float InCubeSize)
{
	shared_ptr<Mesh> NewMesh = make_shared<Mesh>();

	float Vertices[] = {
		// Front face
		 InCubeSize,  InCubeSize,  InCubeSize, 1.0f, 1.0f,
		 InCubeSize, -InCubeSize,  InCubeSize, 1.0f, 0.0f,
		-InCubeSize, -InCubeSize,  InCubeSize, 0.0f, 0.0f,
		-InCubeSize,  InCubeSize,  InCubeSize, 0.0f, 1.0f,

		// Back face
		 InCubeSize,  InCubeSize, -InCubeSize, 1.0f, 1.0f,
		 InCubeSize, -InCubeSize, -InCubeSize, 1.0f, 0.0f,
		-InCubeSize, -InCubeSize, -InCubeSize, 0.0f, 0.0f,
		-InCubeSize,  InCubeSize, -InCubeSize, 0.0f, 1.0f,

		// Right face
		 InCubeSize,  InCubeSize, -InCubeSize, 1.0f, 1.0f,
		 InCubeSize, -InCubeSize, -InCubeSize, 1.0f, 0.0f,
		 InCubeSize, -InCubeSize,  InCubeSize, 0.0f, 0.0f,
		 InCubeSize,  InCubeSize,  InCubeSize, 0.0f, 1.0f,

		 // Left face
		 -InCubeSize,  InCubeSize,  InCubeSize, 1.0f, 1.0f,
		 -InCubeSize, -InCubeSize,  InCubeSize, 1.0f, 0.0f,
		 -InCubeSize, -InCubeSize, -InCubeSize, 0.0f, 0.0f,
		 -InCubeSize,  InCubeSize, -InCubeSize, 0.0f, 1.0f,

		 // Top face
		  InCubeSize,  InCubeSize, -InCubeSize, 1.0f, 1.0f,
		  InCubeSize,  InCubeSize,  InCubeSize, 1.0f, 0.0f,
		 -InCubeSize,  InCubeSize,  InCubeSize, 0.0f, 0.0f,
		 -InCubeSize,  InCubeSize, -InCubeSize, 0.0f, 1.0f,

		 // Bottom face
		  InCubeSize, -InCubeSize,  InCubeSize, 1.0f, 1.0f,
		  InCubeSize, -InCubeSize, -InCubeSize, 1.0f, 0.0f,
		 -InCubeSize, -InCubeSize, -InCubeSize, 0.0f, 0.0f,
		 -InCubeSize, -InCubeSize,  InCubeSize, 0.0f, 1.0f,
	};


	uint Indices[] = {
		 0,  1,  2,   0,  2,  3,   // Front
		 4,  5,  6,   4,  6,  7,   // Back
		 8,  9, 10,   8, 10, 11,   // Right
		12, 13, 14,  12, 14, 15,   // Left
		16, 17, 18,  16, 18, 19,   // Top
		20, 21, 22,  20, 22, 23    // Bottom
	};


	NewMesh->SetVerticesData(Vertices, sizeof(Vertices));
	NewMesh->SetIndicesData(Indices, sizeof(Indices));
	NewMesh->SetVertexCount(36);
	NewMesh->SetVertexLayout({ {3, sizeof(float)}, {2, sizeof(float)} });

	return NewMesh;
}
