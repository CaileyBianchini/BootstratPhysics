#pragma once
#include "gl_core_4_4.h"
#include "glm\vec4.hpp"
#include "glm\mat4x4.hpp"

class Mesh
{
public:
	struct Vertex 
	{
		glm::vec4 position;
		glm::vec4 color;
	};
public:
	Mesh();
	~Mesh();

	void start();
	void draw();

	void generateVertices(Vertex* vertices, int& vertexCount);

	glm::mat4 getTransform() { return m_transform;  }
	void setTansform(glm::mat4 transform) { m_transform = transform; }

private:
	glm::mat4 m_transform;
	unsigned int m_triCount;
	unsigned int m_vertexArrayObject, m_vertexBufferObject, m_indexBufferObject;

};

