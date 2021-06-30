#ifndef _VERTEXBUFFER_H_
#define _VERTEXBUFFER_H_

#include <memory>

#include "BufferLayout.h"

//Temp Type Defines for OpenGL
typedef unsigned int GLuint;
typedef float GLfloat;

class VertexBuffer
{
public:

	VertexBuffer();
	VertexBuffer(const void* _Data, GLuint _Size);

	void Bind() const;
	void Unbind() const;

	void SetData(const GLfloat* _Data, GLuint _Size);
	void SetLayout(const BufferLayout& _Layout) { m_Layout = _Layout; }

	const int GetSize() { return m_DataSize; }
	const BufferLayout& GetLayout() { return m_Layout; }

	~VertexBuffer();

private:

	GLuint m_ID; //Define ID
	BufferLayout m_Layout;
	int m_DataSize;

};

#endif
