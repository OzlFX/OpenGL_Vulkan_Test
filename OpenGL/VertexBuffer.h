#ifndef _VERTEXBUFFER_H_
#define _VERTEXBUFFER_H_

//Temp Type Defines for OpenGL
typedef unsigned int GLuint;

class VertexBuffer
{
public:

	VertexBuffer();

	void Bind() const;
	void UnBind() const;

	void SetData(const void* _Data);

	const GLuint GetID() { return m_ID; }
	const GLuint GetSize() { return m_Size; }

	~VertexBuffer();

private:

	GLuint m_ID; //Define ID
	GLuint m_Size; //Define Size

};

#endif
