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

	~VertexBuffer();

private:

	GLuint m_ID; //Define ID

};

#endif
