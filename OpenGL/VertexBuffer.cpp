#include <exception>
#include <GL/glew.h>

#include "VertexBuffer.h"

/*VertexBuffer::VertexBuffer()
	: m_DataSize(0), m_ID(0)
{
	glGenBuffers(1, &m_ID); //Create a new VBO using the VBO id

	if (!m_ID)
		throw std::exception();
}*/

VertexBuffer::VertexBuffer(const void* _Data, GLuint _Size)
	: m_DataSize(_Size), m_ID(0)
{
	glGenBuffers(1, &m_ID); //Create a new VBO using the VBO id

	if (!m_ID)
		throw std::exception();

	Bind();
	//Upload a copy of the data from memory to VBO
	glBufferData(GL_ARRAY_BUFFER, _Size, _Data, GL_STATIC_DRAW);
}

//Bind the buffer
void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID); //Bind the VBO data
}

//Unbind the buffer
void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbind
}

void VertexBuffer::SetData(const GLfloat* _Data, GLuint _Size)
{
	m_DataSize = _Size;
	Bind();
	//Upload a copy of the data from memory to VBO
	glBufferData(GL_ARRAY_BUFFER, _Size, _Data, GL_STATIC_DRAW);
	Unbind();
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_ID); //Delete VBO
}