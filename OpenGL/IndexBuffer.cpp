#include <exception>
#include <GL/glew.h>

#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(GLuint* _Indices, GLuint _Count)
	: m_Count(_Count), m_Indicies(_Indices)
{
	glCreateBuffers(1, &m_ID);

	if (!m_ID)
		throw std::exception();

	Bind();
	glBufferData(GL_ARRAY_BUFFER, _Count * sizeof(GLuint), _Indices, GL_STATIC_DRAW);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_ID);
}
