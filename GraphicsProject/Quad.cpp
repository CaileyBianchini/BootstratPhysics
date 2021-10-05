#include "Quad.h"

Quad::Quad(glm::vec4 color) : Quad::Quad()
{
	m_color = color;
}

Quad::Vertex* Quad::generateVertices(unsigned int& vertexCount, unsigned int& triCount)
{
	Vertex* vertices = nullptr;
	vertexCount = 6;
	triCount = 2;

	//Define the vertices for a quad
	vertices = new Vertex[vertexCount];

	//triangle 0
	vertices[0].position = { -2.0f, 0.0f, 2.0f, 1.0f };
	vertices[1].position = { 2.0f, 0.0f, 2.0f, 1.0f };
	vertices[2].position = { -2.0f, 0.0f, -2.0f, 1.0f };
	//triangle 1
	vertices[3].position = { 2.0f, 0.0f, 2.0f, 1.0f };
	vertices[4].position = { -2.0f, 0.0f, -2.0f, 1.0f };
	vertices[5].position = { 2.0f, 0.0f, -2.0f, 1.0f };


	for (int i = 0; i < vertexCount; i++)
	{
		vertices[i].color = m_color;
		if(i == 0)
			vertices[0].color = { 1.0f, 0.0f, 0.0f, 1.0f };
	}


	return vertices;
}
