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
	unsigned int vertexCount;
	Vertex* vertices = generateVertices(vertexCount, m_triCount);

	//fill vertex buffer
	glBufferData(
		GL_ARRAY_BUFFER,                       //type of buffer
		sizeof(Vertex) * vertexCount,           //size in bytes of all vertices
		vertices,                                              //all verticeis
		GL_STATIC_DRAW                          //how the data will update
	);

	unsigned int memoryPosition = 0u;
	//Enable vertex POSITION as first attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,						//attribute index
		4,						//number of values within attribute
		GL_FLOAT,				//type of each value
		GL_FALSE,				//whether to normalize
		sizeof(Vertex),			//size in bytes of one vertex
		(void*)memoryPosition	//memory position of this attribute
	);
	memoryPosition += sizeof(Vertex::position);

	//Enable vertex NORMAL as second attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,						//attribute index
		4,						//number of values within attribute
		GL_FLOAT,				//type of each value
		GL_TRUE,				//whether to normalize
		sizeof(Vertex),			//size in bytes of one vertex
		(void*)memoryPosition	//memory position of this attribute
	);
	memoryPosition += sizeof(Vertex::normal);

	//Enable vertex TEXTURE COORDINATE as third attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,						//attribute index
		2,						//number of values within attribute
		GL_FLOAT,				//type of each value
		GL_FALSE,				//whether to normalize
		sizeof(Vertex),			//size in bytes of one vertex
		(void*)memoryPosition	//memory position of this attribute
	);
	memoryPosition += sizeof(Vertex::texCoord);

	//Enable vertex TANGENT as fourth attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(
		3,						//attribute index
		4,						//number of values within attribute
		GL_FLOAT,				//type of each value
		GL_FALSE,				//whether to normalize
		sizeof(Vertex),			//size in bytes of one vertex
		(void*)memoryPosition	//memory position of this attribute
	);
	memoryPosition += sizeof(Vertex::tangent);

	//Enable vertex COLOR as fifth attribute
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(
		4,						//attribute index
		4,						//number of values within attribute
		GL_FLOAT,				//type of each value
		GL_FALSE,				//whether to normalize
		sizeof(Vertex),			//size in bytes of one vertex
		(void*)memoryPosition	//memory position of this attribute
	);
	memoryPosition += sizeof(Vertex::color);


	//unbind 
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//deallocated vertices
	delete[] vertices;
}

void Mesh::draw(aie::ShaderProgram* shader)
{
	shader->bindUniform("modelMatrix", m_transform);
	glBindVertexArray(m_vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, m_triCount * 3);
}

