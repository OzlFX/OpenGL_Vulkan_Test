#include <exception>
#include <GL/glew.h>

#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
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