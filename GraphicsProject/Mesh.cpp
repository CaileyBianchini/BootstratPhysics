#include "Mesh.h"

Mesh::Mesh()
{
	m_transform = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	m_triCount = 0;
	m_vertexArrayObject = 0;
	m_vertexBufferObject = 0;
	m_indexBufferObject = 0;
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
	glDeleteBuffers(1, &m_vertexBufferObject);
	glDeleteBuffers(1, &m_indexBufferObject);
}

void Mesh::start()
{
	assert(m_vertexArrayObject == 0);

	//Generate buffers
	glGenBuffers(1, &m_vertexBufferObject);
	glGenVertexArrays(1, &m_vertexArrayObject);

	//Bind vertex array
	glBindVertexArray(m_vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);

	//Generate the vertices
	//Vertex* vertices{};
	//int vertexCount;
	//generateVertices(vertices, vertexCount);

	//define the vertives for a quad
	Vertex verticies[6];
	//triangle 0
	verticies[0].position = { -0.5f, 0.0f, 0.5f, 1.0f };                                 // or glm::vec4()
	verticies[1].position = { 0.5f, 0.0f, 0.5f, 1.0f };
	verticies[2].position = { -0.5f, 0.0f, 0.5f, 1.0f };
	//triangle 1
	verticies[3].position = { 0.5f, 0.0f, 0.5f, 1.0f };
	verticies[4].position = { -0.5f, 0.0f, -0.5f, 1.0f };
	verticies[5].position = { 0.5f, 0.0f, -0.5f, 1.0f };

	//fill vertex buffer
	glBufferData(
		GL_ARRAY_BUFFER,     //type of buffer
		sizeof(Vertex) * 6,           //size in bytes of all vertices
		verticies,                          //all verticeis
		GL_STATIC_DRAW      //how the data will update
	);

	// Enable vertex position as first attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                                         //attribute index
		4,                                        //number of values within attributes
		GL_FLOAT,                      //type of each value
		GL_FALSE,                      //whether to normalise
		sizeof(Vertex),                 //size in bytes on one vertex
		0                                       //memory position of this attribute
	);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::draw()
{
	glBindVertexArray(m_vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Mesh::generateVertices(Vertex* vertices, int& vertexCount)
{
	
}
