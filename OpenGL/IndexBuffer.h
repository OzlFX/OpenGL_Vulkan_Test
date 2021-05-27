#ifndef _INDEXBUFFER_H_
#define _INDEXBUFFER_H_

//Temp Type Defines for OpenGL
typedef unsigned int GLuint;

class IndexBuffer
{
public:

	IndexBuffer(GLuint* _Indices, GLuint _Count);

	void Bind() const;
	void UnBind() const;

	GLuint GetCount() const { return m_Count; }

	~IndexBuffer();

private:

	GLuint m_ID;
	GLuint m_Count;

};

#endif
