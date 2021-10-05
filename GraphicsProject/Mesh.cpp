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
	//enable vertex color as a second attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,                                                     //attribute index
		4,                                                   //number of values within attribute
		GL_FLOAT,                                 //type of each value
		GL_FALSE,                                  //whether to normalize
		sizeof(Vertex),                            // sizze in bytes of one vertex
		(void*)sizeof(glm::vec4)          //memory position of this attribute
	);
	//enable vertex normal as third attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,                                                      //attribute index
		4,                                                     //number of values within attribute
		GL_FLOAT,                                   //type of each value
		GL_TRUE,                                    //wether to normalize
		sizeof(Vertex),                             //size in bytes of one vertex
		(void*)(sizeof(glm::vec4) * 2)  //memory position of this attribute
	);

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

