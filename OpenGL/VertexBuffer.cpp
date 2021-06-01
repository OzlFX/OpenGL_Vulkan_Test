#include <exception>
#include <GL/glew.h>

#include "VertexBuffer.h"

VertexBuffer::VertexBuffer() : m_Components(0), m_DataSize(0)
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

void VertexBuffer::SetData(const GLfloat* _Data, int _ComponentSize)
{
	m_DataSize = sizeof(_Data);
	m_Components = _ComponentSize;
	//Upload a copy of the data from memory to VBO
	glBufferData(GL_ARRAY_BUFFER, m_DataSize * sizeof(GLfloat), _Data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_ID); //Delete VBO
}