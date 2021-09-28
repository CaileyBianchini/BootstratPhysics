#include "Mesh.h"

Mesh::Mesh()
{
	m_triCount = 0;
	m_vertexArrayObject = 0;
	m_vertexBufferObject = 0;
	m_indexBufferObject = 0;

	assert(m_vertexArrayObject == 0);

	//Generate buffers
	glGenBuffers(1, &m_vertexArrayObject);
	glGenVertexArrays(1, &m_vertexArrayObject);

	//Bind vertex array
	glBindVertexArray(m_vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
	glDeleteBuffers(1, &m_vertexBufferObject);
	glDeleteBuffers(1, &m_indexBufferObject);
}
