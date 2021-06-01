#ifndef _VERTEXBUFFER_H_
#define _VERTEXBUFFER_H_

//Temp Type Defines for OpenGL
typedef unsigned int GLuint;
typedef float GLfloat;

class VertexBuffer
{
public:

	VertexBuffer();

	void Bind() const;
	void UnBind() const;

	void SetData(const void* _Data, int _ComponentSize = 3);
	int GetSize() { return m_DataSize; }
	int GetComponentCount() { return m_Components; }

	~VertexBuffer();

private:

	GLuint m_ID; //Define ID
	int m_Components;
	int m_DataSize;

};

#endif
