#include <exception>
#include <GL/glew.h>

#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	m_ID = 0; //Set the Vertex Buffer Object ID
	m_Size = 0; //Set initial size to 0

	glGenBuffers(1, &m_ID); //Create a new VBO using the VBO id

	if (!m_ID)
		throw std::exception();
}

//Bind the buffer
void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID); //Bind the VBO data
}

//Unbind the buffer
void VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbind
}

void VertexBuffer::SetData(const void* _Data)
{
	//Upload a copy of the data from memory to VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(_Data), _Data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_ID); //Delete VBO
}