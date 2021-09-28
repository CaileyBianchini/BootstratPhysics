#pragma once
#include "gl_core_4_4.h"
#include "glm\vec4.hpp"
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


private:
	unsigned int m_triCount;
	unsigned int m_vertexArrayObject, m_vertexBufferObject, m_indexBufferObject;

};

